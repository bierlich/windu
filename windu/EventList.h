#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <memory>

#ifndef __EventList__
#define __EventList__

using namespace std;

template<typename Etype>
class EventList {
private:
	class Node {
		public:
			template<typename T>
			Node(T&& val, EventList* elist) : _val(forward<T>(val)), _elist(elist) {
				_next.reset();
			}
			~Node(){
				_next.reset();
			}
			Etype & getVal() {return _val;}
			shared_ptr<Node> _next;
		private:
			Etype _val;
			EventList * _elist;
		friend class EventList;
		friend class Iterator;	
	};

	bool FillFromInput(Etype& newroot){
		long int ncount = 0;
		_root.reset();
		push_back(newroot);
		Etype tmpevent;
		while(_is >> tmpevent&&ncount!=_block){
			push_back(tmpevent);
			tmpevent.Clean();
			++ncount;
		}

		if(_is.eof()){
			_is.close();
			return true;
		}
		else if(_is.good()){
			return false;
		}
		cerr << "Broken stream! (1)" << endl;
		return true;
	}

	bool FillFromInput(){
		long int ncount = 0;
		//		_root.reset();
		Etype tmpevent;
		while(_is >> tmpevent&&ncount!=_block){
			push_back(tmpevent);
			tmpevent.Clean();
			++ncount;
		}
		if(_is.eof()){
			_is.close();
			return true;
		}
		else if(_is.good()){
			return false;
		}
		cerr << "Broken stream! (2)" << endl;
		return true;
	}

	shared_ptr<Node> _empty;
	shared_ptr<Node> _root;
	shared_ptr<Node> _last;
	string _input;
	ifstream _is;
	long int _block;

public:
	EventList() {
		_root.reset();
		_last.reset();
		_empty.reset();
		_block = 1;
	}

	EventList(string input, int mem=10000000) {
		_input = input;
		_is.open(_input);
		if(!_is) cout << "Problem opening " << _input << endl;
		_root.reset();
		_last.reset();
		_empty.reset();
		_block = mem;
	}

	~EventList(){
		_is.close();
		_root.reset();
	}

	void Clear(){
		if (!_is.good())_is.open(_input);
		if(!_is) cout << "Problem opening " << _input << endl;
		_is.clear();
		_root.reset();
		_last.reset();
		_empty.reset();
	}

	template<typename T>
	void push_back(T&& event){
		if(!_root){
			_root = shared_ptr<Node>(new Node(forward<T>(event),this));
			_last = _root;
		}
		else{
			auto p = shared_ptr<Node>(new Node(forward<T>(event),this));
			_last->_next = p;
			_last = p; 
		}
	}

	void set_input(string input, int mem=100000){
		_input = input;
		_is.open(_input);
		if(!_is) cout << "Problem opening " << _input << endl;
		_root.reset();
		_last.reset();
		_empty.reset();
		_block = mem;
	}

	void set_blocklen(int blen){
		_block = blen;
	}
	
	class Iterator : public iterator<forward_iterator_tag, Etype> {
		public:
			Iterator(shared_ptr<Node> p) : _node(p) {
			}

			~Iterator() {
			}
			Iterator& operator=(const Iterator& other){
				_node = other._node;
				return *this;
			}
			bool operator==(const Iterator& other){
				return _node == other._node;
			}
			bool operator!=(const Iterator& other){
				return _node!=other._node;
			}
			Iterator& operator++(){
				if(_node==_node->_elist->_last){
					_node = _node->_elist->_empty;
				}
				else{
					_node = _node->_next;

				}
				/*if(_node){
					if(_node==_node->_elist->_last){
						cout << "!! 1" << endl;
						if(_node->_elist->FillFromInput(_node->getVal())){
							cout << "!! 2" << endl;
							_node = _node->_next;
							 return *this;
						}
						else{
							cout << "!! 3" << endl;
					//		cout << "Filling again" << endl;
							_node = _node->_elist->_root;
							return *this;
						}
					}*/
				//}	
				return *this;
			}
			Etype& operator*(){
				return _node->getVal();
			}
			Etype* operator->(){
				return(&*(EventList<Etype>::Iterator)*this);
			}
		private:
			shared_ptr<Node> _node;	
		};

	Iterator begin(){
		FillFromInput();
		return Iterator(_root);
	}	

	Iterator end(){
		return _empty;
	}

protected:
friend class Node;
};
	#include "EventList.hxx"
#endif
