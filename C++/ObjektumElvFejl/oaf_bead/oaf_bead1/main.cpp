/*
Gonda Dávid
2017.10.03.
Zsák objektum készítése/Zsák metszete (8. feladat)
*/

#include <iostream>
#include "bag.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

//Menu objektum

class Menu {
public:

//Menu inditasa
    void Run();

private:

    Bag x;

//Menu opciok kiirasaa
    void MenuWrite();

//Zsakba adatok beillesztese
    void Insert();

//Zskbol adatok torlese
    void Erase();

//Ures-e a zsak
    void isEmpty();

//Megadott adat hanyszor szerepel a zsakban
    void elemCount();

//Ket zsak metszete, a masodik zsakot ennek a hivasa utan kell megadni
    void Intersection();

//Zsak kiirasa
    void Write();

};

int main() {
    Menu m;
    m.Run();
    return 0;
}

void Menu::Run() {
    int n = 0;
    do {
        MenuWrite();
        cout << endl << "Menupont: " ;
        cin >> n;
        switch(n) {
        case 1:
            Insert();
            break;
        case 2:
            Erase();
            break;
        case 3:
            isEmpty();
            break;
        case 4:
            elemCount();
            break;
        case 5:
            Intersection();
            break;
        case 6:
            Write();
            break;
        }
    } while(n!=0);
}

void Menu::MenuWrite() {
    cout << endl << endl << " 0. -Kilepes" << endl;
    cout << " 1. -Zsakba adott elem betetele" << endl;
    cout << " 2. -Zsakba adott elem torelse" << endl;
    cout << " 3. -Ures-e a zsak" << endl;
    cout << " 4. -Adott elem elofordulasi szama" << endl;
    cout << " 5. -Ket zsak metszete" << endl;
    cout << " 6. -Zsak kiirasa" << endl;
}

void Menu::Insert(){
    int a;
    while(!cin.fail()){
        cout << "Adja meg a beillesztendo elemet(leallitashoz adjon meg egy betut):\n";
        cin >> a;
        if(!cin.fail()) x.insert(a);
    }
    cin.clear();
    cin.ignore();
}

void Menu::Erase(){
    int a;
    while(!cin.fail()){
        cout << "Adja meg a torlendo elemet(leallitashoz adjon meg egy betut):\n";
        cin >> a;
        if(!cin.fail()) x.erase(a);
    }
    cin.clear();
    cin.ignore();
}

void Menu::isEmpty(){
    if(x.isEmpty()) cout << "\nA zsak ures" << endl << endl;
    else cout << "\nA zsak nem ures" << endl << endl;
}

void Menu::elemCount(){
    int a;
    cout << "\nAdja meg a lekerdezendo erteket: ";
    cin >> a; cout << endl;
    x.elemCount(a);
}

void Menu::Intersection(){
    Bag a;
    cout << "Adja meg a masodik zsakot:\n";
    int b;
    while(!cin.fail()){
        cout << "Adja meg a beillesztendo elemet(leallitashoz adjon meg egy betut):\n";
        cin >> b;
        if(!cin.fail()) a.insert(b);
    }
    cin.clear();
    cin.ignore();

    Bag metszet;
    metszet.intersection(x, a);
    cout << endl;
    metszet.write();
    cout << endl;
}

void Menu::Write(){
    x.write();
}

#else

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("ertek beillesztese","inp.txt"){

    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        Bag test;
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
        cout << "Ertek beillesztese\n\n";
        cout << "elems[0].ertek == 9";
        CHECK(test._ertek(0) == 9);
        cout << "\nelems[0].darab == 1\n";
        CHECK(test._darab(0) == 1);
        cout << "elems[1].ertek == 0";
        CHECK(test._ertek(1) == 0);
        cout << "\nelems[1].darab == 3\n";
        CHECK(test._darab(1) == 3);
        cout << "elems[2].ertek == 3";
        CHECK(test._ertek(2) == 3);
        cout << "\nelems[2].darab == 2\n";
        CHECK(test._darab(2) == 2);
    }
    f.close();
}

TEST_CASE("ertek kivetele tobb darabos erteknel","inp.txt"){

    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        Bag test;
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
        test.erase(0);

        cout <<  "\n\nErtek kivetele, tobb darabos erteknel\n";
        cout << "\nelems[0].ertek == 9";
        CHECK(test._ertek(0) == 9);
        cout << "\nelems[0].darab == 1\n";
        CHECK(test._darab(0) == 1);
        cout << "elems[1].ertek == 0";
        CHECK(test._ertek(1) == 0);
        cout << "\nelems[1].darab == 2 //alapbol 3 darab nulla van\n";
        CHECK(test._darab(1) == 2);
        cout << "elems[2].ertek == 3";
        CHECK(test._ertek(2) == 3);
        cout << "\nelems[2].darab == 2\n";
        CHECK(test._darab(2) == 2);
    }
    f.close();
}

TEST_CASE("ertek kivetele egy darabos erteknel","inp.txt"){

    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        Bag test;
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
        test.erase(9);

        cout <<  "\n\nErtek kivetele, egy darabos erteknel\n";
        cout << "\nelems[0].ertek == 3 //itt volt a 9";
        CHECK(test._ertek(0) == 3);
        cout << "\nelems[0].darab == 2\n";
        CHECK(test._darab(0) == 2);
        cout << "elems[1].ertek == 0";
        CHECK(test._ertek(1) == 0);
        cout << "\nelems[1].darab == 3\n";
        CHECK(test._darab(1) == 3);
    }
    f.close();
}

