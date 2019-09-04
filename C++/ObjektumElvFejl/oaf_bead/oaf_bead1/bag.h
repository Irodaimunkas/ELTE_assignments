/*
Gonda Dávid
2017.10.03.
Zsák objektum készítése/Zsák metszete (8. feladat)
*/

#ifndef BAG_H_INCLUDED
#define BAG_H_INCLUDED

//Zsak elemei struktúra
struct zsElem{
    int ertek;
    int darab;
    };

//Zsak osztaly
//Műveletek: Zsakba beszuras, torles, ures-e, megadott elem darab szama, kepernyore iras, metszet
//Reprezentáció: Zsak elemei strukturaval vannak megadva (elem erteke, darabszama), ezen elemek pedig egy dinamikus tombben szerepelnek
class Bag{
public:
    Bag();
    ~Bag();

    void insert(int e);
    void erase(int e);
    bool isEmpty() {return meret == 0;};
    int elemCount(int e);
    void write();
    void intersection(Bag x, Bag a);

//Tesztekhez
    int _ertek(int e) { return elems[e].ertek;}
    int _darab(int e) { return elems[e].darab;}

    Bag(const Bag& x);
    Bag& operator=(const Bag& x);

private:
    zsElem* elems;
    int meret;
};




#endif // BAG_H_INCLUDED
