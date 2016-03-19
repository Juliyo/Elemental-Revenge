/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hFireAdvanced.cpp
 * Author: joselu
 * 
 * Created on 14 de marzo de 2016, 13:06
 */

#include "hFireAdvanced.hpp"

hFireAdvanced::hFireAdvanced() {

    if (!hTexture.loadFromFile("resources/Textures/girofuego.png")) {

        //comentario error
        exit(0);
    }
    SetTexture(hTexture);
    SetOrigin(125, 124);
    SetScale(0.3, 0.3);
    SetPosition(-10000, -10000);
    setCD(5.f);
    setCast(2.f);
    actualSize = sf::Vector2f(0.3, 0.3);

    primerCast = true;

}

hFireAdvanced::hFireAdvanced(const hFireAdvanced& orig) {
}

hFireAdvanced::~hFireAdvanced() {
}

void hFireAdvanced::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {



    hSprite.setPosition(posicion.x, posicion.y);
    hSprite.rotate(90);

}

void hFireAdvanced::DrawWithInterpolation(sf::RenderWindow& window, float interpolation, const sf::Vector2f& posPrev, const sf::Vector2f& posNew) {
    Draw90(window, posPrev, posNew, interpolation);
}
