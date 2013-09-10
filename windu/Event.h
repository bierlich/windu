#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <forward_list>

#ifndef __Event__
#define __Event__

using namespace std;

template<typename Ptype, typename Etype>
class Event {
public:
	Event(){
		_good = false;
	}

	Event(forward_list<Ptype> pList, shared_ptr<Etype> eventPar){
		_pList = pList;
		_eventPar = eventPar;
		_good = false;
	}

	Event(const Event& other)
		: _good(other._good), _pList(other._pList), _eventPar(other._eventPar)
		{
	}

	Event(Event&& other)
		: _good(other._good), _pList(move(other._pList)), _eventPar(other._eventPar)
		{
		other._eventPar.reset();
	}

	~Event(){
	}

	template<typename TT>
	void AddParticle(TT&& p){
		_pList.push_front(forward<TT>(p));
	}

	typename forward_list<Ptype>::iterator begin(){
		return _pList.begin();
	}

	void Clean(){
		_eventPar.reset();
		_good = false;
		_pList.clear();
	}

	typename forward_list<Ptype>::iterator end(){
		return _pList.end();
	}

	bool IsGood(){
		return _good;
	}
	
	shared_ptr<Etype> GetPar(){
		shared_ptr<Etype> ptr = _eventPar;
		return ptr;
	}

protected:
private:
	bool _good;
	forward_list<Ptype> _pList;
	shared_ptr<Etype> _eventPar;
	template<typename TX, typename TY>
	friend istream& operator>> (istream& aStream, Event<TX,TY>& aEvent); 
	template<typename TZ, typename TW>
	friend ostream& operator<< (ostream& aStream, Event<TZ,TW>& aEvent); 
};

	#include "Event.hxx"
#endif