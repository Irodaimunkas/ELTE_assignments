#include "types.hpp"
#include <iostream>

FIELD field_from_int(const int i)
{
    switch(i)
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
    }
    return FIELD::SEA;
}

int field_value(const FIELD &f)
{
    switch(f)
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
    }
    return 0;
}

int tile_value(const Tile &f)
{
    return field_value(f.second);
}

bool operator<(const Coordinate &a, const Coordinate &b)
{
    if(a.x < b.x){
        return true;
    }else if (a.x > b.x){
        return false;
    } else if(a.y < b.y){
        return true;
    } else{
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
    for(int i = 0; i < m.rows_; i++){
        m.map_[i].resize(m.cols_);
        for(int j = 0; j < m.cols_; j++){
            int temp;
            s >> temp;
            m.set_tile(i, j, field_from_int(temp));
        }
    }
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
    if( r > 0 && c > 0){
        rows_ = r;
        cols_ = c;
        map_.resize(r);
        for(int i = 0; i < r; i++) map_[i].resize(c);
    } else
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
    if( x < rows_ && y < cols_ && x >= 0 && y >= 0) l = true;
    return l;
}

Tile Map::tile_at(const int i, const int j) const
{
    if(in_range(i,j)) return std::make_pair(Coordinate(i, j), map_[i][j]);
    return std::make_pair(Coordinate(i, j), FIELD::SEA);
}

void Map::set_tile(const int i, const int j, const FIELD f)
{
    if( in_range(i, j) ){
        map_[i][j] = f;
    }
}

Tile Map::tile_in_direction(int x, int y, const DIRECTION d) const
{
    switch(d){
        case DIRECTION::NORTH_WEST:
            if(y % 2 == 0){
                return tile_at(x-1,y-1);
            } else{
                return tile_at(x,y-1);
            }
        case DIRECTION::NORTH:
            return tile_at(x-1,y);
        case DIRECTION::NORTH_EAST:
            if(y % 2 == 0){
                return tile_at(x-1,y+1);
            } else{
                return tile_at(x,y+1);
            }
        case DIRECTION::SOUTH_EAST:
            if(y % 2 == 0){
                return tile_at(x,y+1);
            } else{
                return tile_at(x+1,y+1);
            }
        case DIRECTION::SOUTH:
            return tile_at(x+1,y);
        case DIRECTION::SOUTH_WEST:
            if(y % 2 == 0){
                return tile_at(x,y-1);
            } else{
                return tile_at(x+1,y-1);
            }
    }
}

std::set<Tile> Map::get_tiles_in_radius(const int i, const int j, const int r) const
{
    std::set<Tile> tmp;
    Tile currTile;
    currTile = tile_at(i,j);
    tmp.insert(currTile);
    for(int k = 1; k <= r; k++){
        currTile = tile_at(i-k,j);
        tmp.insert(currTile);
        for(int j = 0; j < k; j++){
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::SOUTH_EAST);
            tmp.insert(currTile);
        }
        for(int j = 0; j < k; j++){
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::SOUTH);
            tmp.insert(currTile);
        }
        for(int j = 0; j < k; j++){
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::SOUTH_WEST);
            tmp.insert(currTile);
        }
        for(int j = 0; j < k; j++){
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::NORTH_WEST);
            tmp.insert(currTile);
        }
        for(int j = 0; j < k; j++){
            currTile = tile_in_direction(currTile.first.x, currTile.first.y, DIRECTION::NORTH);
            tmp.insert(currTile);
        }
        for(int j = 0; j < k; j++){
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
