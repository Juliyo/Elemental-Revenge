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
    hSprite.setScale(2,2);
    hSprite.setPosition(0, 0);
    hSprite.setOrigin(100/2,81/2);
    
}

hRayAdvanced::hRayAdvanced(const hRayAdvanced& orig) {
}

hRayAdvanced::~hRayAdvanced() {
}

void hRayAdvanced::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {

    if(tiempoCd.getElapsedTime().asSeconds()>3 || primerCast){
        primerCast=false;
        draw=true;
        sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
        hSprite.setPosition(mousePosition);
        tiempoCast.restart();
        tiempoCd.restart();
    }


   
}
