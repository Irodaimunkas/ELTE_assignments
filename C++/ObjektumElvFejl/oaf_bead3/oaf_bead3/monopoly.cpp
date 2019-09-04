/*
Made By: Gonda David
BIXU0S
gonda.david18@gmail.com
18/11/2017
*/
#include "monopoly.h"
#include <iostream>

/*
If player can pay the service without going under zero, the function subtracts his money by the tiles "service money".
If the player can't pay for the service, he lost.
*/
void Service::moneyExchange(std::vector<Player>& a, int i){
    if(a[i].money - owedMoney >= 0){
        a[i].money = a[i].money - owedMoney;
    } else a[i].lost = true;
}

//The function adds the tiles "luck money" to the players money.
void Luck::moneyExchange(std::vector<Player>& a, int i){
    a[i].money = a[i].money + luckyMoney;
}

/*
If the tile is owned by someone and built upon, the player gives 2000 to the owner, if it's only owned, the player gives 500 to the owner.
If neither, then the player buys the tile or not, depending on his/her strategy. If the player owns the tile already, he can built on it,
depending on his/her strategy. (G - Greedy, C - Cautious, T - Tactical)
*/
void Property::moneyExchange(std::vector<Player>& a, int i){
    if(owned){
        if(builtOn){
            if(a[i].money - 2000 >= 0){
                a[i].money-=2000;
                int j = 0;
                while(a[j].name != owner) j++;
                a[j].money+=2000;
            } else a[i].lost = true;
        } else if(owner == a[i].name && builtOn == false){
           switch(a[i].type){
            case 'G':
                if(a[i].money - 4000 >= 0){
                    builtOn = true;
                    a[i].money = a[i].money - 4000;
                }
                break;
            case 'C':
                if(a[i].money - 4000 >= 0 && a[i].money - 4000 >= a[i].money/2){
                    builtOn = true;
                    a[i].money = a[i].money - 4000;
                }
                break;
            case 'T':
                if(a[i].counter % 2 == 0 && a[i].money - 4000 >= 0){
                    builtOn = true;
                    a[i].money = a[i].money - 4000;
                    a[i].counter++;
                } else a[i].counter++;
                break;
            }
        } else {
            if(a[i].money - 500 >= 0){
                a[i].money-=500;
                int j = 0;
                while(a[j].name != owner) j++;
                a[j].money+=500;
            } else a[i].lost = true;
        }
    } else{
        switch(a[i].type){
        case 'G':
            if(a[i].money - 1000 >= 0){
                owned = true;
                owner = a[i].name;
                a[i].money = a[i].money - 1000;
                a[i].ownedProperties.push_back(a[i].placeOnMap);
            }
            break;
        case 'C':
            if(a[i].money - 1000 >= 0 && a[i].money - 1000 >= a[i].money/2){
                owned = true;
                owner = a[i].name;
                a[i].money = a[i].money - 1000;
                a[i].ownedProperties.push_back(a[i].placeOnMap);
            }
            break;
        case 'T':
            if(a[i].counter % 2 == 0 && a[i].money - 1000 >= 0){
                owned = true;
                owner = a[i].name;
                a[i].money = a[i].money - 1000;
                a[i].counter++;
                a[i].ownedProperties.push_back(a[i].placeOnMap);
            } else a[i].counter++;
            break;
        }
    }
}

void Game::run(int stop){
    //game
    bool gameEnd = false;
    int round = 1;
    int j = 0;
    int diceRoll;
    std::stringstream in;
    in.str(diceRolls);
    while(round <= stop && !gameEnd && !in.eof()){
        in >> diceRoll;
        players[j].placeOnMap = (players[j].placeOnMap + diceRoll) % (int)tiles.size();
        std::cout << players[j].name << " | before: " << players[j].money << " | after: ";
        tiles[players[j].placeOnMap]->moneyExchange(players, j);
        std::cout << players[j].money << " | " << players[j].placeOnMap + 1 << std::endl;
        if(players[j].lost){
            for(int k = 0; k < (int)players[j].ownedProperties.size(); k++){
                delete tiles[k];
                tiles[k] = new Property;
            }
        }
        do{
        j = (j + 1) % (int)players.size();
        }while(players[j].lost);
        round++;
    }
}

void Game::create(const std::string &str){
    std::ifstream f(str.c_str());
    if(f.fail()) {
        std::cout << "Nincs meg a fájl\n";
        exit(1);
    }

   // create tiles
    int n;
    f >> n;
    tiles.resize(n);
    for(int i=0; i<n; ++i){
        char type;
        int money;
        f >> type;
        switch(type){
        case 'P' :
            tiles[i] = new Property;
            break;
        case 'S' :
            f >> money;
            tiles[i] = new Service(money);
            break;
        case 'L' :
            f >> money;
            tiles[i] = new Luck(money);
            break;
        }
    }

   // Create players
    int m;
    f >> m;
    players.resize(m);
    for(int j=0; j<m; ++j) f >> players[j].name >> players[j].type;
    getline(f,diceRolls);
    getline(f,diceRolls);
}

void Game::write_sol(){
    std::cout << std::endl;
    for(int i = 0; i < (int)players.size(); i++){
        std::cout << players[i].name << " " << players[i].money << std::endl;
        if(!players[i].lost){
            for(int j = 0; j < (int)players[i].ownedProperties.size(); j++){
                std::cout << players[i].ownedProperties[j] + 1 << " ";
            }
        } else std::cout << "Lost";
        std::cout << std::endl;
    }
}

void Game::delete_tiles(){
    //delete tiles
    for(int i = 0; i < (int)tiles.size(); i++) delete tiles[i];
}

int Game::getMoney(int index){
    return players[index].money;
}

int Game::getOwnedProp(int index, int counter){
    return players[index].ownedProperties[counter];
}

int Game::rolls(){
    return (diceRolls.length()/2)+1;
}
