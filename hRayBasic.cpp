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
#include <math.h>
hRayBasic::hRayBasic() {
    draw = false;
    hTexture.loadFromFile("resources/Textures/rayo.png");
    SetTexture(hTexture);
    SetTextureRect(sf::IntRect(0,0,67,233));
    SetOrigin(41,223);
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
    angleShot = (angleShot * 180 / 3.14)+90;
    SetAngle(angleshot2, angleShot);
    
    angleshot2 = angleShot; //so it goes in a straight line
    
    //GetSprite().setRotation((angleShot * 180 / 3.14)+90);
   
}
void hRayBasic::DrawWithInterpolation(sf::RenderWindow& window, float interpolation, PhysicsState *physicsState){
	Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition() , &anglePrev, &angleNew, interpolation);
}

