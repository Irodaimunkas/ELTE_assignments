#include <iostream>
#include <stdlib.h>

using namespace std;

//Konstansok:
const int MaxM = 100;
const int MaxN = 100;

//Rekordok:
struct tTanulo {
    int sorszam;
    int pontszam;
};

struct tVerseny {
    int resztvevok;
    tTanulo Tanulok[MaxN];
} Verseny[MaxM];

//globális változók:
int tanulok_szam, versenyek_szam;
int verseny_min_pont[MaxM];
int legszorosabb_versenyekDB;
int legszorosabb_versenyek_sorszam[MaxM];


//függvények:
void beker_1(int& N, int& M, int X[]);
void beker_2(int N, int M, tVerseny x[]);
void kiir(int db, int db_ertek[]);
void billentyure_var();
void pontszam_ellenor(int M, int& db, int db_ertek[], tVerseny x[], int pont[]);

int main()
{
    beker_1(tanulok_szam, versenyek_szam, verseny_min_pont);
    beker_2(tanulok_szam, versenyek_szam, Verseny);
    pontszam_ellenor(versenyek_szam, legszorosabb_versenyekDB, legszorosabb_versenyek_sorszam, Verseny, verseny_min_pont);
    kiir(legszorosabb_versenyekDB, legszorosabb_versenyek_sorszam);
//    billentyure_var();
    return 0;
}

void beker_1(int& N, int& M, int X[]){
    cin >> N >> M;
    cin.ignore();
    string X_temp;
    getline(cin, X_temp);
    int space = 0;
    for(int i = 0; i < M; i++){
        X[i] = atoi(X_temp.substr(space, X_temp.find(" ", space)).c_str());
        space = X_temp.find(" ", space) + 1;
    }

}

void beker_2(int N, int M, tVerseny x[]){
    for(int i = 0; i < M; i++){
        string X_temp;
        getline(cin, X_temp);
        int space = 0;
        x[i].resztvevok = atoi(X_temp.substr(space, X_temp.find(" ", space)).c_str());
        space = X_temp.find(" ", space) + 1;
        for(int j = 0; j < x[i].resztvevok; j++){
            x[i].Tanulok[j].sorszam = atoi(X_temp.substr(space, X_temp.find(" ", space)).c_str());
            space = X_temp.find(" ", space) + 1;
            x[i].Tanulok[j].pontszam = atoi(X_temp.substr(space, X_temp.find(" ", space)).c_str());
            space = X_temp.find(" ", space) + 1;
        }

    }
}

void pontszam_ellenor(int M, int& db, int db_ertek[], tVerseny x[], int pont[]){
    db = 0;
    db_ertek[db-1] = -3;
    int min_kul;
    if(x[0].Tanulok[0].pontszam >= x[0].Tanulok[1].pontszam){
        min_kul = x[0].Tanulok[0].pontszam - x[0].Tanulok[1].pontszam;
    } else min_kul = x[0].Tanulok[1].pontszam - x[0].Tanulok[0].pontszam;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < x[i].resztvevok; j++){
            for(int k = j + 1; k < x[i].resztvevok; k++){
//                cout << i << min_kul << endl;
                if(x[i].Tanulok[j].pontszam >= x[i].Tanulok[k].pontszam){
                    if( x[i].Tanulok[j].pontszam - x[i].Tanulok[k].pontszam < min_kul && x[i].Tanulok[j].pontszam - x[i].Tanulok[k].pontszam != 0){
                        min_kul = x[i].Tanulok[j].pontszam - x[i].Tanulok[k].pontszam;
                    }
                } else if( x[i].Tanulok[k].pontszam - x[i].Tanulok[j].pontszam < min_kul && x[i].Tanulok[k].pontszam - x[i].Tanulok[j].pontszam != 0){
                        min_kul = x[i].Tanulok[k].pontszam - x[i].Tanulok[j].pontszam;
                    }
            }
        }
    }
    for(int i = 0; i < M; i++){
        for(int j = 0; j < x[i].resztvevok; j++){
            for(int k = j + 1; k < x[i].resztvevok; k++){
                if(x[i].Tanulok[j].pontszam >= x[i].Tanulok[k].pontszam){
                    if( x[i].Tanulok[j].pontszam - x[i].Tanulok[k].pontszam == min_kul){
                        if(db_ertek[db-1] != i + 1){
                            db_ertek[db] = i + 1;
                            db++;
                        }
                    }
                } else if( x[i].Tanulok[k].pontszam - x[i].Tanulok[j].pontszam == min_kul){
                        if(db_ertek[db-1] != i + 1){
                            db_ertek[db] = i + 1;
                            db++;
                        }
                    }
            }
        }
    }
}

void kiir(int db, int db_ertek[]){
    cout << db << " ";
    for(int i = 0; i < db; i++){
        if(i != db-1){
            cout << db_ertek[i] << " ";
        }else cout << db_ertek[i];
    }
}
