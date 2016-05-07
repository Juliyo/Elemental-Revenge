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
#include "Hud.hpp"

void hWaterAdvanced::CreateBody() {

}


hWaterAdvanced::hWaterAdvanced(): Collisionable((Entity*)this) {

    animationDurante = new Animation();
    animationDurante->setSpriteSheet("resources/Textures/AguaHardcore.png");
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

    setCD(10.f);
    //***********************************************
    clockCd.restart();

}

std::string hWaterAdvanced::getClassName() {

}

hWaterAdvanced::~hWaterAdvanced() {
}

void hWaterAdvanced::cast(sf::Vector2f posicion, Hud *hud, float cdAguaAvanzadoPausa) {

    if ((clockCd.getTiempo()+cdAguaAvanzadoPausa) > hCd || primerCast == true) {
        primerCast = false;
        tiempoInicio.restart();
        SetPosition(posicion);
        float angleShot = Motor2D::Instance()->getAngleShot(posicion);
        angleshot2 = angleShot;
        
        //SetRotation(angleShot * 180 / 3.14);
        tiempoCast.restart();
        dibujar = true;
    }

}
void hWaterAdvanced::DrawWithInterpolation( float interpolation){
    DrawAnimation( GetPreviousPosition(), GetPosition(), interpolation);
}

void hWaterAdvanced::UpdateHechizo(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    Update(elapsedTime);
}

void hWaterAdvanced::setDibujar(bool NuevoDibujar) {
    dibujar = NuevoDibujar;
}