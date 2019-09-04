#include "fightinghamsterrobotsmodel.h"

FightingHamsterRobotsModel::FightingHamsterRobotsModel(QObject *parent) : QObject(parent)
{
    _currentPlayer = 1;
}

void FightingHamsterRobotsModel::onKeyPressedM(Keys key)
{
    switch(key){
        case W:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() < 5){
                    table().playerOne().addCm(UPC);
                }
            }
            else{
                if(table().playerTwo().getCmN() < 5){
                    table().playerTwo().addCm(UPC);
                }
            }
            break;
        case D:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() < 5){
                    table().playerOne().addCm(RIGHTC);
                }
            }
            else{
                if(table().playerTwo().getCmN() < 5){
                    table().playerTwo().addCm(RIGHTC);
                }
            }
            break;
        case S:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() < 5){
                    table().playerOne().addCm(DOWNC);
                }
            }
            else{
                if(table().playerTwo().getCmN() < 5){
                    table().playerTwo().addCm(DOWNC);
                }
            }
            break;
        case A:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() < 5){
                    table().playerOne().addCm(LEFTC);
                }
            }
            else{
                if(table().playerTwo().getCmN() < 5){
                    table().playerTwo().addCm(LEFTC);
                }
            }
            break;
        case E:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() < 5){
                    table().playerOne().addCm(ROTATER);
                }
            }
            else{
                if(table().playerTwo().getCmN() < 5){
                    table().playerTwo().addCm(ROTATER);
                }
            }
            break;
        case Q:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() < 5){
                    table().playerOne().addCm(ROTATEL);
                }
            }
            else{
                if(table().playerTwo().getCmN() < 5){
                    table().playerTwo().addCm(ROTATEL);
                }
            }
            break;
        case K:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() < 5){
                    table().playerOne().addCm(PUNCH);
                }
            }
            else{
                if(table().playerTwo().getCmN() < 5){
                    table().playerTwo().addCm(PUNCH);
                }
            }
            break;
        case L:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() < 5){
                    table().playerOne().addCm(SHOOT);
                }
            }
            else{
                if(table().playerTwo().getCmN() < 5){
                    table().playerTwo().addCm(SHOOT);
                }
            }
            break;
        case BACKSPACE:
            if(_currentPlayer == 1){
                if(table().playerOne().getCmN() > 0){
                    table().playerOne().removeLastCm();
                }
            }
            else{
                if(table().playerTwo().getCmN() > 0){
                    table().playerTwo().removeLastCm();
                }
            }
            break;
        case ENTER:
            if(table().playerTwo().getCmN() == 5){
                for(int i = 0; i < 5; i++)
                    doCommand(i);
                table().playerOne().clearCm();
                table().playerTwo().clearCm();
                _currentPlayer = 1;
            }
            else if(table().playerOne().getCmN() == 5){
                _currentPlayer = 2;
            }
            break;
    }
}

