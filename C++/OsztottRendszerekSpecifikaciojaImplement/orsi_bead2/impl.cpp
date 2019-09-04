#include "types.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <future>

FIELD field_from_int(const int i)
{
    switch (i)
    {
    case 0:
        return FIELD::CANNIBALS;
    case 1:
        return FIELD::DESERT;
    case 2:
        return FIELD::FOREST;
    case 3:
        return FIELD::GOLD_MINE;
    case 4:
        return FIELD::GRASSLAND;
    case 5:
        return FIELD::IRON;
    case 6:
        return FIELD::LAKE;
    case 7:
        return FIELD::SEA;
    case 8:
        return FIELD::SWAMP;
    case 9:
        return FIELD::VILLAGE;
    case 10:
        return FIELD::WHEAT;
    case 11:
        return FIELD::CITY;
    }
    return FIELD::SEA;
}

int field_value(const FIELD &f)
{
    switch (f)
    {
    case FIELD::CANNIBALS:
        return -2;
    case FIELD::DESERT:
        return 0;
    case FIELD::FOREST:
        return 3;
    case FIELD::GOLD_MINE:
        return 5;
    case FIELD::GRASSLAND:
        return 2;
    case FIELD::IRON:
        return 2;
    case FIELD::LAKE:
        return 3;
    case FIELD::SEA:
        return 1;
    case FIELD::SWAMP:
        return 1;
    case FIELD::VILLAGE:
        return 6;
    case FIELD::WHEAT:
        return 3;
    case FIELD::CITY:
        return 10;
    }
    return 0;
}

int tile_value(const Tile &f)
{
    return field_value(f.second);
}

bool operator<(const Coordinate &a, const Coordinate &b)
{
    if (a.x < b.x)
    {
        return true;
    }
    else if (a.x > b.x)
    {
        return false;
    }
    else if (a.y < b.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
std::ostream& operator<<(std::ostream& s, const FIELD& f)
{
    switch (f)
    {
        case FIELD::CANNIBALS:
            s << "cannibals";
            break;
        case FIELD::DESERT:
            s << "desert";
            break;
        case FIELD::FOREST:
            s << "forest";
            break;
        case FIELD::GOLD_MINE:
            s << "gold mine";
            break;
        case FIELD::GRASSLAND:
            s << "grassland";
            break;
        case FIELD::IRON:
            s << "iron";
            break;
        case FIELD::LAKE:
            s << "lake";
            break;
        case FIELD::SEA:
            s << "sea";
            break;
        case FIELD::SWAMP:
            s << "swamp";
            break;
        case FIELD::VILLAGE:
            s << "village";
            break;
        case FIELD::WHEAT:
            s << "wheat";
            break;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const DIRECTION& d)
{
    switch(d){
        case DIRECTION::NORTH_WEST:
            s << "NW";
            break;
        case DIRECTION::NORTH:
            s << "N";
            break;
        case DIRECTION::NORTH_EAST:
            s << "NE";
            break;
        case DIRECTION::EAST: //not used here
            s << "E";
            break;
        case DIRECTION::SOUTH_EAST:
            s << "SE";
            break;
        case DIRECTION::SOUTH:
            s << "S";
            break;
        case DIRECTION::SOUTH_WEST:
            s << "SW";
            break;
        case DIRECTION::WEST: //not used here
            s << "W";
            break;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const Coordinate& p)
{
    s << "(" << p.x << ", " << p.y << ")";
    return s;
}

std::istream& operator>>(std::istream& s, Coordinate& p)
{
    s >> p.x >> p.y;
    p.x = p.x - 1;
    p.y = p.y - 1;
    return s;
}

std::ostream& operator<<(std::ostream& s, const Tile& t)
{
    s << "Tile coordinate: " << t.first << "\n";
    s << "Tile field: " << t.second << "\n";
    return s;
}
*/
std::istream &operator>>(std::istream &s, Map &m)
{
    s >> m.rows_ >> m.cols_;
    m.map_.resize(m.rows_);
    for (int i = 0; i < m.rows_; i++)
    {
        m.map_[i].resize(m.cols_);
        for (int j = 0; j < m.cols_; j++)
        {
            int temp;
            s >> temp;
            m.set_tile(i, j, field_from_int(temp));
        }
    }
    
    m.find_cities();
    return s;
}

Map::Map()
{
    rows_ = 0;
    cols_ = 0;
    map_.resize(0);
}

Map::Map(const int r, const int c)
{
    if (r > 0 && c > 0)
    {
        rows_ = r;
        cols_ = c;
        map_.resize(r);
        for (int i = 0; i < r; i++)
            map_[i].resize(c);
    }
    else
    {
        rows_ = 0;
        cols_ = 0;
        map_.resize(0);
    }
}

int Map::rows() const
{
    return rows_;
}

int Map::cols() const
{
    return cols_;
}

bool Map::in_range(const int x, const int y) const
{
    bool l = false;
    if (x < rows_ && y < cols_ && x >= 0 && y >= 0)
        l = true;
    return l;
}

Tile Map::tile_at(const int i, const int j) const
{
    if (in_range(i, j))
        return std::make_pair(Coordinate(i, j), map_[i][j]);
    return std::make_pair(Coordinate(i, j), FIELD::SEA);
}

void Map::set_tile(const int i, const int j, const FIELD f)
{
    if (map_[i][j] == FIELD::CITY)
    {
        cities_.erase(Coordinate(i, j));
    }
    if (in_range(i, j))
    {
        map_[i][j] = f;
    }
    if (map_[i][j] == FIELD::CITY)
    {
        cities_.insert(Coordinate(i, j));
    }
}

Tile Map::tile_in_direction(int x, int y, const DIRECTION d) const
{
    switch (d)
    {
    case DIRECTION::NORTH_WEST:
        if (y % 2 == 0)
        {
            return tile_at(x - 1, y - 1);
        }
        else
        {
            return tile_at(x, y - 1);
        }
    case DIRECTION::NORTH:
        return tile_at(x - 1, y);
    case DIRECTION::NORTH_EAST:
        if (y % 2 == 0)
        {
            return tile_at(x - 1, y + 1);
        }
        else
        {
            return tile_at(x, y + 1);
        }
    case DIRECTION::SOUTH_EAST:
        if (y % 2 == 0)
        {
            return tile_at(x, y + 1);
        }
        else
        {
            return tile_at(x + 1, y + 1);
        }
    case DIRECTION::SOUTH:
        return tile_at(x + 1, y);
    case DIRECTION::SOUTH_WEST:
        if (y % 2 == 0)
        {
            return tile_at(x, y - 1);
        }
        else
        {
            return tile_at(x + 1, y - 1);
        }
    }
}

std::set<Tile> Map::get_tiles_in_radius(const int i, const int j, const int r) const
{
    std::set<Tile> tmp;
    Tile currTile;
    currTile = tile_at(i, j);
    tmp.insert(currTile);
    for (int k = 1; k <= r; k++)
    {
        currTile = tile_at(i - k, j);
        tmp.insert(currTile);
        for (int j = 0; j < k; j++)
        {
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::SOUTH_EAST);
            tmp.insert(currTile);
        }
        for (int j = 0; j < k; j++)
        {
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::SOUTH);
            tmp.insert(currTile);
        }
        for (int j = 0; j < k; j++)
        {
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::SOUTH_WEST);
            tmp.insert(currTile);
        }
        for (int j = 0; j < k; j++)
        {
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::NORTH_WEST);
            tmp.insert(currTile);
        }
        for (int j = 0; j < k; j++)
        {
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::NORTH);
            tmp.insert(currTile);
        }
        for (int j = 0; j < k; j++)
        {
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::NORTH_EAST);
            tmp.insert(currTile);
        }
    }
    return tmp;
    /*
    std::set<Tile> s;
    return s;
    */
}

