#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include "types.hpp"

int err_no = 0;

std::string field_str(const FIELD &f)
{
    switch (f)
    {
    case FIELD::CANNIBALS:
        return "cannibals";
    case FIELD::DESERT:
        return "desert";
    case FIELD::FOREST:
        return "forest";
    case FIELD::GOLD_MINE:
        return "gold mine";
    case FIELD::GRASSLAND:
        return "grassland";
    case FIELD::IRON:
        return "iron";
    case FIELD::LAKE:
        return "lake";
    case FIELD::SEA:
        return "sea";
    case FIELD::SWAMP:
        return "swamp";
    case FIELD::VILLAGE:
        return "village";
    case FIELD::WHEAT:
        return "wheat";
    }
    return "";
}

template <class T>
void assert(const T &a, const T &b, std::string error = "")
{
    if (a != b)
    {
        std::endl(std::cout);
        ++err_no;
        std::cerr << "\t" << err_no << ". error: " << error << std::endl;
        std::cerr << "\t    Expected value: " << a << ", actual value: " << b << std::endl;
    }
}

void test_field_values()
{
    std::cout << "Testing field values...";

    assert(-2, field_value(FIELD::CANNIBALS), "Invalid field value for Cannibals!");
    assert(0, field_value(FIELD::DESERT), "Invalid field value for desert!");
    assert(3, field_value(FIELD::FOREST), "Invalid field value for forest!");
    assert(5, field_value(FIELD::GOLD_MINE), "Invalid field value for gold mine!");
    assert(2, field_value(FIELD::GRASSLAND), "Invalid field value for grassland!");
    assert(2, field_value(FIELD::IRON), "Invalid field value for iron!");
    assert(3, field_value(FIELD::LAKE), "Invalid field value for lake!");
    assert(1, field_value(FIELD::SEA), "Invalid field value for sea!");
    assert(1, field_value(FIELD::SWAMP), "Invalid field value for swamp!");
    assert(6, field_value(FIELD::VILLAGE), "Invalid field value for village!");
    assert(3, field_value(FIELD::WHEAT), "Invalid field value for wheat!");

    std::cout << "done!" << std::endl;
}

void test_field_from_int()
{

    std::cout << "Testing field from int...";

    assert(field_str(FIELD::CANNIBALS), field_str(field_from_int(0)), "Invalid int to field conversion for Cannibals!");
    assert(field_str(FIELD::DESERT), field_str(field_from_int(1)), "Invalid int to field conversion for desert!");
    assert(field_str(FIELD::FOREST), field_str(field_from_int(2)), "Invalid int to field conversion for forest!");
    assert(field_str(FIELD::GOLD_MINE), field_str(field_from_int(3)), "Invalid int to field conversion for gold mine!");
    assert(field_str(FIELD::GRASSLAND), field_str(field_from_int(4)), "Invalid int to field conversion for grassland!");
    assert(field_str(FIELD::IRON), field_str(field_from_int(5)), "Invalid int to field conversion for iron!");
    assert(field_str(FIELD::LAKE), field_str(field_from_int(6)), "Invalid int to field conversion for lake!");
    assert(field_str(FIELD::SEA), field_str(field_from_int(7)), "Invalid int to field conversion for sea!");
    assert(field_str(FIELD::SWAMP), field_str(field_from_int(8)), "Invalid int to field conversion for swamp!");
    assert(field_str(FIELD::VILLAGE), field_str(field_from_int(9)), "Invalid int to field conversion for village!");
    assert(field_str(FIELD::WHEAT), field_str(field_from_int(10)), "Invalid int to field conversion for wheat!");

    std::cout << "done!" << std::endl;
}

void test_map_constructor()
{

    std::cout << "Testing Map constructor...";

    Map m(5, 4);
    assert(5, m.rows(), "Rows should be 5 for a 5x4 map!");
    assert(4, m.cols(), "Cols should be 4 for a 5x4 map!");

    Map m2(-4, -2);
    assert(0, m2.rows(), "Rows should be 0 for an invalid map!");
    assert(0, m2.cols(), "Cols should be 0 for an invalid map!");

    Map m3;
    assert(0, m3.rows(), "Rows should be 0 for an empty map!");
    assert(0, m3.cols(), "Cols should be 0 for an empty map!");

    std::cout << "done!" << std::endl;
}

void test_in_range()
{

    std::cout << "Testing Map::in_range()...";

    Map m(3, 5);
    assert(true, m.in_range(0, 0), "(0,0) should be inside a 3x5 map!");
    assert(true, m.in_range(2, 0), "(2,0) should be inside a 3x5 map!");
    assert(true, m.in_range(0, 4), "(0,4) should be inside a 3x5 map!");
    assert(true, m.in_range(2, 4), "(2,4) should be inside a 3x5 map!");
    assert(false, m.in_range(3, 5), "(3,5) should NOT be inside a 3x5 map!");
    assert(false, m.in_range(-1, -1), "(-1,-1) should NOT be inside a 3x5 map!");

    std::cout << "done!" << std::endl;
}

