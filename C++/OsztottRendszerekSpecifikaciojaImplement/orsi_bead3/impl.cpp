#include "types.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <iterator>
#include <cmath>
#include <future>

FIELD field_from_int(const int i)
{
    return static_cast<FIELD>(i);
}

int tile_value(const Tile &f)
{
    return field_value(std::get<1>(f));
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
    default:
        return 10;
    }
}

std::ostream &operator<<(std::ostream &s, const FIELD &f)
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
    case FIELD::CITY:
        s << "city";
        break;
    }
    return s;
}

std::ostream &operator<<(std::ostream &s, const DIRECTION &d)
{
    switch (d)
    {
    case DIRECTION::NORTH_WEST:
        s << "NW";
        break;
    case DIRECTION::NORTH:
        s << "N";
        break;
    case DIRECTION::NORTH_EAST:
        s << "NE";
        break;
    case DIRECTION::EAST:
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
    case DIRECTION::WEST:
        s << "W";
        break;
    }
    return s;
}

bool operator<(const Coordinate &a, const Coordinate &b)
{
    if (a.x < b.x)
        return true;
    if (a.x > b.x)
        return false;

    return a.y <= b.y;
}

std::ostream &operator<<(std::ostream &s, const Coordinate &p)
{
    s << "(" << p.x << "," << p.y << ")";
    return s;
}
std::istream &operator>>(std::istream &s, Coordinate &p)
{
    s >> p.x >> p.y;
    return s;
}

std::ostream &operator<<(std::ostream &s, const Tile &t)
{
    s << std::get<0>(t) << "-" << std::get<1>(t);
    return s;
}

std::istream &operator>>(std::istream &s, Map &m)
{
    int r, c;
    s >> r >> c;
    m = Map(r, c);
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            int f;
            s >> f;
            m.set_tile(i, j, field_from_int(f));
        }
    }
    return s;
}

Map::Map() : rows_(0), cols_(0)
{
}

Map::Map(const int r, const int c)
{
    rows_ = r > 0 ? r : 0;
    cols_ = c > 0 ? c : 0;
    map_ = std::vector<std::vector<FIELD>>(rows_, std::vector<FIELD>(cols_, FIELD::SEA));
}

bool Map::in_range(const int x, const int y) const
{
    return x >= 0 && x < rows_ && y >= 0 && y < cols_;
}

Tile Map::tile_at(const int i, const int j) const
{
    FIELD f = in_range(i, j) ? map_[i][j] : FIELD::SEA;
    return std::make_pair(Coordinate(i, j), f);
}

void Map::set_tile(const int i, const int j, const FIELD f)
{
    if (in_range(i, j))
    {
        map_[i][j] = f;
        if (f == FIELD::CITY)
        {
            cities_.push_back(City(i, j));
        }
    }
}

std::set<Tile> Map::get_tiles_in_radius(const int i, const int j, const int r) const
{
    std::array<DIRECTION, 6> dirs = {
        DIRECTION::SOUTH_EAST,
        DIRECTION::SOUTH,
        DIRECTION::SOUTH_WEST,
        DIRECTION::NORTH_WEST,
        DIRECTION::NORTH,
        DIRECTION::NORTH_EAST,
    };
    std::set<Tile> s;
    int x = i;

    s.insert(tile_at(x, j)); //origo

    for (int i = 1; i <= r; ++i)
    {
        --x;
        Tile actual = tile_at(x, j);
        for (const auto &dir : dirs)
        {
            for (int j = 0; j < i; ++j)
            {
                actual = tile_in_direction(actual, dir);
                s.insert(actual);
            }
        }
    }
    return s;
}

