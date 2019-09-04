/*
Made by: Gonda Dávid
23/10/2017
Bag object/Bags' intersection/Bags' symmetric difference (task #6)
*/

#include <iostream>
#include "bag.h"

using namespace std;

//#define NORMAL_MODE
#ifdef NORMAL_MODE

//Menu object

class Menu {
public:

//Start Menu
    void Run();

private:

    Bag x;

//Write out the Menu
    void MenuWrite();

//Insert into bag
    void Insert();

//Delete from bag
    void Erase();

//Is the bag empty
    void isEmpty();

//Value's count in bag
    void count();

//Two bags' symmetric difference, input second bag after call
    void symDef();

//Two bags' intersection, input second bag after call
    void Intersection();

//Write out bag
    void Write();

//Tells if a value is in the bag or not.
    void isElem();

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
            count();
            break;
        case 5:
            symDef();
            break;
        case 6:
            Intersection();
            break;
        case 7:
            Write();
            break;
        case 8:
            isElem();
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
    cout << " 5. -Ket zsak szimmetrikus differenciaja" << endl;
    cout << " 6. -Ket zsak metszete" << endl;
    cout << " 7. -Zsak kiirasa" << endl;
    cout << " 8. -Adott elem szerepel-e a listaban" << endl;
}

void Menu::Insert(){
    char more_in = 'Y';
    while(more_in == 'Y' || more_in == 'y'){
        try{
        cout << "\nAdja meg a beillesztendo erteket: ";
        cin >> x;
        }catch(Bag::Exceptions ex){
            if(ex == Bag::INT_INPUT_STRING){
                cout << "Hiba: nem megfelelo input int tipusba input!";
                cin.clear();
                string tmp = "";
                getline(cin, tmp);
            }
        }
        cout << "\nAkar meg adatot beilleszteni?(Y-N) ";
        cin >> more_in;
    }
}

void Menu::Erase(){
    int a;
    cin >> a;
    x.erase(a);
}

void Menu::isEmpty(){
    if(x.isEmpty()) cout << "\nA zsak ures" << endl << endl;
    else cout << "\nA zsak nem ures" << endl << endl;
}

void Menu::isElem(){
    int a;
    cout << "\nAdja meg a lekerdezendo erteket: ";
    cin >> a; cout << endl;
    bool in_bag = x.isElem(a);
    if(in_bag == 1) cout << "Az elem szerepel a listaban." << endl;
    else cout << "Nincs ilyen szam!\n";
}

void Menu::count(){
    int a;
    cout << "\nAdja meg a lekerdezendo erteket: ";
    cin >> a; cout << endl;
    int _count = x.count(a);
    if(_count != 0) cout << "Az elem elemszama: " << _count;
    else cout << "Nincs ilyen szam!\n";
}

void Menu::symDef(){
    Bag y;
    char more_in = 'Y';
    cout << "Madosik zsak:\n";
    while(more_in == 'Y' || more_in == 'y'){
        try{
        cout << "\nAdja meg a beillesztendo erteket: ";
        cin >> y;
        }catch(Bag::Exceptions ex){
            if(ex == Bag::INT_INPUT_STRING){
                cout << "Hiba: nem megfelelo input int tipusba input!";
                cin.clear();
                string tmp = "";
                getline(cin, tmp);
            }
        }
        cout << "\nAkar meg adatot beilleszteni?(Y-N) ";
        cin >> more_in;
    }
    Bag symDef;
    symDef = x - y;
    cout << symDef;
}

void Menu::Intersection(){
    Bag y;
    char more_in = 'Y';
    cout << "Madosik zsak:\n";
    while(more_in == 'Y' || more_in == 'y'){
        try{
        cout << "\nAdja meg a beillesztendo erteket: ";
        cin >> y;
        }catch(Bag::Exceptions ex){
            if(ex == Bag::INT_INPUT_STRING){
                cout << "Hiba: nem megfelelo input int tipusba input!";
                cin.clear();
                string tmp = "";
                getline(cin, tmp);
            }
        }
        cout << "\nAkar meg adatot beilleszteni?(Y-N) ";
        cin >> more_in;
    }
    Bag inter;
    inter = x + y;
    cout << inter;
}

