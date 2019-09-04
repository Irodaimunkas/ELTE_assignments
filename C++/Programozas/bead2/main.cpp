//1.beadandó -- 7.feladat
//Madarak életének kutatásával foglalkozó szakemberek n különböző településen
//m különböző madárfaj előfordulását tanulmányozzák. Egy adott időszakban
//megszámolták, hogy az egyes településen egy madárfajnak hány egyedével
//találkoztak. Melyik az a madárfaj, amelyik a leggyakrabban (azaz a legtöbb településen) fordult elő?
//Név: Gonda Dávid
//Neptun: BIXU0S
//email: gonda.david18@gmail.com

#include <iostream>
#include <vector>
#include <limits>
#include "input_vector_matrix.h"
#include "input_vector_matrix_f.h"
#include "most_frequent_specie.h"

using namespace std;

int main()
{
bool restart = 1;
do{
    int town_max, species_max;
    vector< vector<int> > elofordulas;
    int a;
    do{
    cout << "Datas are from file (1), or from keyboard (2): ";

    if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    cin >> a;
    }while((a != 1 && a != 2) || cin.fail());

    switch(a){
    case 1: {
            cout << "File name: ";
            string file;
            cin >> file;
            input_vector_matrix_f(town_max, species_max, elofordulas, file); break;
        }
    case 2: input_vector_matrix(town_max, species_max, elofordulas); break;
    }

    int most_frequent_bird_s;
    most_frequent_bird_s = most_frequent_specie(town_max, species_max, elofordulas);
    cout << "The most frequent bird species': " << most_frequent_bird_s + 1;

    do{

    if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    cout << "\n\nRun program again? (0 = no / 1 = yes): ";
    cin >> restart;
    }while((restart != 0 && restart != 1) || cin.fail());
}while(restart);
    return 0;
}
