/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 23:05
 */

#include "../Headers/hRayBasic.hpp"
#include "../Headers/Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
hRayBasic::hRayBasic() {
    draw = false;
    hTexture.loadFromFile("resources/Textures/rayo.png");
    renderState.SetTexture(hTexture);
    renderState.SetTextureRect(sf::IntRect(0,0,67,233));
    renderState.SetOrigin(41,223);
    /*hSprite.setTexture(hTexture);
    hSprite.setTextureRect(sf::IntRect(0,0,67,233));
    hSprite.setOrigin(41,223);*/
   // hSprite.rotate(-90.f);
}

hRayBasic::hRayBasic(const hRayBasic& orig) {
}

hRayBasic::~hRayBasic() {
}

void hRayBasic::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {
    draw=true;
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    //hSprite.setPosition(posicion);
    float angleShot = atan2(mousePosition.y - posicion.y, mousePosition.x - posicion.x);
    angleshot2 = angleShot; //so it goes in a straight line
    renderState.GetSprite().setRotation((angleShot * 180 / 3.14)+90);
   
}