//"odd-q" vertical layout, odd columns shoved down
Tile Map::tile_in_direction(int x, int y, const DIRECTION d) const
{
    switch (d)
    {
    case DIRECTION::NORTH_WEST:
        --y;
        if (y & 1)
        {
            --x;
        }
        break;
    case DIRECTION::NORTH:
        --x;
        break;
    case DIRECTION::NORTH_EAST:
        ++y;
        if (y & 1)
        {
            --x;
        }
        break;
    case DIRECTION::SOUTH_EAST:
        if (y & 1)
        {
            ++x;
        }
        ++y;
        break;
    case DIRECTION::SOUTH:
        ++x;
        break;
    case DIRECTION::SOUTH_WEST:
        if (y & 1)
        {
            ++x;
        }
        --y;
        break;
    default:
        break;
    }
    return tile_at(x, y);
}

int Map::rows() const
{
    return rows_;
}

int Map::cols() const
{
    return cols_;
}
/**
  * new functions for 2nd assignment
  */
void Map::find_cities()
{
    cities_.clear();
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            if (map_[i][j] == FIELD::CITY)
            {
                cities_.push_back(City(i, j));
            }
        }
    }
}

std::vector<City> Map::get_cities() const
{
    return cities_;
}

double Map::get_length(const FlightPath &p) const
{
    return get_distance(std::get<0>(p), std::get<1>(p));
}

double Map::get_distance(const City &a, const City &b) const
{
    int x = b.x - a.x;
    int y = b.y - a.y;
    return std::sqrt(x * x + y * y);
}

FlightPath Map::closest_brute_force(const std::vector<City> &cities) const
{
    if (cities.size() == 0)
    {
        return {{0, 0}, {0, 0}};
    }
    else if (cities.size() == 1)
    {
        return {cities[0], cities[0]};
    }
    else if (cities.size() == 2)
    {
        return {cities[0], cities[1]};
    }

    double abDist = get_distance(cities[0], cities[1]);
    double acDist = get_distance(cities[0], cities[2]);
    double bcDist = get_distance(cities[1], cities[2]);

    double min_dist = std::min(std::min(abDist, acDist), bcDist);
    if (min_dist == abDist)
    {
        return {cities[0], cities[1]};
    }
    else if (min_dist == acDist)
    {
        return {cities[0], cities[2]};
    }
    else
    {
        return {cities[1], cities[2]};
    }
}

FlightPath Map::find_shortest(const std::vector<City> &x_cities, const std::vector<City> &y_cities) const
{
    int city_count = x_cities.size();
    if (city_count <= 3)
    {
        return closest_brute_force(x_cities);
    }

    auto iter = x_cities.begin();
    std::advance(iter, (city_count / 2));
    std::vector<City> on_left_x(x_cities.begin(), iter);
    std::vector<City> on_right_x(iter, x_cities.end());

    int middleX = on_right_x[0].x;

    std::vector<City> on_left_y;
    std::vector<City> on_right_y;

    for (auto it : y_cities)
    {
        if (it.x <= middleX)
        {
            on_left_y.push_back(it);
        }
        else
        {
            on_right_y.push_back(it);
        }
    }

    std::future<FlightPath> fp_asnyc = std::async(std::launch::async, [&]() {
        return find_shortest(on_left_x, on_left_y);
    });

    auto fp_1 = find_shortest(on_right_x, on_right_y);
    auto fp_2 = fp_asnyc.get();

    FlightPath min_path = get_length(fp_1) <= get_length(fp_2) ? fp_1 : fp_2;

    std::vector<City> stripe;
    std::copy_if(y_cities.begin(), y_cities.end(), std::back_inserter(stripe),
                 [&](const City &c) {
                     return std::abs(middleX - c.x) < get_length(min_path);
                 });

    auto result = min_path;

    if (stripe.size() > 0)
    {
        for (iter = stripe.begin(); iter != stripe.end(); ++iter)
        {
            for (auto it = iter + 1; it != stripe.end() && ((it->y - iter->y) < get_length(min_path)); ++it)
            {
                auto new_dist = get_distance(*it, *iter);
                if (new_dist < get_length(result))
                {
                    result = {*it, *iter};
                }
            }
        }
    }
    return result;
}

