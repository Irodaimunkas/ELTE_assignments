#ifndef BLACKHOLEMODEL_H
#define BLACKHOLEMODEL_H

#include <QObject>
#include <QVector>
#include "dataaccess.h"

class blackHoleModel : public QObject
{
    Q_OBJECT
public:
    blackHoleModel(dataAccess *dataAccessMock);
    void newGame(int mapSize);
    void findThenMoveShips();
    void shipDirChange(int row, int col);

    void saveGame();
    void loadGame();


    //setters/getters
    void setFieldType(int x, int y, Type type) { _map[x][y].type = type; }
    void setFieldDir(int x, int y, Direction dir) { _map[x][y].dir = dir; }
    void setPlayer(Player player) { _player = player; }
    void setFirstDirChange(bool change) { _firstDirChange = change; }
    Type getFieldType(int x, int y) { return _map[x][y].type; }
    Direction getFieldDir(int x, int y) { return _map[x][y].dir; }
    Player getPlayer() { return _player; }
    int getMapSize() { return _mapSize; }
    bool getFirstDirChange() { return _firstDirChange; }

signals:
    void endGame();

private:
    void moveShip(int x, int y, Field field);
    void stepOnBHole();

    QVector<QVector<Field> > _map;
    int _mapSize;
    Player _player;
    int _score[2];
    bool _firstDirChange;

    dataAccess *_dataAccess;
};

#endif // BLACKHOLEMODEL_H
