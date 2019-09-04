//Made by Gonda David
//Date: 04/12/2017
//4th assignment
//2nd task

#include <iostream>
#include "library/summation.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include <fstream>
#include <clocale>

using namespace std;

//Input pairs, and their money in-/outtake container
struct Pair {
    int _account;
    int _moneyMove;
    int result;

    friend ifstream& operator>>(ifstream&, Pair&);
};

ifstream& operator>>(ifstream& f, Pair& df)
{
f >> df._account >> df._moneyMove;
return f;
}

/*class SeqInFileEnumerator : public Enumerator<Pair>{
    protected:
        std::ifstream _f;
        Pair          _df;

    public:
        enum Exceptions { OPEN_ERROR };
        SeqInFileEnumerator(const std::string& str){
            _f.open(str.c_str());
            if(_f.fail()) throw OPEN_ERROR;
        }

        void first()         final override { next();}
        void next()          final override { _f >> _df._account >> _df._moneyMove;}
        bool end()     const final override { return _f.eof();}
        Pair current() const final override { return _df; }
};
*/
//The linear search's condition
class MyLinSearch : public LinSearch<Pair> {
public:
    bool cond(const Pair& e) const override {
        return e.result <= -100000;
    }
};

//The account-money move's enumerator
class PairEnumerator : public Enumerator<Pair> {
protected:
    SeqInFileEnumerator<Pair> *_f;
    Pair _current;
    bool _end;
public:
    PairEnumerator(const string& str) {
        _f = new SeqInFileEnumerator<Pair>(str);
    }
    ~PairEnumerator() {
        delete _f;
    }
    void first() override {
        _f->first();
    }
    void next() override;
    bool end() const override {
        return _end;
    }
    Pair current() const override {
        return _current;
    }
};

//Defines the summation, an account's money moves' summation goes until another account is read
class MoneyMoving : public Summation<Pair, int> {
protected:
    Pair _act;
    void first() override {}
    bool whileCond(const Pair& e) const override {
        return e._account == _act._account;
    }
    void add(const Pair &e) {
        *Summation<Pair, int>::_result+= e._moneyMove;
    }
    void init(){
        *Summation<Pair, int>::_result = 0;
    }
    bool cond(const Pair& e){ return e._moneyMove < 0; }
public:
    MoneyMoving(const Pair &str):
        Summation<Pair, int>(), _act(str) {}
};

//PairEnumerator's next function: if the file has ended, it returnes, if not, it gives the current account's money move
void PairEnumerator::next() {
    if((_end = _f->end())) return;

    _current = _f->current();

    MoneyMoving pr(_current);
    pr.addEnumerator(_f);
    pr.run();
    _current.result = pr.result();
//  cout << _current.result << endl;
}

//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main() {
    setlocale(LC_ALL,"hun");

    MyLinSearch pr;
    PairEnumerator t("inp.txt");
    pr.addEnumerator(&t);
    pr.run();
    cout << "Eredmény: ";
    if (pr.found())
        cout << "Igen";
    else cout << "Nem";
//    cout << pr.elem()._account << " " << pr.elem().result;
    return 0;
}

#else

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("front","inp_front.txt"){
    MyLinSearch pr;
    PairEnumerator t("inp_front.txt");
    pr.addEnumerator(&t);
    pr.run();
    CHECK(pr.found() == true);
}

TEST_CASE("middle","inp.txt"){
    MyLinSearch pr;
    PairEnumerator t("inp.txt");
    pr.addEnumerator(&t);
    pr.run();
    CHECK(pr.found() == true);
}

TEST_CASE("end","inp_end.txt"){
    MyLinSearch pr;
    PairEnumerator t("inp_front.txt");
    pr.addEnumerator(&t);
    pr.run();
    CHECK(pr.found() == true);
}

TEST_CASE("not found","inp2.txt"){
    MyLinSearch pr;
    PairEnumerator t("inp2.txt");
    pr.addEnumerator(&t);
    pr.run();
    CHECK(pr.found() == false);
}

TEST_CASE("empty","empty.txt"){
    MyLinSearch pr;
    PairEnumerator t("empty.txt");
    pr.addEnumerator(&t);
    pr.run();
    CHECK(pr.found() == false);
}

#endif
