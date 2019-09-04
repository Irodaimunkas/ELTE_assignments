/*
Gonda Dávid
2017.10.03.
Zsák objektum készítése/Zsák metszete (8. feladat)
*/

#ifndef BAG_H_INCLUDED
#define BAG_H_INCLUDED

#include <iostream>


//Bag node structure
    struct bagElem{
    int _count;
    int _val;
    bagElem *prev;
    bagElem *next;
    };


//Bag class
//Methods: Insert, delete, isEmpty, a given value's count, write out the bag, intersection, symmetric difference
//Presentation: The bag's nodes are made in a structure (value, count), these are represented on a linked list
class Bag{
public:
    enum Exceptions{ INT_INPUT_STRING };
    Bag();
    ~Bag();

    void erase(int e);
    bool isEmpty() const { return _first == _last; };
    int count(int e);
    bool isElem(int i);
    friend std::ostream& operator<<(std::ostream& out, Bag& x);
    friend Bag operator-(const Bag& a, const Bag& b);
    friend Bag operator+(const Bag& x, const Bag& a);

    Bag(const Bag& x);
    Bag& operator=(const Bag& x);
    friend std::istream& operator>>(std::istream& in, Bag& x);

class Enumerator {
    public:
        Enumerator(Bag *p):_bq(p),_current(NULL) {
            ++(_bq->_enumaratorCount);
        }
        ~Enumerator() {
            --(_bq->_enumaratorCount);
        }
        int current_val()const {
            return _current->_val;
        }
        int current_count()const {
            return _current->_count;
        }
        void first()  {
            _current = _bq->_first;
        }
        bool end()    const {
            return _current==NULL;
        }
        void next()   {
            _current = _current->next;
        }

    private:

        Bag *_bq;
        bagElem *_current;
    };

    Enumerator createEnumerator() {
        return Enumerator(this);
    }

private:
    bagElem *_first;
    bagElem *_last;

    int _enumaratorCount;
};




#endif // BAG_H_INCLUDED