// shoot, punch, rotates, dirs
void FightingHamsterRobotsModel::doCommand(int val){
    int x_one = table().playerOne().getX();
    int y_one = table().playerOne().getY();
    int x_two = table().playerTwo().getX();
    int y_two = table().playerTwo().getY();

    switch(table().playerOne().getCms()[val]){
        case UPC:
            if( (x_one - 1 != x_two || y_one != y_two) && x_one - 1 >= 0 ){
                if(x_one - 2 == x_two && y_one == y_two && table().playerTwo().getCms()[val] == DOWNC)
                    return;
                table().playerOne().setX( x_one - 1 );
                table().setValue( x_one, y_one, NOTHING);
                table().setValue( x_one - 1, y_one, PLAYERONE);
            }
            break;
        case DOWNC:
            if( (x_one + 1 != x_two || y_one != y_two) && x_one + 1 < table().size() ){
                if(x_one + 2 == x_two && y_one == y_two && table().playerTwo().getCms()[val] == UPC)
                    return;
                table().playerOne().setX( x_one + 1 );
                table().setValue( x_one, y_one, NOTHING);
                table().setValue( x_one + 1, y_one, PLAYERONE);
            }
            break;
        case LEFTC:
            if( (y_one - 1 != y_two || x_one != x_two) && y_one - 1 >= 0 ){
                if(y_one - 2 == y_two && x_one == x_two && table().playerTwo().getCms()[val] == RIGHTC)
                    return;
                table().playerOne().setY( y_one - 1 );
                table().setValue( x_one, y_one, NOTHING);
                table().setValue( x_one, y_one - 1, PLAYERONE);
            }
            break;
        case RIGHTC:
            if( (y_one + 1 != y_two || x_one != x_two) && y_one + 1 < table().size() ){
                if(y_one + 2 == y_two && x_one == x_two && table().playerTwo().getCms()[val] == LEFTC)
                    return;
                table().playerOne().setY( y_one + 1 );
                table().setValue( x_one, y_one, NOTHING);
                table().setValue( x_one, y_one + 1, PLAYERONE);
            }
            break;
        case ROTATEL:
            switch(table().playerOne().getDir()){
                case UP:
                    table().playerOne().setDir(LEFT);
                    break;
                case DOWN:
                    table().playerOne().setDir(RIGHT);
                    break;
                case RIGHT:
                    table().playerOne().setDir(UP);
                    break;
                case LEFT:
                    table().playerOne().setDir(DOWN);
                    break;
            }
            break;
        case ROTATER:
            switch(table().playerOne().getDir()){
                case UP:
                    table().playerOne().setDir(RIGHT);
                    break;
                case DOWN:
                    table().playerOne().setDir(LEFT);
                    break;
                case RIGHT:
                    table().playerOne().setDir(DOWN);
                    break;
                case LEFT:
                    table().playerOne().setDir(UP);
                    break;
            }
            break;
        case SHOOT:
            if(table().playerTwo().getCms()[val] != SHOOT){
                switch(table().playerOne().getDir()){
                    case UP:
                        if( shoot(UP, 1) ){
                            table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                            if(table().playerTwo().getHP() == 0) emit playerOneWon();
                        }
                        break;
                    case DOWN:
                        if( shoot(DOWN, 1) ){
                            table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                            if(table().playerTwo().getHP() == 0) emit playerOneWon();
                        }
                        break;
                    case RIGHT:
                        if( shoot(RIGHT, 1) ){
                            table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                            if(table().playerTwo().getHP() == 0) emit playerOneWon();
                        }
                        break;
                    case LEFT:
                        if( shoot(LEFT, 1) ){
                            table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                            if(table().playerTwo().getHP() == 0) emit playerOneWon();
                        }
                        break;
                }
            }
            else {
                switch(table().playerOne().getDir()){
                    case UP:
                        if( shoot(UP, 1) && (table().playerTwo().getDir() == DOWN) ){
                            table().playerOne().setHP( table().playerOne().getHP() - 1 );
                            table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                            if( table().playerOne().getHP() == 0 && table().playerTwo().getHP() == 0 ) emit draw();
                            else if( table().playerOne().getHP() == 0) emit playerTwoWon();
                            else if( table().playerTwo().getHP() == 0) emit playerOneWon();
                        }
                        break;
                    case DOWN:
                        if( shoot(DOWN, 1) && (table().playerTwo().getDir() == UP) ){
                            table().playerOne().setHP( table().playerOne().getHP() - 1 );
                            table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                            if( table().playerOne().getHP() == 0 && table().playerTwo().getHP() == 0 ) emit draw();
                            else if( table().playerOne().getHP() == 0) emit playerTwoWon();
                            else if( table().playerTwo().getHP() == 0) emit playerOneWon();
                        }
                        break;
                    case RIGHT:
                        if( shoot(RIGHT, 1) && (table().playerTwo().getDir() == LEFT) ){
                            table().playerOne().setHP( table().playerOne().getHP() - 1 );
                            table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                            if( table().playerOne().getHP() == 0 && table().playerTwo().getHP() == 0 ) emit draw();
                            else if( table().playerOne().getHP() == 0) emit playerTwoWon();
                            else if( table().playerTwo().getHP() == 0) emit playerOneWon();
                        }
                        break;
                    case LEFT:
                        if( shoot(LEFT, 1) && (table().playerTwo().getDir() == RIGHT) ){
                            table().playerOne().setHP( table().playerOne().getHP() - 1 );
                            table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                            if( table().playerOne().getHP() == 0 && table().playerTwo().getHP() == 0 ) emit draw();
                            else if( table().playerOne().getHP() == 0) emit playerTwoWon();
                            else if( table().playerTwo().getHP() == 0) emit playerOneWon();
                        }
                        break;
                }
                return;
            }
            break;
        case PUNCH:
            if(table().playerTwo().getCms()[val] != PUNCH){
                if( (x_two == x_one + 1 && y_two == y_one + 1) ||
                    (x_two == x_one + 1 && y_two == y_one - 1) ||
                    (x_two == x_one - 1 && y_two == y_one - 1) ||
                    (x_two == x_one - 1 && y_two == y_one + 1) ||
                    (x_two == x_one + 1 && y_two == y_one) ||
                    (x_two == x_one - 1 && y_two == y_one) ||
                    (x_two == x_one && y_two == y_one + 1) ||
                    (x_two == x_one && y_two == y_one - 1) ){
                    table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                    if(table().playerTwo().getHP() == 0) emit playerOneWon();
                }
            }
            else {
                if( (x_two == x_one + 1 && y_two == y_one + 1) ||
                    (x_two == x_one + 1 && y_two == y_one - 1) ||
                    (x_two == x_one - 1 && y_two == y_one - 1) ||
                    (x_two == x_one - 1 && y_two == y_one + 1) ||
                    (x_two == x_one + 1 && y_two == y_one) ||
                    (x_two == x_one - 1 && y_two == y_one) ||
                    (x_two == x_one && y_two == y_one + 1) ||
                    (x_two == x_one && y_two == y_one - 1) ){
                    table().playerOne().setHP( table().playerOne().getHP() - 1 );
                    table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                    if( table().playerOne().getHP() == 0 && table().playerTwo().getHP() == 0 ) emit draw();
                    else if( table().playerOne().getHP() == 0) emit playerTwoWon();
                    else if( table().playerTwo().getHP() == 0) emit playerOneWon();
                }
                return;
            }
            break;
    }
    switch(table().playerTwo().getCms()[val]){
        case UPC:
            if( (x_one != x_two - 1 || y_one != y_two) && x_two - 1 >= 0 ){
                table().playerTwo().setX( x_two - 1 );
                table().setValue( x_two, y_two, NOTHING);
                table().setValue( x_two - 1, y_two, PLAYERTWO);
            }
            break;
        case DOWNC:
            if( (x_one != x_two + 1 || y_one != y_two) && x_two + 1 < table().size() ){
                table().playerTwo().setX( x_two + 1 );
                table().setValue( x_two, y_two, NOTHING);
                table().setValue( x_two + 1, y_two, PLAYERTWO);
            }
            break;
        case LEFTC:
            if( (y_one != y_two - 1 || x_one != x_two) && y_two - 1 >= 0 ){
                table().playerTwo().setY( y_two - 1 );
                table().setValue( x_two, y_two, NOTHING);
                table().setValue( x_two, y_two - 1, PLAYERTWO);
            }
            break;
        case RIGHTC:
            if( (y_one != y_two + 1 || x_one != x_two) && y_two + 1 < table().size() ){
                table().playerTwo().setY( y_two + 1 );
                table().setValue( x_two, y_two, NOTHING);
                table().setValue( x_two, y_two + 1, PLAYERTWO);
            }
            break;
        case ROTATEL:
            switch(table().playerTwo().getDir()){
                case UP:
                    table().playerTwo().setDir(LEFT);
                    break;
                case DOWN:
                    table().playerTwo().setDir(RIGHT);
                    break;
                case RIGHT:
                    table().playerTwo().setDir(UP);
                    break;
                case LEFT:
                    table().playerTwo().setDir(DOWN);
                    break;
            }
            break;
        case ROTATER:
            switch(table().playerTwo().getDir()){
                case UP:
                    table().playerTwo().setDir(RIGHT);
                    break;
                case DOWN:
                    table().playerTwo().setDir(LEFT);
                    break;
                case RIGHT:
                    table().playerTwo().setDir(DOWN);
                    break;
                case LEFT:
                    table().playerTwo().setDir(UP);
                    break;
            }
        case SHOOT:
            switch(table().playerTwo().getDir()){
                case UP:
                    if( shoot(UP, 2) ){
                        table().playerOne().setHP( table().playerOne().getHP() - 1 );
                        if(table().playerOne().getHP() == 0) emit playerTwoWon();
                    }
                    break;
                case DOWN:
                    if( shoot(DOWN, 2) ){
                        table().playerOne().setHP( table().playerOne().getHP() - 1 );
                        if(table().playerOne().getHP() == 0) emit playerTwoWon();
                    }
                    break;
                case RIGHT:
                    if( shoot(RIGHT, 2) ){
                        table().playerOne().setHP( table().playerOne().getHP() - 1 );
                        if(table().playerOne().getHP() == 0) emit playerTwoWon();
                    }
                    break;
                case LEFT:
                    if( shoot(LEFT, 2) ){
                        table().playerOne().setHP( table().playerOne().getHP() - 1 );
                        if(table().playerOne().getHP() == 0) emit playerTwoWon();
                    }
                    break;
            }
            break;
        case PUNCH:
            if(table().playerOne().getCms()[val] != PUNCH){
                if( (x_two == x_one + 1 && y_two == y_one + 1) ||
                    (x_two == x_one + 1 && y_two == y_one - 1) ||
                    (x_two == x_one - 1 && y_two == y_one - 1) ||
                    (x_two == x_one - 1 && y_two == y_one + 1) ||
                    (x_two == x_one + 1 && y_two == y_one) ||
                    (x_two == x_one - 1 && y_two == y_one) ||
                    (x_two == x_one && y_two == y_one + 1) ||
                    (x_two == x_one && y_two == y_one - 1) ){
                    table().playerOne().setHP( table().playerOne().getHP() - 1 );
                    if(table().playerOne().getHP() == 0) emit playerTwoWon();
                }
            }
            else {
                if( (x_two == x_one + 1 && y_two == y_one + 1) ||
                    (x_two == x_one + 1 && y_two == y_one - 1) ||
                    (x_two == x_one - 1 && y_two == y_one - 1) ||
                    (x_two == x_one - 1 && y_two == y_one + 1) ||
                    (x_two == x_one + 1 && y_two == y_one) ||
                    (x_two == x_one - 1 && y_two == y_one) ||
                    (x_two == x_one && y_two == y_one + 1) ||
                    (x_two == x_one && y_two == y_one - 1) ){
                    table().playerOne().setHP( table().playerOne().getHP() - 1 );
                    table().playerTwo().setHP( table().playerTwo().getHP() - 1 );
                    if( table().playerOne().getHP() == 0 && table().playerTwo().getHP() == 0 ) emit draw();
                    else if( table().playerOne().getHP() == 0) emit playerTwoWon();
                    else if( table().playerTwo().getHP() == 0) emit playerOneWon();
                }
            }
            break;
    }
}

