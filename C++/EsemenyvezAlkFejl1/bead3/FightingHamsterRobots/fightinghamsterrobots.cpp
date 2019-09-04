#include "fightinghamsterrobots.h"

FightingHamsterRobots::FightingHamsterRobots(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Fighting Hamster Robots");
    setFixedSize(400,500);

    _model = new FightingHamsterRobotsModel();

    _newSmallGame = new QPushButton(tr("New Game\n(Small)"));
    _newMediumGame = new QPushButton(tr("New Game\n(Medium)"));;
    _newBigGame = new QPushButton(tr("New Game\n(Big)"));;

    _lifePlayerOneL = new QLabel(tr("Player One HP: ") + QString::number(_model->table().playerOne().getHP()));
    _lifePlayerTwoL = new QLabel(tr("Player Two HP: ") + QString::number(_model->table().playerOne().getHP()));
    _currentMove = new QLabel();
    _currentPlayer = new QLabel(tr("Player One | "));

    _addOnsLayout = new QHBoxLayout();
    _addOnsLayout->addWidget(_currentPlayer);
    _addOnsLayout->addWidget(_currentMove);

    _hLayout = new QHBoxLayout();
    _hLayout->addWidget(_newSmallGame);
    _hLayout->addWidget(_newMediumGame);
    _hLayout->addWidget(_newBigGame);

    _hpLayout = new QHBoxLayout();
    _hpLayout->addWidget(_lifePlayerOneL);
    _hpLayout->addWidget(_lifePlayerTwoL);

    _gLayout = new QGridLayout();

    _vLayout = new QVBoxLayout();
    _vLayout->addLayout(_hLayout);
    _vLayout->addLayout(_hpLayout);
    _vLayout->addLayout(_gLayout);
    _vLayout->addLayout(_addOnsLayout);

    setLayout(_vLayout);

    drawGrid(50,50);

    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)), this, SLOT(onKeyPressed(QKeyEvent*)));
    connect(_model, SIGNAL(playerOneWon()), this, SLOT(onPlayerOneWon()));
    connect(_model, SIGNAL(playerTwoWon()), this, SLOT(onPlayerTwoWon()));
    connect(_model, SIGNAL(draw()), this, SLOT(onDraw()));
    connect(_newSmallGame, SIGNAL(clicked(bool)), this, SLOT(newGame()));
    connect(_newMediumGame, SIGNAL(clicked(bool)), this, SLOT(newGame()));
    connect(_newBigGame, SIGNAL(clicked(bool)), this, SLOT(newGame()));
}

void FightingHamsterRobots::drawGrid(int w, int h){
    _labels.resize(_model->table().size());
    for(int i = 0; i < _model->table().size(); i++){
        _labels[i].resize(_model->table().size());
        for(int j = 0; j < _model->table().size(); j++){
            _labels[i][j] = new QLabel();
            _labels[i][j]->setFixedSize(w, h);
            _labels[i][j]->setStyleSheet("QLabel { background-color : white; }");
            if(_model->table().getVals()[i][j] == PLAYERONE) {
                _labels[i][j]->setStyleSheet("QLabel { background-color : pink; color: black }");
                _labels[i][j]->setText("Up");
                _labels[i][j]->setAlignment(Qt::AlignCenter);
            }
            if(_model->table().getVals()[i][j] == PLAYERTWO) {
                _labels[i][j]->setStyleSheet("QLabel { background-color : black; }");
                _labels[i][j]->setText("Up");
                _labels[i][j]->setAlignment(Qt::AlignCenter);
            }
            _gLayout->addWidget(_labels[i][j],i,j);
        }
    }
}

void FightingHamsterRobots::onKeyPressed(QKeyEvent* event){
    if(event->key() == Qt::Key_W) {
        _model->onKeyPressedM(W);
    }
    else if(event->key() == Qt::Key_S) {
        _model->onKeyPressedM(S);
    }
    else if(event->key() == Qt::Key_A) {
        _model->onKeyPressedM(A);
    }
    else if(event->key() == Qt::Key_D) {
        _model->onKeyPressedM(D);
    }
    else if(event->key() == Qt::Key_E) {
        _model->onKeyPressedM(E);
    }
    else if(event->key() == Qt::Key_Q) {
        _model->onKeyPressedM(Q);
    }
    else if(event->key() == Qt::Key_K) {
        _model->onKeyPressedM(K);
    }
    else if(event->key() == Qt::Key_L) {
        _model->onKeyPressedM(L);
    }
    else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        _model->onKeyPressedM(ENTER);
    }
    else if(event->key() == Qt::Key_Backspace) {
        _model->onKeyPressedM(BACKSPACE);
    }
    refreshTable();
}

