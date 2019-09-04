#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector>

enum Direction { UP, DOWN, LEFT, RIGHT };
enum Command { UPC, DOWNC, LEFTC, RIGHTC, ROTATEL, ROTATER, PUNCH, SHOOT };

class Player : public QObject
{
    Q_OBJECT

private:
    int _health;
    int _x;
    int _y;
    int _cmN;
    Direction _dir;
    QVector<Command> _cm;


public:
    explicit Player(QObject *parent = 0);
    int getX() { return _x; }
    int getY() { return _y; }
    int getHP() { return _health; }
    int getCmN() { return _cmN; }
    Direction getDir()  { return _dir; }
    QVector<Command> getCms() { return _cm; }

    void setX(int val);
    void setY(int val);
    void setHP(int val);
    void setDir(Direction val);
    void addCm(Command cm);
    void removeLastCm();
    void clearCm();
};

#endif // PLAYER_H