FlightPath Map::get_shortest_flightpath() const
{
    std::vector<City> x_cities(cities_.begin(), cities_.end());
    std::sort(x_cities.begin(), x_cities.end(),
              [](const City &a, const City &b) {
                  return a.x < b.x;
              });

    std::vector<City> y_cities(cities_.begin(), cities_.end());
    std::sort(y_cities.begin(), y_cities.end(),
              [](const City &a, const City &b) {
                  return a.y < b.y;
              });

    return find_shortest(x_cities, y_cities);
}

//3rd assignment
void Map::calculate_trades(std::vector<trader> &traders)
{
    find_cities();
    int c = cities_.size();

    std::vector<Pipe<trader>> pipes(c + 1);
    std::vector<std::thread> working_cities;

    for (int i = 0; i < c; i++)
    {
        auto f = [&](int j) { city_trade(cities_[j], traders.size(), pipes[j], pipes[j + 1]); };
        working_cities.push_back(std::thread(f, i));
    }
    for (int i = 0; i < traders.size(); i++)
    {
        pipes[0].push(traders[i]);
//        std::cout << i << "\n";
    }
    
    std::ofstream outFile;
    outFile.open("output.txt");
    for (int i = 0; i < traders.size(); i++)
    {
        trader out = pipes[pipes.size() - 1].pop();
        for (int j = 0; j < out.size() - 1; j++)
        {
            outFile << out[j] << " ";
        }
        outFile << "\n";
    }
    for (int i = 0; i < c; i++)
    {
     //   std::cout << "asd: " << i << "\n";
        working_cities[i].join();
    }
}

bool is_useful_field(FIELD f)
{
    switch (f)
    {
    case FIELD::FOREST:
        return true;
    case FIELD::GOLD_MINE:
        return true;
    case FIELD::IRON:
        return true;
    case FIELD::LAKE:
        return true;
    case FIELD::WHEAT:
        return true;
    }
    return false;
}

int get_field_index(FIELD f)
{
    switch (f)
    {
    case FIELD::FOREST:
        return 0;
    case FIELD::GOLD_MINE:
        return 1;
    case FIELD::IRON:
        return 2;
    case FIELD::LAKE:
        return 3;
    case FIELD::WHEAT:
        return 4;
    }
    return -1;
}

bool have_sellable(stock &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] > 0)
            return true;
    }
    return false;
}

void Map::city_trade(const City &city, int count, Pipe<trader> &from, Pipe<trader> &to) const
{
    std::set<Tile> s = get_tiles_in_radius(city, 2);
    std::vector<Tile> radTwoCities(s.begin(), s.end());
    std::array<int, 5> resources;
    resources.fill(0);
    for (int i = 0; i < radTwoCities.size(); i++)
    {
        if (is_useful_field(radTwoCities[i].second))
        {
            resources[get_field_index(radTwoCities[i].second)]++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        trader in = from.pop();
        int mi = in[in.size() - 1];
        /*
        std::vector<bool> available_stock(5);
        for (int j = 0; j < resources.size(); j++)
        {
            if (resources[i] > mi)
            {
                available_stock[i] = true;
            }
            else
            {
                available_stock[i] = false;
            }
        }*/
        if (have_sellable(resources))
        {
            int cityWant = 0;
            while ((cityWant < (in.size() - 1)) && ((resources[cityWant] > 0) || (in[cityWant] == 0)))
            {
                cityWant++;
            }

            if (cityWant < (in.size() - 1))
            {
                bool canTrade = false;
                int traderWant = 0;
                while (traderWant < (in.size() - 1))
                {
                    if (resources[traderWant] > mi)
                    {
                        canTrade = true;
                        break;
                    }
                    traderWant++;
                }
                if (canTrade)
                {
                    in[traderWant] += mi;
                    resources[traderWant] -= mi;

                    in[cityWant] -= 1;
                    resources[cityWant] += 1;
                }
            }
        }
        to.push(in);
    }
}
