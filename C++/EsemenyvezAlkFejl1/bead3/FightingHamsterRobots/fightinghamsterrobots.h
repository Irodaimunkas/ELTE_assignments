#ifndef FIGHTINGHAMSTERROBOTS_H
#define FIGHTINGHAMSTERROBOTS_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "fightinghamsterrobotsmodel.h"
#include <QKeyEvent>
#include <QMessageBox>

class FightingHamsterRobots : public QWidget
{
    Q_OBJECT

private:
    QPushButton *_newSmallGame, *_newMediumGame, *_newBigGame;
    QVector<QVector<QLabel*> > _labels;
    QVBoxLayout *_vLayout;
    QHBoxLayout *_hLayout, *_addOnsLayout, *_hpLayout;
    QGridLayout *_gLayout;
    FightingHamsterRobotsModel *_model;
    QLabel *_lifePlayerOneL, *_lifePlayerTwoL, *_currentMove, *_currentPlayer;

public:
    FightingHamsterRobots(QWidget *parent = 0);

    void drawGrid(int w, int h);
    void refreshTable();

    ~FightingHamsterRobots();

public slots:
    void onPlayerOneWon();
    void onPlayerTwoWon();
    void onDraw();
    void deleteLabelGrid();

private slots:
    void onKeyPressed(QKeyEvent* event);
    void newGame();

signals:
    void keyPressEvent(QKeyEvent*);
};

#endif // FIGHTINGHAMSTERROBOTS_H
