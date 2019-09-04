#include "fieldtable.h"

FieldTable::FieldTable()
{
    _tableSize = 6;
    _playerOne.setX(3);
    _playerOne.setY(1);
    _playerTwo.setX(3);
    _playerTwo.setY(4);

    setTable();
}

void FieldTable::setTableSize(int val){
    _tableSize = val;
}

void FieldTable::setTable(){
    _tableValues.resize(_tableSize);
    for(int i = 0; i < _tableSize; i++){
        _tableValues[i].resize(_tableSize);
        for(int j = 0; j < _tableSize; j++){
            _tableValues[i][j] = NOTHING;
        }
    }
    _tableValues[_playerOne.getX()][_playerOne.getY()] = PLAYERONE;
    _tableValues[_playerTwo.getX()][_playerTwo.getY()] = PLAYERTWO;
}