void test_tile_at()
{

    std::cout << "Testing Map::tile_at()...";

    std::vector<std::vector<FIELD>> map =
        {
            {FIELD::GRASSLAND, FIELD::CANNIBALS, FIELD::DESERT},
            {FIELD::GOLD_MINE, FIELD::SEA, FIELD::LAKE},
            {FIELD::IRON, FIELD::SWAMP, FIELD::WHEAT}};

    Map m(map);

    assert(field_str(FIELD::SEA), field_str(std::get<1>(m.tile_at(-1, 0))), "Wrong field stored at (-1,0)!");
    assert(field_str(FIELD::GRASSLAND), field_str(std::get<1>(m.tile_at(0, 0))), "Wrong field stored at (0,0)!");
    assert(field_str(FIELD::CANNIBALS), field_str(std::get<1>(m.tile_at(0, 1))), "Wrong field stored at (0,1)!");
    assert(field_str(FIELD::DESERT), field_str(std::get<1>(m.tile_at(0, 2))), "Wrong field stored at (0,2)!");
    assert(field_str(FIELD::GOLD_MINE), field_str(std::get<1>(m.tile_at(1, 0))), "Wrong field stored at (1,0)!");
    assert(field_str(FIELD::SEA), field_str(std::get<1>(m.tile_at(1, 1))), "Wrong field stored at (1,1)!");
    assert(field_str(FIELD::LAKE), field_str(std::get<1>(m.tile_at(1, 2))), "Wrong field stored at (1,2)!");
    assert(field_str(FIELD::IRON), field_str(std::get<1>(m.tile_at(2, 0))), "Wrong field stored at (2,0)!");
    assert(field_str(FIELD::SWAMP), field_str(std::get<1>(m.tile_at(2, 1))), "Wrong field stored at (2,1)!");
    assert(field_str(FIELD::WHEAT), field_str(std::get<1>(m.tile_at(2, 2))), "Wrong field stored at (2,2)!");
    assert(field_str(FIELD::SEA), field_str(std::get<1>(m.tile_at(3, 2))), "Wrong field stored at (3,2)!");

    std::cout << "done!" << std::endl;
}

void test_tile_in_dir()
{

    std::cout << "Testing Map::tile_in_dir()...";

    std::vector<std::vector<FIELD>> map =
        {
            {FIELD::GRASSLAND, FIELD::CANNIBALS, FIELD::DESERT},
            {FIELD::GOLD_MINE, FIELD::SEA, FIELD::LAKE},
            {FIELD::IRON, FIELD::SWAMP, FIELD::WHEAT}};

    Map m(map);
    int x = 1, y = 1;
    assert(field_str(FIELD::CANNIBALS), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::NORTH))), "Wrong field given for Ndirection!");
    assert(field_str(FIELD::LAKE), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::NORTH_EAST))), "Wrong field given for NE direction!");
    assert(field_str(FIELD::SWAMP), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::SOUTH))), "Wrong field given for S direction!");
    assert(field_str(FIELD::WHEAT), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::SOUTH_EAST))), "Wrong field given for SE direction!");
    assert(field_str(FIELD::IRON), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::SOUTH_WEST))), "Wrong field given for SW direction!");
    assert(field_str(FIELD::GOLD_MINE), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::NORTH_WEST))), "Wrong field given for NW direction!");

    std::cout << "done!" << std::endl;
}

void test_set_tile()
{

    std::cout << "Testing Map::set_tile()...";

    Map m(6, 6);
    m.set_tile(1, 1, FIELD::WHEAT);
    assert(field_str(FIELD::WHEAT), field_str(std::get<1>(m.tile_at(1, 1))), "Field at (1,1) should be changeable from SEA to WHEAT!");

    m.set_tile(-1, 1, FIELD::WHEAT);
    assert(field_str(FIELD::SEA), field_str(std::get<1>(m.tile_at(-1, 1))), "Field at (-1,1) should be not be changeable (from SEA)!");

    std::cout << "done!" << std::endl;
}

void test_radius()
{
    std::cout << "Testing Map::get_tiles_in_radius()...";

    std::vector<std::vector<FIELD>> map =
        {
            {FIELD::GRASSLAND, FIELD::CANNIBALS, FIELD::DESERT},
            {FIELD::GOLD_MINE, FIELD::SEA, FIELD::LAKE},
            {FIELD::IRON, FIELD::SWAMP, FIELD::WHEAT}};

    Map m(map);
    std::set<Tile> s = m.get_tiles_in_radius(1, 1, 1);
    assert(field_str(FIELD::CANNIBALS), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::NORTH))), "Wrong field given for NORTH direction!");
    assert(field_str(FIELD::LAKE), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::NORTH_EAST))), "Wrong field given for NORTH direction!");
    assert(field_str(FIELD::SWAMP), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::SOUTH))), "Wrong field given for SOUTH direction!");
    assert(field_str(FIELD::WHEAT), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::SOUTH_EAST))), "Wrong field given for SOUTH direction!");
    assert(field_str(FIELD::IRON), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::SOUTH_WEST))), "Wrong field given for SOUTH direction!");
    assert(field_str(FIELD::GOLD_MINE), field_str(std::get<1>(m.tile_in_direction(1, 1, DIRECTION::NORTH_WEST))), "Wrong field given for SOUTH direction!");

    std::cout << "done!" << std::endl;
}

void test_all()
{
    test_field_values();
    test_field_from_int();
    test_map_constructor();
    test_in_range();
    test_tile_at();
    test_tile_in_dir();
    test_set_tile();
    test_radius();
}

int main()
{
    test_all();
    std::endl(std::cout);
    if (err_no)
    {
        std::cout << "You gotta work in this, mate!" << std::endl;
    }
    else
    {
        std::cout << "All tests successfully passed!" << std::endl;
    }
}