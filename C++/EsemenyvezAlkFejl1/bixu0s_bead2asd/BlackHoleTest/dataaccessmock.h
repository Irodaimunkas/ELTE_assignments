#ifndef DATAACCESSMOCK
#define DATAACCESSMOCK

#include "dataaccess.h"

class dataAccessMock : public dataAccess{
public:
    bool saveGame(QVector<QVector<Field> > saveGameData, Player currPlayer, bool firstChangeDir, int score[2]){
        qDebug() << "Size: " << saveGameData.size();
        qDebug() << "CurrPlayer: " << (int) currPlayer;
        qDebug() << "firstDirChange: " << (int) firstChangeDir;
        qDebug() << "redScore: " << score[0];
        qDebug() << "blueScore: " << score[1];

        for (int i = 0; i < saveGameData.size(); i++){
            for(int j = 0; j < saveGameData.size(); j++){
                qDebug() << i << " " << j << " direction: " << (int) saveGameData[i][j].dir;
                qDebug() << i << " " << j << " type: " << (int) saveGameData[i][j].type;
            }
        }
        return true;
    }

    bool loadGame(QVector<QVector<Field> >& map, Player& player, int& size, bool& firstChangeDir, int (&score)[2]){
        size = 5;
        player = PLAYER_ONE;
        firstChangeDir = true;
        score[0] = 0;
        score[1] = 0;

        map.resize(size);
        for(int i = 0; i < size; i++){
            map[i].resize(size);
            for(int j = 0; j < size; j++){
                map[i][j].dir = NO_DIR;
                map[i][j].type = EMPTY;
            }
        }

        map[0][0].type = RED;
        map[0][1].type = RED;
        map[0][size-1].type = RED;
        map[0][size-2].type = RED;

        map[size-1][0].type = BLUE;
        map[size-1][1].type = BLUE;
        map[size-1][size-1].type = BLUE;
        map[size-1][size-2].type = BLUE;

        map[size/2][size/2].type = B_HOLE;

        qDebug() << "Game loaded: ";

        qDebug() << "Size: " << size;
        qDebug() << "CurrPlayer: " << (int) player;
        qDebug() << "firstDirChange: " << (int) firstChangeDir;
        qDebug() << "redScore: " << score[0];
        qDebug() << "blueScore: " << score[1];

        for (int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                qDebug() << i << " " << j << " direction: " << (int) map[i][j].dir;
                qDebug() << i << " " << j << " type: " << (int) map[i][j].type;
            }
        }

        return true;
    }
};

#endif // DATAACCESSMOCK

