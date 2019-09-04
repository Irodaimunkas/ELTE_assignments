#ifndef FIGHTINGHAMSTERROBOTSMODEL_H
#define FIGHTINGHAMSTERROBOTSMODEL_H

#include <QObject>
#include "fieldtable.h"
#include "loadsave.h"

enum Keys { W, D, S, A, E, Q, K, L, BACKSPACE, ENTER };

class FightingHamsterRobotsModel : public QObject
{
    Q_OBJECT
private:
    FieldTable _table;
    int _currentPlayer;
public:
    explicit FightingHamsterRobotsModel(QObject *parent = 0);

    int getCurrentPlayer() { return _currentPlayer; }

    FieldTable &table() { return _table; }
    void onKeyPressedM(Keys key);
    void doCommand(int val);
    void newGameM(int size);

    bool shoot(Direction dir, int player);

signals:
    void playerOneWon();
    void playerTwoWon();
    void draw();
};

#endif // FIGHTINGHAMSTERROBOTSMODEL_H