void Menu::Write(){
    cout << x;
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
            f >> test;
        }
        CHECK(test.isElem(9) == 1);
        CHECK(test.isElem(0) == 1);
        CHECK(test.isElem(3) == 1);
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
            f >> test;
        }
        test.erase(0);

        CHECK(test.isElem(9) == 1);
        CHECK(test.isElem(0) == 1);
        CHECK(test.isElem(3) == 1);
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
            f >> test;
        }
        test.erase(9);

        CHECK(test.isElem(9) == 0);
        CHECK(test.isElem(0) == 1);
        CHECK(test.isElem(3) == 1);
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
            f >> test;
        }
        test.erase(156);

        CHECK(test.isElem(9) == 1);
        CHECK(test.isElem(0) == 1);
        CHECK(test.isElem(3) == 1);
    }
    f.close();
}

TEST_CASE("ures-e ures zsakon","inp.txt"){

    Bag test;

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
            f >> test;
        }
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
            f >> test;
        }
        CHECK(test.count(9) == 1);
        CHECK(test.count(0) == 3);
        CHECK(test.count(3) == 2);
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
            f >> test;
        }
    }
    string file_name1 = "nincs_metszet.txt";

    ifstream f1(file_name1.c_str());
    if(f1.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f1.eof()){
            f1 >> test1;
        }
    }
    Bag metszet;
    metszet = test + test1;
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
            f >> test;
        }
    }
    string file_name1 = "van_metszet.txt";

    ifstream f1(file_name1.c_str());
    if(f1.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f1.eof()){
            f1 >> test1;
        }
    }
    Bag metszet;
    metszet = test + test1;

    CHECK(metszet.count(0) == 2);
    CHECK(metszet.count(3) == 1);
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
            f >> test;
        }
    }
    Bag test1;

    Bag metszet;
    metszet = test + test1;

    CHECK(metszet.isEmpty() == 1);
    f.close();
}

TEST_CASE("ket ures zsak metszete"){
    Bag test;
    Bag test1;
    Bag metszet;
    metszet = test + test1;

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
            f >> test;
        }
    }
    string file_name1 = "van_metszet.txt";

    ifstream f1(file_name1.c_str());
    if(f1.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f1.eof()){
            f1 >> test1;
        }
    }

    test1 = test;
    CHECK(test1.count(9) == 1);
    CHECK(test1.count(0) == 3);
    CHECK(test1.count(3) == 2);
    f.close();
    f1.close();
}

TEST_CASE("ket zsak szimmetrikus differenciaja, ha nincs kozos ertek","inp.txt, nincs_metszet.txt"){

    Bag test;
    Bag test1;
    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f.eof()){
            f >> test;
        }
    }
    string file_name1 = "nincs_metszet.txt";

    ifstream f1(file_name1.c_str());
    if(f1.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f1.eof()){
            f1 >> test1;
        }
    }
    Bag metszet;
    metszet = test - test1;
    CHECK(metszet.isEmpty() == 0);
    f.close();
    f1.close();
}

TEST_CASE("ket zsak szimmterikus differenciaja, ha van kozos ertek","inp.txt, van_metszet.txt"){

    Bag test;
    Bag test1;
    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f.eof()){
            f >> test;
        }
    }
    string file_name1 = "van_metszet.txt";

    ifstream f1(file_name1.c_str());
    if(f1.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f1.eof()){
            f1 >> test1;
        }
    }
    Bag metszet;
    metszet = test - test1;

    CHECK(metszet.count(0) == 1);
    CHECK(metszet.count(3) == 1);
    CHECK(metszet.count(5) == 1);
    CHECK(metszet.count(6) == 1);
    CHECK(metszet.count(7) == 2);
    CHECK(metszet.count(8) == 3);
    CHECK(metszet.count(9) == 1);
    f.close();
    f1.close();
}

TEST_CASE("egy ures, egy nem ures zsak szimmetrikus differenciaja", "inp.txt"){

    Bag test;
    string file_name = "inp.txt";

    ifstream f(file_name.c_str());
    if(f.fail()){
        cout << "Fajlnyitasi hiba!" << endl;
        exit(1);
    } else {
        while(!f.eof()){
            f >> test;
        }
    }
    Bag test1;

    Bag metszet;
    metszet = test - test1;

    CHECK(metszet.isEmpty() == 0);
    f.close();
}

TEST_CASE("ket ures zsak szimmetrikus differenciaja"){
    Bag test;
    Bag test1;
    Bag metszet;
    metszet = test - test1;

    CHECK(metszet.isEmpty() == 1);
}

#endif
