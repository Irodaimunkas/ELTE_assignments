#include "bag.h"
#include <stdlib.h>
#include <algorithm>

Bag::Bag(){
    _first = NULL;
    _last = NULL;
    _enumaratorCount = 0;
}

Bag::~Bag(){
    bagElem *p, *q;
    q = _first;
    while( q != NULL ){
        p = q;
        q = q->next;
        delete p;
    }
}

/*
Erase from bag
Input: one integer
Output: -
Description: The function defines two node pointer, p's equal with NULL, q's equal with the bag's first node.
Then until q doesn't equal with NULL and q's value doesn't equal with the input value (e), p will be q, and q will be the next node
on the list after q. After this, if q doesn't equal NULL, the function checks if q's current count bigger than one, if yes, it substracts
from it one, if not, it checks if p equals NULL, if yes, it makes the bag's first node's next pointer equal with q's next pointer, if not,
it makes p's next pointer equal with q's next pointer.
*/
void Bag::erase(int e){
    bagElem *q, *p;
    p = NULL;
    q = _first;
    while(q != NULL && q->_val != e){
        p = q;
        q = q->next;
    }
    if(q != NULL){
        if(q->_count > 1) q->_count--;
        else if(p == NULL){
            this->_first = q->next;
        } else p->next = q->next;
    }
}

/*
Input value's count
Input: one integer
Output: -
Description: Returns the input value's count.
*/

int Bag::count(int i)
{
    int c = 0;
    Bag:: Enumerator it2 = createEnumerator ();
    for(it2.first(); !it2.end(); it2.next()){
        if (it2.current_val()==i) {
            c = it2.current_count();
            break;
        }
    }
    return c;
}

/*
Input value's count
Input: one integer
Output: -
Description: Returns a true if the input is in the bag, false if not.
*/
bool Bag::isElem(int i)
{
    bool c = 0;
    Bag:: Enumerator it2 = createEnumerator ();
    for(it2.first(); !it2.end(); it2.next()){
        if (it2.current_val()==i) {
            c = 1;
            break;
        }
    }
    return c;
}
/*
Writing out the bag
Input: -
Output: -
Description: The function defines an i index and makes it equal to one. Then it defines a q node pointer and makes it equal to the first
node of the bag. Then while q doesn't equal with NULL, it writes out i, q's value, and q's count, then it makes q equal with q's next pointer,
and adds one to i.
*/
std::ostream& operator<<(std::ostream& out, Bag& x) {
    int i = 1;
    bagElem *q;
    q = x._first;
    while(q != NULL) {
        out << std::endl << "A zsak "<< i << ". tagjanak erteke: "<< q->_val << " darabszama: " << q->_count << std::endl;
        q = q->next;
        i++;
    }
    return out;
}

Bag::Bag(const Bag& x){
    if(x._first == NULL){
        _first = _last = NULL;
    } else{
        bagElem *q = new bagElem;

        q->_val = x._first->_val;
        q->_count = x._first->_count;
        q->prev = NULL;
        q->next = NULL;

        _first = q;
        _last = q;

        for(bagElem *p=x._first->next;p!=NULL;p=p->next){
            q = new bagElem;
            q->_count = p->_count;
            q->_val = p->_val;
            q->prev = _last;
            q->next = NULL;
            _last->next = q;
            _last = q;
        }
    }
}

/*
Makes the left bag equal with the right bag
Input: one bag
Output: bag reference
Description: If the two bags' address is equal, the function returns the current bag. If this is not the case, then first it deletes
all of the nodes from the left bag, then if the right bag is empty, it makes the left one empty too. If the right bag is not empty,
then it copies all of the nodes from the right bag to the left.
*/
Bag& Bag::operator=(const Bag& x){
    if(this == &x) return *this;
    bagElem *q = _first;

//Deleting left list
    while(q!=NULL){
        bagElem *p = q->next;
        delete q;
        q = p;
    }

//If right list is empty
    if(x._first==NULL){
        _first = _last = NULL;
    }

//Copy right list to the left list
    else{
        bagElem *q = new bagElem;

        q->_count = x._first->_count;
        q->_val = x._first->_val;
        q->prev = x._first->prev;
        q->next = x._first->next;

        _first = _last = q;

        for(bagElem *p=x._first->next;p!=NULL;p=p->next){
            q = new bagElem;
            q->_count = p->_count;
            q->_val = p->_val;
            q->prev = _last;
            q->next = NULL;
            _last->next = q;
            _last = q;
        }
    }
    return *this;
}

