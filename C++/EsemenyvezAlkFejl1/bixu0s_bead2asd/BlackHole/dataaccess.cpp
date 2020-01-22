#include "dataaccess.h"

bool dataAccess::saveGame(QVector<QVector<Field> > saveGameData, Player currPlayer, bool firstChangeDir, int score[2]){
    QFile file("game.sav");
    if (!file.open(QFile::WriteOnly))
        return false;

    QTextStream stream(&file);

    stream << saveGameData.size() << endl;
    stream << (int) currPlayer << endl;
    stream << (int) firstChangeDir << endl;
    stream << score[0] << endl;
    stream << score[1] << endl;

    for (int i = 0; i < saveGameData.size(); i++){
        for(int j = 0; j < saveGameData.size(); j++){
            stream << (int) saveGameData[i][j].dir << endl;
            stream << (int) saveGameData[i][j].type << endl;
        }
    }

    file.close();

    return true;
}

bool dataAccess::loadGame(QVector<QVector<Field> >& map,Player& player, int& size, bool& firstChangeDir, int (&score)[2]){
    QFile file("game.sav");
    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);

    size = stream.readLine().toInt();
    player = (Player) stream.readLine().toInt();
    firstChangeDir = (bool) stream.readLine().toInt();
    score[0] = stream.readLine().toInt();
    score[1] = stream.readLine().toInt();

    map.resize(size);
    for (int i = 0; i < size; i++){
        map[i].resize(size);
        for(int j = 0; j < size; j++){
            map[i][j].dir = (Direction) stream.readLine().toInt();
            map[i][j].type = (Type) stream.readLine().toInt();
        }
    }

    file.close();

    return true;
}
