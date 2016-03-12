/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hFireBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 12:45
 */

#include "../Headers/hFireBasic.hpp"

hFireBasic::hFireBasic() {


    if (!hTexture.loadFromFile("resources/Textures/bolaFuego.png")) {

        //comentario error
        exit(0);
    }
    hSprite.setTexture(hTexture);
    hSprite.setTextureRect(sf::IntRect(0, 0, 100, 81));
    hSprite.setScale(0.2, 0.2);
    hSprite.setPosition(-10000, -10000);

}

hFireBasic::hFireBasic(const hFireBasic& orig) {

}

hFireBasic::~hFireBasic() {
}

void hFireBasic::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {

    printf("lanzo el fuego");




    //hFuegoBasico[contFuego].hSprite.setRotation(0);
    hSprite.setPosition(posicion);
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    float angleShot = atan2(mousePosition.y - hSprite.getPosition().y,
            mousePosition.x - hSprite.getPosition().x);
    angleshot2 = angleShot; //so it goes in a straight line
    hSprite.setRotation(angleShot * 180 / 3.14);

}