void FightingHamsterRobots::refreshTable(){
    if(_model->getCurrentPlayer() == 1){
        _currentMove->clear();
        _currentPlayer->clear();
        _currentPlayer->setText("Player One");
        for(int i = 0; i < _model->table().playerOne().getCmN(); i++){
            switch(_model->table().playerOne().getCms()[i]){
                case UPC:
                    _currentMove->setText(_currentMove->text() + tr(" + UP"));
                    break;
                case DOWNC:
                    _currentMove->setText(_currentMove->text() + tr(" + DOWN"));
                    break;
                case LEFTC:
                    _currentMove->setText(_currentMove->text() + tr(" + LEFT"));
                    break;
                case RIGHTC:
                    _currentMove->setText(_currentMove->text() + tr(" + RIGHT"));
                    break;
                case ROTATEL:
                    _currentMove->setText(_currentMove->text() + tr(" + ROTATEL"));
                    break;
                case ROTATER:
                    _currentMove->setText(_currentMove->text() + tr(" + ROTATER"));
                    break;
                case SHOOT:
                    _currentMove->setText(_currentMove->text() + tr(" + SHOOT"));
                    break;
                case PUNCH:
                    _currentMove->setText(_currentMove->text() + tr(" + PUNCH"));
                    break;
            }
        }
    }
    else{
        _currentMove->clear();
        _currentPlayer->clear();
        _currentPlayer->setText(tr("Player Two"));
        for(int i = 0; i < _model->table().playerTwo().getCmN(); i++){
            switch(_model->table().playerTwo().getCms()[i]){
                case UPC:
                    _currentMove->setText(_currentMove->text() + tr(" + UP"));
                    break;
                case DOWNC:
                    _currentMove->setText(_currentMove->text() + tr(" + DOWN"));
                    break;
                case LEFTC:
                    _currentMove->setText(_currentMove->text() + tr(" + LEFT"));
                    break;
                case RIGHTC:
                    _currentMove->setText(_currentMove->text() + tr(" + RIGHT"));
                    break;
                case ROTATEL:
                    _currentMove->setText(_currentMove->text() + tr(" + ROTATEL"));
                    break;
                case ROTATER:
                    _currentMove->setText(_currentMove->text() + tr(" + ROTATER"));
                    break;
                case SHOOT:
                    _currentMove->setText(_currentMove->text() + tr(" + SHOOT"));
                    break;
                case PUNCH:
                    _currentMove->setText(_currentMove->text() + tr(" + PUNCH"));
                    break;
            }
        }
    }
    for(int i = 0; i < _model->table().size(); i++){
        for(int j = 0; j < _model->table().size(); j++){
            _labels[i][j]->clear();
            _labels[i][j]->setStyleSheet("QLabel { background-color : white; }");
            if(_model->table().getVals()[i][j] == PLAYERONE) {
                _labels[i][j]->setStyleSheet("QLabel { background-color : pink; color: black }");
                switch(_model->table().playerOne().getDir()){
                    case UP:
                        _labels[i][j]->setText("Up");
                        _labels[i][j]->setAlignment(Qt::AlignCenter);
                        break;
                    case DOWN:
                        _labels[i][j]->setText("Down");
                        _labels[i][j]->setAlignment(Qt::AlignCenter);
                        break;
                    case RIGHT:
                        _labels[i][j]->setText("Right");
                        _labels[i][j]->setAlignment(Qt::AlignCenter);
                        break;
                    case LEFT:
                        _labels[i][j]->setText("Left");
                        _labels[i][j]->setAlignment(Qt::AlignCenter);
                        break;
                }
            }
            if(_model->table().getVals()[i][j] == PLAYERTWO) {
                _labels[i][j]->setStyleSheet("QLabel { background-color : black; }");
                switch(_model->table().playerTwo().getDir()){
                    case UP:
                        _labels[i][j]->setText("Up");
                        _labels[i][j]->setAlignment(Qt::AlignCenter);
                        break;
                    case DOWN:
                        _labels[i][j]->setText("Down");
                        _labels[i][j]->setAlignment(Qt::AlignCenter);
                        break;
                    case RIGHT:
                        _labels[i][j]->setText("Right");
                        _labels[i][j]->setAlignment(Qt::AlignCenter);
                        break;
                    case LEFT:
                        _labels[i][j]->setText("Left");
                        _labels[i][j]->setAlignment(Qt::AlignCenter);
                        break;
                }
            }
        }
    }
    _lifePlayerOneL->clear();
    _lifePlayerTwoL->clear();
    _lifePlayerOneL->setText(tr("Player One HP: ") + QString::number(_model->table().playerOne().getHP()));
    _lifePlayerTwoL->setText(tr("Player Two HP: ") + QString::number(_model->table().playerTwo().getHP()));
}

void FightingHamsterRobots::deleteLabelGrid(){
    for(int i = 0; i < _model->table().size(); i++){
        for(int j = 0; j < _model->table().size(); j++){
            delete _labels[i][j];
        }
    }
}

void FightingHamsterRobots::newGame(){
    if(QObject::sender() == _newSmallGame){
        deleteLabelGrid();
        _model->newGameM(4);
        setFixedSize(250,350);
        drawGrid(50,50);
        refreshTable();
    }
    else if(QObject::sender() == _newMediumGame){
        deleteLabelGrid();
        _model->newGameM(6);
        setFixedSize(400,500);
        drawGrid(50,50);
        refreshTable();
    }
    else {
        deleteLabelGrid();
        _model->newGameM(8);
        setFixedSize(500,600);
        drawGrid(50,50);
        refreshTable();
    }
}

void FightingHamsterRobots::onPlayerOneWon(){
    QMessageBox::information(this, tr("Player One Won!"), tr("Congratulations Player One!"));
    deleteLabelGrid();
    _model->newGameM(6);
    setFixedSize(400,500);
    drawGrid(50,50);
    refreshTable();
}

void FightingHamsterRobots::onPlayerTwoWon(){
    QMessageBox::information(this, tr("Player Two Won!"), tr("Congratulations Player Two!"));
    deleteLabelGrid();
    _model->newGameM(6);
    setFixedSize(400,500);
    drawGrid(50,50);
    refreshTable();
}

void FightingHamsterRobots::onDraw(){
    QMessageBox::information(this, tr("Draw..."), tr("Looks like it was an equal battle..."));
    deleteLabelGrid();
    _model->newGameM(6);
    setFixedSize(400,500);
    drawGrid(50,50);
    refreshTable();
}

FightingHamsterRobots::~FightingHamsterRobots()
{
    delete _model;
}

