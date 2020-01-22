#include "blackholeview.h"

blackHoleView::blackHoleView(QWidget *parent)
    : QWidget(parent)
{
    _model = new blackHoleModel();

    _easyPB = new QPushButton(tr("Easy (5x5)"));
    _medPB = new QPushButton(tr("Medium (7x7)"));
    _hardPB = new QPushButton(tr("Hard (9x9)"));

    _nextTurnPB = new QPushButton(tr("Next Turn"));

    _saveGamePB = new QPushButton(tr("Save Game"));
    _loadGamePB = new QPushButton(tr("Load Game"));

    _diffHBoxLayout = new QHBoxLayout();
    _diffHBoxLayout->addWidget(_easyPB);
    _diffHBoxLayout->addWidget(_medPB);
    _diffHBoxLayout->addWidget(_hardPB);

    _loadSavHBoxeLayout = new QHBoxLayout();
    _loadSavHBoxeLayout->addWidget(_saveGamePB);
    _loadSavHBoxeLayout->addWidget(_loadGamePB);

    _gridBoxLayout = new QGridLayout();

    _vBoxLayout = new QVBoxLayout();
    _vBoxLayout->addLayout(_diffHBoxLayout);
    _vBoxLayout->addLayout(_gridBoxLayout);
    _vBoxLayout->addWidget(_nextTurnPB);
    _vBoxLayout->addLayout(_loadSavHBoxeLayout);

    connect(_easyPB, SIGNAL(clicked(bool)), this, SLOT(newGame()));
    connect(_medPB, SIGNAL(clicked(bool)), this, SLOT(newGame()));
    connect(_hardPB, SIGNAL(clicked(bool)), this, SLOT(newGame()));
    connect(_nextTurnPB, SIGNAL(clicked(bool)), this, SLOT(onNextTurn()));
    connect(_model, SIGNAL(endGame()), this, SLOT(onEndGame()));
    connect(_saveGamePB, SIGNAL(clicked(bool)), this, SLOT(onSaveGame()));
    connect(_loadGamePB, SIGNAL(clicked(bool)), this, SLOT(onLoadGame()));

    setLayout(_vBoxLayout);
}

blackHoleView::~blackHoleView()
{

}

void blackHoleView::newGame(){
    if(!_mapView.isEmpty()){
        for(int i = 0; i < _mapView.size(); i++){
            for(int j = 0; j < _mapView.size(); j++){
                delete _mapView[i][j];
            }
        }
    }

    QObject *obj = sender();
    if(obj == _easyPB){
        _model->newGame(5);
        setFixedSize(290,380);
    } else if(obj == _medPB){
        _model->newGame(7);
        setFixedSize(390,480);
    } else if(obj == _hardPB){
        _model->newGame(9);
        setFixedSize(490,580);
    }

    _mapView.resize(_model->getMapSize());
    for(int i = 0; i < _model->getMapSize(); i++){
        _mapView[i].resize(_model->getMapSize());
        for(int j = 0; j < _model->getMapSize(); j++){
            _mapView[i][j] = new QPushButton();
            _mapView[i][j]->setFixedSize(50,50);
            switch(_model->getFieldType(i,j)){
            case BLUE:
                _mapView[i][j]->setStyleSheet("background-color: blue");

                setMapViewDir(i, j);

                connect(_mapView[i][j], SIGNAL(clicked(bool)), this, SLOT(onShipClick()));
                break;
            case RED:
                _mapView[i][j]->setStyleSheet("background-color: red");

                setMapViewDir(i, j);

                connect(_mapView[i][j], SIGNAL(clicked(bool)), this, SLOT(onShipClick()));
                break;
            case B_HOLE:
                _mapView[i][j]->setStyleSheet("background-color: black");
                break;
            case EMPTY:
                _mapView[i][j]->setStyleSheet("background-color: white");
                break;
            }
            _gridBoxLayout->addWidget(_mapView[i][j], i, j);
        }
    }
}


void blackHoleView::redraw(){
    for(int i = 0; i < _mapView.size(); i++){
        for(int j = 0; j < _mapView.size(); j++){
            delete _mapView[i][j];
        }
    }

    _mapView.resize(_model->getMapSize());
    for(int i = 0; i < _model->getMapSize(); i++){
        _mapView[i].resize(_model->getMapSize());
        for(int j = 0; j < _model->getMapSize(); j++){
            _mapView[i][j] = new QPushButton();
            _mapView[i][j]->setFixedSize(50,50);
            switch(_model->getFieldType(i,j)){
            case BLUE:
                _mapView[i][j]->setStyleSheet("background-color: blue");

                setMapViewDir(i, j);

                connect(_mapView[i][j], SIGNAL(clicked(bool)), this, SLOT(onShipClick()));
                break;
            case RED:
                _mapView[i][j]->setStyleSheet("background-color: red");

                setMapViewDir(i, j);

                connect(_mapView[i][j], SIGNAL(clicked(bool)), this, SLOT(onShipClick()));
                break;
            case B_HOLE:
                _mapView[i][j]->setStyleSheet("background-color: black");
                break;
            case EMPTY:
                _mapView[i][j]->setStyleSheet("background-color: white");
                break;
            }
            _gridBoxLayout->addWidget(_mapView[i][j], i, j);
        }
    }
}

void blackHoleView::onShipClick(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int index = _gridBoxLayout->indexOf(button);
    int row, col, rowSpan, colSpan;
    _gridBoxLayout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);

    _model->shipDirChange(row, col);

    redraw();
}

void blackHoleView::setMapViewDir(int i, int j){
    switch(_model->getFieldDir(i,j)){
    case UP:
        _mapView[i][j]->setText(tr("⇑"));
        break;
    case DOWN:
        _mapView[i][j]->setText(tr("⇓"));
        break;
    case LEFT:
        _mapView[i][j]->setText(tr("⇐"));
        break;
    case RIGHT:
        _mapView[i][j]->setText(tr("⇒"));
        break;
    }
}

void blackHoleView::onNextTurn(){
    _model->findThenMoveShips();
    redraw();
}

void blackHoleView::onEndGame(){
    if(_model->getPlayer() == PLAYER_ONE) QMessageBox::information(this, tr("Game Ended"), tr("RED won!"));
    else QMessageBox::information(this, tr("Game Ended"), tr("BLUE won!"));
    _model->newGame(_model->getMapSize());
    redraw();
}

void blackHoleView::onSaveGame(){
    _model->saveGame();
}

void blackHoleView::onLoadGame(){
    _model->loadGame();
    switch(_model->getMapSize()){
    case 5:
        setFixedSize(290,380);
        break;
    case 7:
        setFixedSize(390,480);
        break;
    case 9:
        setFixedSize(490,580);
        break;
    }
    redraw();
}
