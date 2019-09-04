#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    _health = 3;
    _cm.resize(5);
    _cmN = 0;
    _dir = UP;
}

void Player::setX(int val){
    _x = val;
}

void Player::setY(int val){
    _y = val;
}

void Player::setHP(int val){
    _health = val;
}

void Player::setDir(Direction val){
    _dir = val;
}

void Player::addCm(Command cm){
    if(_cmN < 5){
        _cm[_cmN] = cm;
        _cmN++;
    }
}

void Player::removeLastCm(){
    _cmN--;
}

void Player::clearCm(){
    _cm.clear();
    _cm.resize(5);
    _cmN = 0;
}
