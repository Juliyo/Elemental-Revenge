/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hWaterAdvanced.cpp
 * Author: joselu
 * 
 * Created on 11 de marzo de 2016, 13:01
 */

#include "hWaterAdvanced.hpp"

hWaterAdvanced::hWaterAdvanced() {

    animationDurante = new Animation();

    if (!hTexture.loadFromFile("resources/Textures/AguaHardcore.png")) {

        //comentario error
        exit(0);
    }
    /* SetTexture(hTexture);
     SetTextureRect(sf::IntRect(0, 91, 108, 69));*/
    //hSprite.setPosition(-10000, -10000);

    //********************************************

    animationDurante->setSpriteSheet(hTexture);
    animationDurante->addFrame(sf::IntRect(5, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(100, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(200, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(300, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(400, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(505, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(605, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(705, 97, 95, 60));
    
    currentAnimation = &animationDurante;
    
    InicializarAnimatedSprite(sf::seconds(0.05f), true, false);
    SetOriginAnimatedSprite(95 / 2, 60 / 2);

    //***********************************************
    clockCd.restart();

}

hWaterAdvanced::hWaterAdvanced(const hWaterAdvanced& orig) {
}

hWaterAdvanced::~hWaterAdvanced() {
}

void hWaterAdvanced::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {

    if (clockCd.getElapsedTime().asSeconds() > 5 || primerCast == true) {
        primerCast = false;
        clockCd.restart();
        tiempoInicio.restart();
        SetPosition(posicion);
        sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
        float angleShot = atan2(mousePosition.y - GetPosition().y, mousePosition.x - GetPosition().x);
        angleshot2 = angleShot; //so it goes in a straight line
        //SetRotation(angleShot * 180 / 3.14);
        tiempoCast.restart();
        dibujar = true;
    }

}
void hWaterAdvanced::DrawWithInterpolation(sf::RenderWindow& window, float interpolation){
    DrawAnimation(window, GetPreviousPosition(), GetPosition(), interpolation);
}

void hWaterAdvanced::UpdateHechizo(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    Update(elapsedTime);
}

void hWaterAdvanced::setDibujar(bool NuevoDibujar) {
    dibujar = NuevoDibujar;
}