#ifndef BLACKHOLEVIEW_H
#define BLACKHOLEVIEW_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "blackholemodel.h"
#include <QMessageBox>

class blackHoleView : public QWidget
{
    Q_OBJECT

public:
    blackHoleView(QWidget *parent = 0);
    ~blackHoleView();

    void redraw();
    void setMapViewDir(int i, int j);

private slots:
    void newGame();
    void onShipClick();
    void onNextTurn();
    void onEndGame();
    void onSaveGame();
    void onLoadGame();

private:
    QVector<QVector<QPushButton*> > _mapView;
    QPushButton *_easyPB, *_medPB, *_hardPB, *_nextTurnPB, *_saveGamePB, *_loadGamePB;
    QVBoxLayout *_vBoxLayout;
    QHBoxLayout *_diffHBoxLayout, *_loadSavHBoxeLayout;
    QGridLayout *_gridBoxLayout;

    blackHoleModel *_model;
};

#endif // BLACKHOLEVIEW_H
