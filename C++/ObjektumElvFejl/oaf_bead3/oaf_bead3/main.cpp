/*
Made By: Gonda David
BIXU0S
gonda.david18@gmail.com
18/11/2017
*/

#include <iostream>
#include "monopoly.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    Game game;
    game.create("inp.txt");
    int stop;
    bool badInput = true;
    std::cout << "Please provide the stop state: ";

    //asking for end round until user gives a desired input
    while(badInput){
        try{
        std::cin >> stop;
        if(stop > game.rolls()) throw Tiles::NOT_IN_RANGE;
        else badInput = false;
        }catch(Tiles::Exceptions ex){
            if(ex == Tiles::NOT_IN_RANGE){}
            std::cout << "Went over actual rounds' number!\nPlease provide a correct number: \n";
        }
    }
    game.run(stop);
    game.write_sol();
    game.delete_tiles();
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("First round","inp.txt"){
    /*string diceRolls;
    vector<Player> players;
    vector<Tiles*> tiles;
    create("inp.txt", tiles, players, diceRolls);
    game(tiles, players, diceRolls, 3);*/
    Game game;
    game.create("inp.txt");
    game.run(3);
    CHECK(game.getOwnedProp(1,0) == 0);
    CHECK(game.getMoney(1) == 9000);
}

TEST_CASE("Middle round","inp.txt"){
    Game game;
    game.create("inp.txt");
    game.run(6);
    CHECK(game.getOwnedProp(1,0) == 0);
    CHECK(game.getMoney(1) == 5000);
    CHECK(game.getOwnedProp(2,0) == 3);
    CHECK(game.getMoney(2) == 9500);
}

TEST_CASE("Last round","inp.txt"){
    Game game;
    game.create("inp.txt");
    game.run(9);
    CHECK(game.getOwnedProp(0,0) == 4);
    CHECK(game.getMoney(0) == 7500);
    CHECK(game.getOwnedProp(1,0) == 0);
    CHECK(game.getMoney(1) == 4500);
    CHECK(game.getOwnedProp(2,0) == 3);
    CHECK(game.getMoney(2) == 9000);
}

TEST_CASE("Someone lost and lost his property","inp.txt"){
    Game game;
    game.create("inp_lost.txt");
    game.run(6);
    CHECK(game.getMoney(0) == 9000);
    CHECK(game.getOwnedProp(1,0) == 3);
    CHECK(game.getOwnedProp(1,1) == 0);
    CHECK(game.getMoney(1) == 8500);
    CHECK(game.getOwnedProp(2,0) == 4);
    CHECK(game.getMoney(2) == 8500);
}
#endif