bool FightingHamsterRobotsModel::shoot(Direction dir, int player){
    int x_one = table().playerOne().getX();
    int y_one = table().playerOne().getY();
    int x_two = table().playerTwo().getX();
    int y_two = table().playerTwo().getY();
    switch(dir){
        case UP:
            if(player == 1){
                for(int i = x_one; i >= 0; i--){
                    if( i == x_two && y_one == y_two) return true;
                }
                return false;
            }
            else{
                for(int i = x_two; i >= 0; i--){
                    if( i == x_one && y_one == y_two) return true;
                }
                return false;
            }
            break;
        case DOWN:
            if(player == 1){
                for(int i = x_one; i < table().size(); i++){
                    if( i == x_two && y_one == y_two) return true;
                }
                return false;
            }
            else{
                for(int i = x_two; i < table().size(); i++){
                    if( i == x_one && y_one == y_two) return true;
                }
                return false;
            }
            break;
        case LEFT:
            if(player == 1){
                for(int i = y_one; i >= 0; i--){
                    if( i == y_two && x_one == x_two) return true;
                }
                return false;
            }
            else{
                for(int i = y_two; i >= 0; i--){
                    if( i == y_one && x_one == x_two) return true;
                }
                return false;
            }
            break;
        case RIGHT:
            if(player == 1){
                for(int i = y_one; i < table().size(); i++){
                    if( i == y_two && x_one == x_two) return true;
                }
                return false;
            }
            else{
                for(int i = y_two; i < table().size(); i++){
                    if( i == y_one && x_one == x_two) return true;
                }
                return false;
            }
            break;
    }
    return false;
}

void FightingHamsterRobotsModel::newGameM(int size){
    _currentPlayer = 1;
    table().playerOne().setX( size/2);
    table().playerTwo().setX( size/2);
    table().playerOne().setY( size/2 - 2);
    table().playerTwo().setY( size/2 + 1);
    table().playerOne().setHP(3);
    table().playerTwo().setHP(3);
    table().playerOne().setDir(UP);
    table().playerTwo().setDir(UP);
    table().playerOne().clearCm();
    table().playerTwo().clearCm();

    table().setTableSize(size);
    table().setTable();
}
