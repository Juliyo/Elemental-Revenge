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
        SetOrigin(125,124);
        SetScale(0.45, 0.45);
        SetPosition(-10000, -10000);

    primerCast=true;
    
}

hFireAdvanced::hFireAdvanced(const hFireAdvanced& orig) {
}

hFireAdvanced::~hFireAdvanced() {
}

void hFireAdvanced::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {


    
    hSprite.setPosition(posicion.x, posicion.y);
    hSprite.rotate(90);

}

void hFireAdvanced::DrawWithInterpolation(sf::RenderWindow& window, float interpolation, const sf::Vector2f& posPrev, const sf::Vector2f& posNew){
	Draw90(window,posPrev, posNew , interpolation);
}
