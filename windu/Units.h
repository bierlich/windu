// Just a very simple template based unit system
// Written for test purposes only.
// Written for HEP, so we use c==1 (!=h) units,
// and the two exponents used are thus
// <LENGTH = TIME, ENERGY>
#include <iostream>

template<int L, int E>
class Qty {
public:
    Qty(double raw = 1.) : _raw(raw) {

    }
    double _raw;

protected:

private:

};


template<int L, int E>
    Qty<L,E> operator *(Qty<L,E> lhs, double rhs){
        return Qty<L,E>(lhs._raw*rhs);
    }

template<int L, int E>
    Qty<L,E> operator /(Qty<L,E> lhs, double rhs){
        return Qty<L,E>(lhs._raw/rhs);
    }

template<int L, int E>
    Qty<L,E> operator *(double lhs,Qty<L,E> rhs){
        return Qty<L,E>(lhs*rhs._raw);
    }

template<int L, int E>
    Qty<L,E> operator /(double lhs, Qty<L,E> rhs){
        return Qty<L,E>(lhs/rhs._raw);
    }

template<int L, int E>
    Qty<L,E> operator +(Qty<L,E> lhs, double rhs){
        return Qty<L,E>(lhs._raw+rhs);
    }

template<int L, int E>
    Qty<L,E> operator -(Qty<L,E> lhs, double rhs){
        return Qty<L,E>(lhs._raw-rhs);
    }

template<int l1, int e1, int l2, int e2>
    Qty<l1+l2, e1+e2> operator* (Qty<l1,e1> lhs, Qty<l2,e2> rhs){
        return Qty<l1+l2, e1+e2>(lhs._raw*rhs._raw);
    }

template<int l1, int e1, int l2, int e2>
    Qty<l1-l2, e1-e2> operator/ (Qty<l1,e1> lhs, Qty<l2,e2> rhs){
        return Qty<l1-l2, e1-e2>(lhs._raw/rhs._raw);
    }

template<int l, int e>
    Qty<l, e> operator+ (Qty<l,e> lhs, Qty<l,e> rhs){
        return Qty<l, e>(lhs._raw+rhs._raw);
    }

template<int l, int e>
    Qty<l, e> operator- (Qty<l,e> lhs, Qty<l,e> rhs){
        return Qty<l, e>(lhs._raw-rhs._raw);
    }

template<int l, int e>
    bool operator< (Qty<l,e> lhs, Qty<l,e> rhs){
        return lhs._raw<rhs._raw;
    }

template<int l, int e>
    bool operator> (Qty<l,e> lhs, Qty<l,e> rhs){
        return lhs._raw>rhs._raw;
    }
template<int l, int e>
    bool operator<= (Qty<l,e> lhs, Qty<l,e> rhs){
        return lhs._raw<=rhs._raw;
    }

template<int l, int e>
    bool operator>= (Qty<l,e> lhs, Qty<l,e> rhs){
        return lhs._raw>=rhs._raw;
    }

template<int l, int e>
    bool operator== (Qty<l,e> lhs, Qty<l,e> rhs){
        return lhs._raw==rhs._raw;
    }

template<int l, int e>
    bool operator!= (Qty<l,e> lhs, Qty<l,e> rhs){
        return lhs._raw!=rhs._raw;
    }
template<>
    class Qty<0,0>{
        public:
    Qty(double raw = 1.) : _raw(raw) {

    }
    operator double() {
     return _raw;   
    }
    double _raw;

    protected:

    private:

   // friend ostream& operator<< (ostream& aStream, Qty<0,0>& aQty);

    };

ostream& operator << (ostream& aStream, const Qty<0,0>& aQty){
            aStream << aQty._raw;
            return aStream;
        }

typedef Qty<1,0> Length; // Base unit cm
Length centimeter = Length();
Length meter = centimeter*100;
typedef Qty<0,1> Energy; //Base unit MeV
typedef Qty<-1,0> InvLength; // Base unit cm
InvLength invCentimeter = InvLength();
InvLength invMeter = invCentimeter/100;
