#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>

enum Direction { UP, DOWN, LEFT, RIGHT, NO_DIR };
enum Type { BLUE, RED, B_HOLE, EMPTY };
enum Player { PLAYER_ONE, PLAYER_TWO };

struct Field {
    Direction dir;
    Type type;
};

class dataAccess : public QObject
{
    Q_OBJECT
public:
    bool saveGame(QVector<QVector<Field> > saveGameData, Player currPlayer, bool firstChangeDir, int score[2]);
    bool loadGame(QVector<QVector<Field> >& map, Player& player, int& size, bool& firstChangeDir, int (&score)[2]);
};

#endif // DATAACCESS_H
