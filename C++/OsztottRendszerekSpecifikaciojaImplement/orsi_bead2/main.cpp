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
    Map map;
    
    inFile >> map;
    inFile.close();

    FlightPath out = map.get_shortest_flightpath();

    std::ofstream outFile;
    outFile.open("output.txt");
    outFile << "From: (" << out.first.x << "," << out.first.y << ")\n" << "To: (" << out.second.x << "," << out.second.y << ")";

    outFile.close();
}
