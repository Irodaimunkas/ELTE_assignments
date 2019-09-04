#include <future>
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include "types.hpp"

int get_results(Coordinate coord, Map map, int range){
    std::set<Tile> results = map.get_tiles_in_radius(coord, range);

    int s = 0;
    for(std::set<Tile>::iterator it = results.begin(); it != results.end(); ++it) {
        s += tile_value(*it);
    }
    return s;
}

int main(){
    std::ifstream inFile;
    inFile.open("world.map");

    if(!inFile){
        std::cout << "Unable to open file!";
        std::exit(1);
    }

    std::vector<std::future<int>> t;
    Map map;
    int civ_num, range;

    inFile >> map;
    inFile >> civ_num >> range;

    std::vector<Coordinate> coords;

    for(int i = 0; i < civ_num; i++){
        Coordinate coord;
        inFile >> coord.x >> coord.y;
        coord.x = coord.x - 1;
        coord.y = coord.y - 1;
        coords.push_back(coord);
        //t.push_back(std::async(std::launch::async, f, coord, std::ref(map), range));
    }

    inFile.close();

    for(int i = 0; i < coords.size(); i++){
        t.push_back(std::async(std::launch::async, get_results, coords[i], std::ref(map), range));
    }

    std::vector<int> outPut;
    for(int i = 0; i < t.size(); i++){
        outPut.push_back(t[i].get());
    }

    std::ofstream outFile;
    outFile.open("output.txt");

    for(int i = 0; i < t.size(); i++){
        outFile << outPut[i] << "\n";
    }
    outFile.close();
}
