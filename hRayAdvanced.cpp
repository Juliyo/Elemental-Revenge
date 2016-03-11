/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayAdvanced.cpp
 * Author: joselu
 * 
 * Created on 11 de marzo de 2016, 23:04
 */

#include "../Headers/hRayAdvanced.hpp"
#include "../Headers/Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>
hRayAdvanced::hRayAdvanced() {
    
       
    if(!hTexture.loadFromFile("resources/Textures/rayo.png")){
        
        //comentario error
        exit(0);
    }
    hSprite.setTexture(hTexture);
    hSprite.setTextureRect(sf::IntRect(0, 0, 100, 81));
    hSprite.setScale(0.2,0.2);
    hSprite.setPosition(-10000, -10000);
    
    
}

hRayAdvanced::hRayAdvanced(const hRayAdvanced& orig) {
}

hRayAdvanced::~hRayAdvanced() {
}

void hRayAdvanced::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {
    printf("Entra en el rayo B");
        
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));

    //hSprite.setPosition(mousePosition);
   
    SetPosition(mousePosition);
    /*
    draw=true;
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    //hSprite.setPosition(posicion);
    float angleShot = atan2(mousePosition.y - posicion.y, mousePosition.x - posicion.x);
    
    
    angleShot = (angleShot * 180 / 3.14)+90;
    SetAngle(angleshot2, angleShot);
    
    
    angleshot2 = angleShot; //so it goes in a straight line
    */
    //GetSprite().setRotation((angleShot * 180 / 3.14)+90);
    
}