#include <future>
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include "types.hpp"

int main()
{
    auto start = std::chrono::system_clock::now();

    std::ifstream inFile;
    inFile.open("world.map");

    if (!inFile)
    {
        std::cout << "Unable to open file!";
        std::exit(1);
    }
    Map map;

    inFile >> map;

    int traderCount;
    inFile >> traderCount;
    std::vector<trader> traders;
    traders.resize(traderCount);
    for (int i = 0; i < traderCount; i++)
    {
        inFile >> traders[i][0] >> traders[i][1] >> traders[i][2] >> traders[i][3] >> traders[i][4] >> traders[i][5];
    }
    inFile.close();
    
    map.calculate_trades(traders);

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << elapsed.count() << '\n';
}