/*
Read to bag
Input: istream, bag
Output: istream reference
Description: The function reads an input into an integer, if the input fails, it throws an exception. If not, then it checks if the bag is
empty or  if the first node's value is bigger or equal than the input, if one of these is true, then it checks if the first node's value
is bigger than the input value or if the bag is empty, if that's true, it inserts the new value before the first node with a count of one, and makes the first
node the input node. If the is equal to the first node, it adds one to the first node's count, if non of these are true, it inserts the
input node into the list in ascending order. Of course, if the input value is already present on the list, it just adds one to it's counter.
*/
std::istream& operator>>(std::istream& in, Bag& x){
    int e;
    in >> e;

//Input error handling
    if(in.fail()) throw Bag::INT_INPUT_STRING;

    if(x._first == NULL || x._first->_val >= e){
//First node greater than input node
        if(x._first == NULL || x._first->_val > e){
        bagElem *q = new bagElem;

        q->_count = 1;
        q->_val = e;
        q->prev = NULL;
        q->next = x._first;
        x._first = q;

        }
//First node equals input node
    else x._first->_count++;
    }

//Other cases
    else{
        bagElem *p, *q;
        p = x._first;

        q = new bagElem;
        q->_val = e;

//A pointer tries to find the input node in the list
        while(p->next != NULL && p->next->_val <= e) p = p->next;

//Input node exists in list
        if(p->_val == e){
            p->_count++;
        }

//Input node doesn't exist in list
        else {
            q->_count = 1;
            q->next = p->next;
            q->prev = p;
            p->next = q;
        }
    }
    return in;
}

/*
Returns two bags' symmetric difference
Input: bag, bag
Output: -
Description: If either of the two bags are empty, the non-empty one will be the symmetric difference. Otherwise it checks the two bags
with two node pointers. If the pointers' value is equal, if yes, and their counts are the same too, it moves on to the next node,
if their counts'  aren't the same, then the symmetric difference's count will be the two counts' subtraction in absolute value.
If one of the pointers' value (a) is bigger than the other one's (b), then it inserts b and moves to b's next node. If b is bigger than
a, then the same happens with a. Then after one of the pointers' reaches NULL (the bag's end), then the function links the rest of
the other bag to the symmetric difference.
*/
Bag operator-(const Bag& a, const Bag& b){
    Bag _return;
    if(a.isEmpty()){
        _return._first = b._first;
        _return._last = b._last;
    }else if(b.isEmpty()){
        _return._first = a._first;
        _return._last = a._last;
    } else{

        bagElem *q_a, *q_b, *p;
        q_a = a._first;
        q_b = b._first;

        while((q_a != NULL) && (q_b != NULL)){
            if(q_a->_val == q_b->_val){
                if(abs(q_a->_count - q_b->_count) == 0){
                    q_a = q_a->next;
                    q_b = q_b->next;
                } else{
                    p = new bagElem;
                    p->next = NULL;

                    if(_return._first == NULL) _return._first = _return._last = p;
                    else {
                        _return._last->next = p;
                        _return._last = p;
                    }

                    p->_val = q_b->_val;
                    p->_count = abs(q_b->_count - q_a->_count);
                    q_a = q_a->next;
                    q_b = q_b->next;
                }
            } else if (q_a->_val > q_b->_val){
                p = new bagElem;
                p->next = NULL;

                if(_return._first == NULL) _return._first = _return._last = p;
                else {
                    _return._last->next = p;
                    _return._last = p;
                }

                p->_val = q_b->_val;
                p->_count = q_b->_count;
                q_b = q_b->next;
            } else{
                p = new bagElem;
                p->next = NULL;

                if(_return._first == NULL) _return._first = _return._last = p;
                else {
                    _return._last->next = p;
                    _return._last = p;
                }

                p->_val = q_a->_val;
                p->_count = q_a->_count;
                q_a = q_a->next;
            }
        }

        if(q_a == NULL){
            _return._last->next = q_b;
            _return._last = b._last;
        } else {
            _return._last->next = q_a;
            _return._last = a._last;
        }
    }
    return _return;
}

/*
Returns two bags' intersection
Input: bag, bag
Output: -
Description: If one of the bags' is empty, it returns an empty list. Else it checks if the two bags have equal values, if they have,
the function inserts the value and the smaller count into the intersection.
*/
Bag operator+(const Bag& x, const Bag& a){
    Bag _return;
    if(x.isEmpty() || a.isEmpty()) _return._first = _return._last = NULL;
    else{
        bagElem *p;

        for(bagElem *q_x = x._first; q_x != NULL; q_x = q_x->next){
            for(bagElem *q_a = a._first; q_a != NULL; q_a = q_a->next){
                if(q_a->_val == q_x->_val){
                    p = new bagElem;
                    p->next = NULL;

                    if(_return._first == NULL) _return._first = _return._last = p;
                    else {
                        _return._last->next = p;
                        _return._last = p;
                    }

                    p->_val = q_x->_val;
                    p->_count = std::min(q_x->_count, q_a->_count);
                }
            }
        }
    }
    return _return;
}
