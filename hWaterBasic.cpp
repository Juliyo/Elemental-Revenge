/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hWaterBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 23:06
 */

#include "../Headers/hWaterBasic.hpp"
#ifdef _WIN32
#include <Windows.h>
#include <iostream>
#endif

hWaterBasic::hWaterBasic() {
        
if(!hTexture.loadFromFile("resources/Textures/bolaFuego.png")){
       
       //comentario error
       exit(0);
   }
   hSprite.setTexture(hTexture);
   hSprite.setTextureRect(sf::IntRect(0, 0, 100, 81));
   hSprite.setScale(0.5,0.5);
   hSprite.setPosition(-10000, -10000);
}

hWaterBasic::hWaterBasic(const hWaterBasic& orig) {
}

hWaterBasic::~hWaterBasic() {

    
}
void hWaterBasic::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow ){
    
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
   // sf::Vector2f playerposition = player->getPosition();
    hSprite.setPosition(posicion.x+20,posicion.y+35);
    float angleShot = atan2(mousePosition.y - posicion.y, mousePosition.x - posicion.x);
    angleshot2 = angleShot;
    hSprite.setRotation(angleShot*180/3.14);
    tiempoCast.restart();
    dibujar=true;
    std::cout <<"ENTRA";
               
}

void hWaterBasic::setDibujar(bool NuevoDibujar){
    dibujar=NuevoDibujar;
}