/**
  * new functions for 2nd assignment
  */

void Map::find_cities()
{
    cities_.clear();
    for (int i = 0; i < rows(); i++)
    {
        for (int j = 0; j < cols(); j++)
        {
            if (map_[i][j] == FIELD::CITY)
            {
                cities_.insert(Coordinate(i, j));
            }
        }
    }
}

double Map::get_length(const FlightPath &p) const
{
    return sqrt(pow(p.second.x - p.first.x, 2) + pow(p.second.y - p.first.y, 2));
}

double Map::get_distance(const City &a, const City &b) const
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

FlightPath Map::closest_brute_force(const std::vector<City> &cities) const
{
    Coordinate val1 = cities[0];
    Coordinate val2 = cities[1];
    for (int i = 0; i < cities.size() - 1; i++)
    {
        for (int j = i + 1; j < cities.size(); j++)
        {
            if (get_distance(val1, val2) > get_distance(cities[i], cities[j]))
            {
                val1 = cities[i];
                val2 = cities[j];
            }
        }
    }
    return {val1, val2};
}

FlightPath Map::find_shortest(const std::vector<City> &x_cities, const std::vector<City> &y_cities) const
{
    if (x_cities.size() < 4)
    {
        return closest_brute_force(x_cities);
    }
    else
    {
        std::vector<City> on_left_x = std::vector<City>(x_cities.begin(), std::next(x_cities.begin(), (x_cities.size() / 2)));
        std::vector<City> on_right_x = std::vector<City>(std::next(x_cities.begin(), (x_cities.size() / 2)), x_cities.end());
        int middle_x = on_right_x[0].x;

        std::vector<City> on_left_y;
        std::vector<City> on_right_y;

        for (int i = 0; i < y_cities.size(); i++)
        {
            if (y_cities[i].x <= middle_x)
            {
                on_left_y.push_back(y_cities[i]);
            }
            else
            {
                on_right_y.push_back(y_cities[i]);
            }
        }
        std::future<FlightPath> path = std::async(std::launch::async, &Map::find_shortest, this, std::cref(on_left_x), std::cref(on_left_y));
        FlightPath rightMin = find_shortest(on_right_x, on_right_y);
        FlightPath leftMin = path.get();
        FlightPath minPath;
        if (get_length(leftMin) < get_length(rightMin))
        {
            minPath = leftMin;
        }
        else
        {
            minPath = rightMin;
        }
        std::vector<City> stripe;
        for (int i = 0; i < y_cities.size(); i++)
        {
            if (abs(y_cities[i].x - middle_x) < get_length(minPath))
            {
                stripe.push_back(y_cities[i]);
            }
        }
        if (stripe.size() > 1)
        {
            for (int i = 0; i < stripe.size() - 1; i++)
            {
                for (int j = i + 1; j < stripe.size(); j++)
                {
                    if (get_distance(stripe[i], stripe[j]) < get_length(minPath))
                    {
                        minPath = FlightPath(stripe[i], stripe[j]);
                    }
                }
            }
        }
        return minPath;
    }
}

std::set<City> Map::get_cities() const
{
    return cities_;
}

bool compareX(Coordinate &a, Coordinate &b){
    return a.x < b.x;
}

bool compareY(Coordinate &a, Coordinate &b){
    return a.y < b.y;
}

FlightPath Map::get_shortest_flightpath() const
{
    std::vector<City> byX(cities_.begin(), cities_.end());
    std::vector<City> byY(cities_.begin(), cities_.end());
    std::sort(byX.begin(), byX.end(), compareX);
    std::sort(byY.begin(), byY.end(), compareY);
    return find_shortest(byX, byY);
}