TEST_CASE("olyan ertek kivetele, ami nincs benne","inp.txt"){

    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        Bag test;
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
        test.erase(156);
        cout << "\nOlyan ertek kivetele, ami nincs benne\n//pl: 156, semmi nem valtozik\n\n";
        cout << "elems[0].ertek == 9";
        CHECK(test._ertek(0) == 9);
        cout << "\nelems[0].darab == 1\n";
        CHECK(test._darab(0) == 1);
        cout << "elems[1].ertek == 0";
        CHECK(test._ertek(1) == 0);
        cout << "\nelems[1].darab == 3\n";
        CHECK(test._darab(1) == 3);
        cout << "elems[2].ertek == 3";
        CHECK(test._ertek(2) == 3);
        cout << "\nelems[2].darab == 2\n";
        CHECK(test._darab(2) == 2);
    }
    f.close();
}

TEST_CASE("ures-e ures zsakon","inp.txt"){

    Bag test;

    cout << "\nUres-e ures zsakon\n\n";
    cout << "test.isEmpty() == 1\n";
    CHECK(test.isEmpty() == 1);
}

TEST_CASE("Ures-e nem ures zsakon","inp.txt"){

    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        Bag test;
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
        cout << "\nUres-e nem ures zsakon\n\n";
        cout << "test.isEmpty() == 0";
        CHECK(test.isEmpty() == 0);
    }
    f.close();
}

TEST_CASE("ertek darabszamanak lekerdezese","inp.txt"){

    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        Bag test;
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
        cout << "\n\nErtek darabszamanak lekerdezese\n\n";
        cout << "\nelems.elemCount(9) == 1\n";
        CHECK(test.elemCount(9) == 1);
        cout << "\nelemCount(0) == 3\n";
        CHECK(test.elemCount(0) == 3);
        cout << "\nelems.elemCount(3) == 2\n";
        CHECK(test.elemCount(3) == 2);
        cout << "\nelems.elemCount(156) == 0\n";
        CHECK(test.elemCount(156) == 0);
    }
    f.close();
}

TEST_CASE("ket zsak metszete, ha nincs kozos ertek","inp.txt, nincs_metszet.txt"){

    Bag test;
    Bag test1;
    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
    }
    string file_name1 = "nincs_metszet.txt";

    ifstream f1(file_name1.c_str());
    if(f1.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f1.eof()){
            int a;
            f1 >> a;
            test1.insert(a);
        }
    }
    Bag metszet;
    metszet.intersection(test, test1);
    cout << "\n\nKet zsak metszete, nincs metszet\nmetszet.isEmpty() == 1\n";
    CHECK(metszet.isEmpty() == 1);
    f.close();
    f1.close();
}

TEST_CASE("ket zsak metszete, ha van kozos ertek","inp.txt, van_metszet.txt"){

    Bag test;
    Bag test1;
    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
    }
    string file_name1 = "van_metszet.txt";

    ifstream f1(file_name1.c_str());
    if(f1.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f1.eof()){
            int a;
            f1 >> a;
            test1.insert(a);
        }
    }
    Bag metszet;
    metszet.intersection(test, test1);
    cout << "\n\nKet zsak metszete, van metszet\n";
    cout << "metszet.elemCount(0) == 2\n";
    CHECK(metszet.elemCount(0) == 2);
    cout << "metszet.elemCount(3) == 1\n";
    CHECK(metszet.elemCount(3) == 1);
    f.close();
    f1.close();
}

TEST_CASE("egy ures, egy nem ures zsak metszete", "inp.txt"){

    Bag test;
    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
    }
    Bag test1;

    Bag metszet;
    metszet.intersection(test, test1);
    cout << "\n\nEgy ures, egy nem ures zsak metszete\n";
    cout << "metszet.isEmpty() == 1\n";
    CHECK(metszet.isEmpty() == 1);
    f.close();
}

TEST_CASE("ket ures zsak metszete"){
    Bag test;
    Bag test1;
    Bag metszet;
    metszet.intersection(test, test1);
    cout << "\n\nKet ures zsak metszete\n";
    cout << "metszet.isEmpty() == 1\n";
    CHECK(metszet.isEmpty() == 1);
}

TEST_CASE("ertekadas","inp.txt, van_metszet.txt"){

    Bag test;
    Bag test1;
    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f.eof()){
            int a;
            f >> a;
            test.insert(a);
        }
    }
    string file_name1 = "van_metszet.txt";

    ifstream f1(file_name1.c_str());
    if(f1.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f1.eof()){
            int a;
            f1 >> a;
            test1.insert(a);
        }
    }

    cout << "\n\nErtekadas a=b\n";
    test1 = test;
    cout << "elems[0].ertek == 9";
    CHECK(test1._ertek(0) == 9);
    cout << "\nelems[0].darab == 1\n";
    CHECK(test1._darab(0) == 1);
    cout << "elems[1].ertek == 0";
    CHECK(test1._ertek(1) == 0);
    cout << "\nelems[1].darab == 3\n";
    CHECK(test1._darab(1) == 3);
    cout << "elems[2].ertek == 3";
    CHECK(test1._ertek(2) == 3);
    cout << "\nelems[2].darab == 2\n";
    CHECK(test1._darab(2) == 2);
    f.close();
    f1.close();
}

#endif
