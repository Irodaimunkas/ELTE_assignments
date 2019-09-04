/*
Made By: Gonda David
BIXU0S
gonda.david18@gmail.com
18/11/2017
*/
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>

//Players' struct
struct Player{
    char type;
    int money = 10000;
    std::vector<int> ownedProperties;
    std::string name;
    bool lost = false;
    int counter = 0;
    int placeOnMap = -1;
};

//Tiles class for saving inputs
class Tiles{
public:
    enum Exceptions { NOT_IN_RANGE };
    virtual void moneyExchange(std::vector<Player>& a, int i) = 0;
    virtual ~Tiles() {};
};

class Service : public Tiles{
public:
    Service(int oMoney):owedMoney(oMoney) {};
    void moneyExchange(std::vector<Player>& a, int i) override;
private:
    int owedMoney;
};

class Property : public Tiles{
public:
    void moneyExchange(std::vector<Player>& a, int i) override;
private:
    std::string owner = "noone";
    bool builtOn = false;
    bool owned = false;
};

class Luck : public Tiles{
public:
    Luck(int lMoney):luckyMoney(lMoney) {};
    void moneyExchange(std::vector<Player>& a, int i) override;
private:
    int luckyMoney;
};

class Game{
private:
    std::vector<Tiles*> tiles;
    std::vector<Player> players;
    std::string diceRolls;
public:
    void create(const std::string &str);
    void run(int stop);
    void write_sol();
    void delete_tiles();
    int getMoney(int index);
    int getOwnedProp(int index, int counter);
    int rolls();
};
