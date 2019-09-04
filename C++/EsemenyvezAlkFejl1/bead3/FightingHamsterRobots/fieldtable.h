#ifndef FIELDTABLE_H
#define FIELDTABLE_H

#include <QObject>
#include "player.h"
#include <QVector>

enum FieldType { PLAYERONE, PLAYERTWO, NOTHING };

class FieldTable
{
private:
    int _tableSize;
    Player _playerOne, _playerTwo;
    QVector<QVector<FieldType> > _tableValues;

public:
    FieldTable();

    Player &playerOne() { return _playerOne; }
    Player &playerTwo() { return _playerTwo; }
    int size() { return _tableSize; }
    QVector<QVector<FieldType> > getVals() { return _tableValues; }

    void setValue(int x, int y, FieldType val){ _tableValues[x][y] = val; }
    void setTableSize(int val);
    void setTable();
};

#endif // FIELDTABLE_H
