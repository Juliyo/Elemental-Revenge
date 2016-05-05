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

void hFireAdvanced::CreateBody() {

}

hFireAdvanced::hFireAdvanced(): Collisionable((Entity*)this) {


    SetTexture("resources/Textures/girofuego.png");
    SetOrigin(125, 124);
    SetScaleAnimation(0.1, 0.1);
    SetPosition(-10000, -10000);
    setCD(5.f);
    setCast(2.f);
    //actualSize = sf::Vector2f(0.3, 0.3);
    primerCast = true;

}

std::string hFireAdvanced::getClassName() {

}


hFireAdvanced::~hFireAdvanced() {
}

void hFireAdvanced::cast(sf::Vector2f posicion) {



    hSprite.setPosition(posicion.x, posicion.y);
    hSprite.setRotation(90);

}

void hFireAdvanced::DrawWithInterpolation( float interpolation, const sf::Vector2f& posPrev, const sf::Vector2f& posNew) {
   
    Draw90( posPrev, posNew, interpolation);
}
