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
#endif

hWaterBasic::hWaterBasic() {
}

hWaterBasic::hWaterBasic(const hWaterBasic& orig) {
}

hWaterBasic::~hWaterBasic() {
    
if(!hTexture.loadFromFile("resources/Textures/bolaFuego.png")){
       
       //comentario error
       exit(0);
   }
   hSprite.setTexture(hTexture);
   hSprite.setTextureRect(sf::IntRect(0, 0, 100, 81));
   hSprite.setScale(0.2,0.2);
   hSprite.setPosition(-10000, -10000);
    
}
void hWaterBasic::cast(Player player, sf::RenderWindow* mWindow ){
    
    sf::Vector2f mousePosition = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
    sf::Vector2f playerposition = player.getPosition();
    hSprite.setPosition(playerposition);
    float angleShot = atan2(mousePosition.y - playerposition.y, mousePosition.x - playerposition.x);
    angleshot2 = angleShot;
    hSprite.setRotation(angleShot*180/3.14);
               
}

