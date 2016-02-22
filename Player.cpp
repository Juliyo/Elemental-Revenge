
#include"../Headers/Player.hpp"

Player::Player(float velocidad){
    mVelocidad = velocidad;
}

void Player::setVida(int vid){
    mVida = vid;
}
int Player::getVida(){
    return mVida;
}
void Player::setVelocidad(float velocidad){
    mVelocidad = velocidad;
}
float Player::getVelocidad(){
    return mVelocidad;
}

