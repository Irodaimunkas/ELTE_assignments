#include "blackholemodel.h"

blackHoleModel::blackHoleModel(QObject *parent) : QObject(parent)
{
    _dataAccess = new dataAccess();
}

void blackHoleModel::newGame(int mapSize){
    _score[0] = 0;
    _score[1] = 0;
    _player = PLAYER_ONE;
    _firstDirChange = true;
    _mapSize = mapSize;
    _map.resize(mapSize);
    for(int i = 0; i < mapSize; i++){
        _map[i].resize(mapSize);
        for(int j = 0; j < mapSize; j++){
            _map[i][j].dir = NO_DIR;
            _map[i][j].type = EMPTY;
        }
    }

    for(int i = 0; i < mapSize/2; i++){
        _map[i][i].type = RED;
        _map[i][_mapSize - i - 1].type = RED;

        _map[_mapSize - i - 1][i].type = BLUE;
        _map[_mapSize - i - 1][_mapSize - i - 1].type = BLUE;
    }

    _map[_mapSize/2][_mapSize/2].type = B_HOLE;

}

void blackHoleModel::findThenMoveShips(){
    for(int i = 0; i < _mapSize; i++){
        for(int j = 0; j < _mapSize; j++){
            if(_map[i][j].type == RED || _map[i][j].type == BLUE){
                moveShip(i, j, _map[i][j]);
            }
        }
    }
    if(_player == PLAYER_ONE) _player = PLAYER_TWO;
    else _player = PLAYER_ONE;
    _firstDirChange = true;
}

void blackHoleModel::moveShip(int x, int y, Field field){
    int i = 1;
    switch(field.dir){
    case UP:
        _map[x][y].type = EMPTY;
        _map[x][y].dir = NO_DIR;
        while(x - i >= 0 && _map[x - i][y].type == EMPTY ) i++;
        if(_map[std::max(x - i, 0)][y].type == B_HOLE){
             stepOnBHole();
             return;
        }
        _map[x - i + 1][y].type = field.type;
        break;
    case DOWN:
        _map[x][y].type = EMPTY;
        _map[x][y].dir = NO_DIR;
        while(x + i < _mapSize && _map[x + i][y].type == EMPTY ) i++;
        if(_map[std::min(x + i, _mapSize - 1)][y].type == B_HOLE){
            stepOnBHole();
            return;
        }
        _map[x + i - 1][y].type = field.type;
        break;
    case RIGHT:
        _map[x][y].type = EMPTY;
        _map[x][y].dir = NO_DIR;
        while(y + i < _mapSize && _map[x][y + i].type == EMPTY ) i++;
        if(_map[x][std::min(y + i, _mapSize - 1)].type == B_HOLE){
            stepOnBHole();
            return;
        }
        _map[x][y + i - 1].type = field.type;
        break;
    case LEFT:
        _map[x][y].type = EMPTY;
        _map[x][y].dir = NO_DIR;
        while(y - i >= 0 && _map[x][y - i].type == EMPTY ) i++;
        if(_map[x][std::max(0, y - i)].type == B_HOLE){
            stepOnBHole();
            return;
        }
        _map[x][y - i + 1].type = field.type;
        break;
    }
}

void blackHoleModel::stepOnBHole(){
    switch(_player){
    case PLAYER_ONE:
        _score[0]++;
        break;
    case PLAYER_TWO:
        _score[1]++;
        break;
    }
    if(_score[0] == _mapSize/2 || _score [1] == _mapSize/2) emit endGame();
}

void blackHoleModel::shipDirChange(int row, int col){
    bool canContinue = false;

    if(_player == PLAYER_ONE && _map[row][col].type == RED) canContinue = true;
    else if(_player == PLAYER_TWO && _map[row][col].type == BLUE) canContinue = true;

    if(canContinue && (_firstDirChange || _map[row][col].dir != NO_DIR)){
        switch(_map[row][col].dir){
        case UP:
            _map[row][col].dir = RIGHT;
            break;
        case DOWN:
            _map[row][col].dir = LEFT;
            break;
        case LEFT:
            _map[row][col].dir = UP;
            break;
        case RIGHT:
            _map[row][col].dir = DOWN;
            break;
        case NO_DIR:
            _map[row][col].dir = UP;
            break;
        }
        _firstDirChange = false;
    }
}

void blackHoleModel::saveGame(){
    _dataAccess->saveGame(_map, _player, _firstDirChange, _score);
}

void blackHoleModel::loadGame(){
    _dataAccess->loadGame(_map, _player, _mapSize, _firstDirChange, _score);
}
