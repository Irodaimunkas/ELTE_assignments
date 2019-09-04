#include <vector>
#include "most_frequent_specie.h"

/*
Feladat: Leggyakoribb madárfaj keresése
Tevekenyseg: Eloszor megadja az alap maximumot, indexevel egyutt, ami az elso madarfaj
elofordulasa. Ezutan egy ciklust indít 0-tól a telepulesek maximum szamaig. A ciklusban
egy ideiglenes valtozoba teszi az aktualis madarfaj elofordulasat, és ha ez nagyobb mint a meglevo
maximum, ez lesz az uj maximum. Indexet is lecsereli az aktualisra ebben az esetben.
Bemeno adat: int i_in - telepulesek maximuma
             int j_in - madarfajok maximuma
             std::vector< std::vector<int> > vec - madarfajok elofordulasa
Kimeno adat: int most_frequent_specie_i - Leggyakoribb madarfaj indexe
*/
int most_frequent_specie(int i_in, int j_in, std::vector< std::vector<int> > vec){
    int most_frequent_specie = bigger_than_zero_p(i_in, 0, vec);
    int most_frequent_specie_i = 0;
    for(int i = 0; i < j_in; i++){
        int tmp = bigger_than_zero_p(i_in, i, vec);
        if(most_frequent_specie < tmp){
            most_frequent_specie = tmp;
            most_frequent_specie_i = i;
        }
    }
    return most_frequent_specie_i;
}

/*
Feladat: Aktualis madarfaj elofordulasanak megszamlalasa
Tevekenyseg: Megadja az szamlalo valtozonak az alap 0-t. Indit egy ciklust 0-tol a telepulesek
maximumaig. Ha az aktualis madarelofordulas nagyobb mint 0, a szamlalo valtozohoz hozzaad 1-et.
Bemeno adat: int i_in - telepulesek maximuma
             int j_in - aktualis madarfaj
             std::vector< std::vector<int> > vec - madarfajok elofordulasa
Kimeno adat: int c - Madarfaj elõfordulása összesen
*/
int bigger_than_zero_p(int i_in, int j_in, std::vector< std::vector<int> > vec){
    int c = 0;
    for(int j = 0; j < i_in; j++){
        if(vec[j][j_in] > 0){
            c = c + 1;
        }
    }
    return c;
}
