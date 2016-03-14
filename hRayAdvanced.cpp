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
    draw=false;
       
    if(!hTexture.loadFromFile("resources/Textures/rayo.png")){
        
        //comentario error
        exit(0);
    }
    /*
    hSprite.setTexture(hTexture);
    hSprite.setTextureRect(sf::IntRect(0, 0, 100, 81));
    hSprite.setScale(2,2);
    hSprite.setPosition(0, 0);
    hSprite.setOrigin(100/2,81/2);*/
    animation.setSpriteSheet(hTexture);
    animation.addFrame(sf::IntRect(0,0,64,233));
    animation.addFrame(sf::IntRect(64,0,64,233));
    animation.addFrame(sf::IntRect(128,0,64,233));
    animation.addFrame(sf::IntRect(192,0,64,233));
    animation.addFrame(sf::IntRect(256,0,64,233));
    animation.addFrame(sf::IntRect(320,0,64,233));
    animation.addFrame(sf::IntRect(384,0,64,233));
    animation.addFrame(sf::IntRect(448,0,64,233));

    InicializarAnimatedSprite(sf::seconds(0.5f/8),true,false);
    SetOriginAnimatedSprite(41,233);
    
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
void hRayAdvanced::DrawWithOutInterpolation(sf::RenderWindow& window){
	DrawAnimationWithOut(window,hSprite.getPosition() );
}
