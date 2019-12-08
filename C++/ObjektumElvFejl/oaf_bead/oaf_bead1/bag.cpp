/*
Gonda Dávid
2017.10.03.
Zsák objektum készítése/Zsák metszete (8. feladat)
*/

#include <iostream>
#include "bag.h"
#include <string>

// Konstruktor
// Tevékenység:	A konstruktor létrehozza a zsak ertekeinek a dinamikus tombot (meret a dinamikus tombben allo adatokat jeloli, ami
// alapbol nulla)
// Bemenõ adatok:  	~
// Kimenõ adatok:  	~
Bag::Bag() {
    meret = 0;
    elems = new zsElem[meret+1];
    elems[0].darab = 0;
    elems[0].ertek = 0;
}

// Destruktor
// Tevékenység:	Felszabaditja a lefoglalt dinamikus memoriat
// Bemenõ adatok:  	~
// Kimenõ adatok:  	~
Bag::~Bag() {
    delete [] elems;
}

// Zsakba beillesztes
// Tevékenység:	Ha a zsak ures, es az elso bemeno ertek 0, meretet megnoveli egyel, majd a 0-ik erteket 0-ra allitja, es a szamlalojat megnoveli egyel.
//              Ha a zsak nem ures, eloszor vegigmegy a zsakban levo ertekeken, es ha megtalalja a beillesztendo erteket kozottuk
//              az ertek szamlalojahoz hozzaad egyet. Amennyibennem talalja, keszit egy temporalis dinamikus tombot, ebbe lementi
//              a meglevo ertekeket es azok darabszamat, majd letrehoz az eredeti dinamikus tomb helyett egy 1-el nagyobb
//              kapacitasu dinamikus tombot. Ebbe visszamenti a meglevo adatokat, torli az atmeneti dinamikus tombot, majd a kibovitett
//              helyre elmenti a beillesztendo erteket, es darabszamat 1-re valtoztatja. Mivel a tomb merete megnott, ezert a meret valtozohoz
//              hozzaad egyet, majd visszaad egy hamis erteket, mivel a zsak nem volt ures.
// Bemenõ adatok:  	Egesz valtozo (int)
// Kimenõ adatok:  	~
void Bag::insert(int e) {
    if(isEmpty() == 1) {
        meret = meret + 1;
        elems[0].darab++;
        elems[0].ertek = e;
    }else{
        bool l = 0;
        for(int i = 0; i < meret + 1; i++) {
            if(elems[i].ertek == e) {
                l = 1;
                elems[i].darab++;
            }
        }
        if(l == 0) {

            zsElem *p = elems;
            elems = new zsElem[meret+1];

            for(int i = 0; i < meret; i++) {
                elems[i].ertek = p[i].ertek;
                elems[i].darab = p[i].darab;
            }
            delete [] p;


            elems[meret].darab = 1;
            elems[meret].ertek = e;
            meret = meret + 1;
        }
    }
}

// Zsakbol torles
// Tevékenység:	Vegigmegy a zsak elemein, es ha megtalalja az adott elemet, a szamlalojabol kivon egyet.
//              Ha a szamlalo eleri a 0-t, az aktualis elemnek atadja az utolso elem adatait, majd a a dinamikus tomb meretebol levon egyet.
// Bemenõ adatok:  	Egesz valtozo (int)
// Kimenõ adatok:  	~
void Bag::erase(int e) {
    for(int i=0; i<meret; i++) {
        if (elems[i].ertek==e) {
            elems[i].darab = elems[i].darab - 1;
            if (elems[i].darab==0) {
                elems[i]=elems[meret-1];
                meret = meret - 1;
            }
        }
    }
}

// Egy elem elofordulasanak szama
// Tevékenység:	Elmegy addig, amig meg nem talalja az adott elemet, vagy ha nem szerepel az elem a zsakban, a tomb vegeig.
//              Ha benne van az elem, kiirja az elofordulasat, ha nem, kiirja hogy nincs benne. Szukseg eseten visszaadja az elofordulas szamat visszateresi
//              ertekkent.
// Bemenõ adatok:  	Egesz valtozo (int)
// Kimenõ adatok:  	Egesz valtozo (int)
int Bag::elemCount(int e) {
    bool l = 0;
    int i = 0;
    while(l == 0 && i < meret) {
        if(elems[i].ertek == e) l = 1;
        else i++;
    }
    if(l == 0) {
        std::cout << "Nincs ilyen elem" << std::endl << std::endl;
        return 0;
    }
    else std::cout << "A megadott elem darabszama: " << elems[i].darab << std::endl << std::endl;
    return elems[i].darab;
}

// Zsak kiiratasa
// Tevékenység:	Kiirja nullatol a tomb mereteig az elemek erteket es elofordulasukat, majd var egy akarmilyen inputot.
// Bemenõ adatok:  	Egesz valtozo (int)
// Kimenõ adatok:  	~
void Bag::write() {
    for(int i = 0; i < meret; i++) {
        std::cout << std::endl << "A zsak "<< i+1 << ". tagjanak erteke: "<< elems[i].ertek << " darabszama: " << elems[i].darab << std::endl;
    }
}

// Masolo konstruktor
// Tevékenység:	Megadja az uj zsaknak a masolando zsak meretet, majd lemasolja az elemeit.
// Bemenõ adatok:  	Zsak (Bag)
// Kimenõ adatok:  	Zsak (Bag)
Bag::Bag(const Bag& x) {
    meret = x.meret;
    elems = new zsElem[meret];
    for(int i=0; i<meret; ++i) elems[i] = x.elems[i];
}

// Egyenloseg operator
// Tevékenység:	Ha onmagaval hivjuk meg, visszaadja a sajat magat. Maskulonben lemasolja a meretet es az elemeket, majd visszaadja sajat magat.
// Bemenõ adatok:  	Zsak (Bag)
// Kimenõ adatok:  	Zsak (Bag)
Bag& Bag::operator=(const Bag& x) {
    if(this==&x) return *this;
    meret = x.meret;
    elems = new zsElem[meret];
    for(int i=0; i<meret; ++i) elems[i] = x.elems[i];
    return *this;
}

// 2 zsak metszete
// Tevékenység: Elindul egy kulso ciklus az egyik zsakra, egy belso a masikra. Ha az aktualis ertekeik megegyeznek, a hivott zsakba
//              illeszti az erteket, majd a kisebb darabszamot.
// Bemenõ adatok:  	2 Zsak (Bag)
// Kimenõ adatok:  	~
void Bag::intersection(Bag x, Bag a){
    for(int i = 0; i < x.meret; i++){
        for(int j = 0; j < a.meret; j++){
            if(x.elems[i].ertek == a.elems[j].ertek){
                this->insert(x.elems[i].ertek);
                if(x.elems[i].darab <= a.elems[j].darab) this->elems[meret-1].darab = x.elems[i].darab;
                else this->elems[meret-1].darab = a.elems[j].darab;
            }
        }
    }
}
