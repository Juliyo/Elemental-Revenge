/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayAdvanced.cpp
 * Author: zimuu
 * 
 * Created on 11 de marzo de 2016, 23:04
 */

#include "../Headers/hRayAdvanced.hpp"

hRayAdvanced::hRayAdvanced() {
    draw=false;
    animationDurante = new Animation();
    setCast(1);
    setCD(3);
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
    animationDurante->setSpriteSheet(hTexture);
    
    animationDurante->addFrame(sf::IntRect(0,0,960,582));
    animationDurante->addFrame(sf::IntRect(960,0,960,582));
    animationDurante->addFrame(sf::IntRect(960*2,0,960,582));
    animationDurante->addFrame(sf::IntRect(960*3,0,960,582));
    animationDurante->addFrame(sf::IntRect(960*4,0,960,582));
    
    animationDurante->addFrame(sf::IntRect(0,582,960,582));
    animationDurante->addFrame(sf::IntRect(960,582,960,582));
    animationDurante->addFrame(sf::IntRect(960*2,582,960,582));
    animationDurante->addFrame(sf::IntRect(960*3,582,960,582));
    animationDurante->addFrame(sf::IntRect(960*4,582,960,582));
    
    
    animationDurante->addFrame(sf::IntRect(0,582*2,960,582));
    animationDurante->addFrame(sf::IntRect(960,582*2,960,582));
    animationDurante->addFrame(sf::IntRect(960*2,582*2,960,582));
    animationDurante->addFrame(sf::IntRect(960*3,582*2,960,582));
    animationDurante->addFrame(sf::IntRect(960*4,582*2,960,582));
    
    animationDurante->addFrame(sf::IntRect(0,582*3,960,582));
    animationDurante->addFrame(sf::IntRect(960,582*3,960,582));
    animationDurante->addFrame(sf::IntRect(960*2,582*3,960,582));
    animationDurante->addFrame(sf::IntRect(960*3,582*3,960,582));
    animationDurante->addFrame(sf::IntRect(960*4,582*3,960,582));
    
    animationDurante->addFrame(sf::IntRect(0,582*4,960,582));
    animationDurante->addFrame(sf::IntRect(960,582*4,960,582));
    animationDurante->addFrame(sf::IntRect(960*2,582*4,960,582));
    animationDurante->addFrame(sf::IntRect(960*3,582*4,960,582));
    animationDurante->addFrame(sf::IntRect(960*4,582*4,960,582));
    
    animationDurante->addFrame(sf::IntRect(0,582*5,960,582));
    animationDurante->addFrame(sf::IntRect(960,582*5,960,582));
    animationDurante->addFrame(sf::IntRect(960*2,582*5,960,582));
    animationDurante->addFrame(sf::IntRect(960*3,582*5,960,582));
    animationDurante->addFrame(sf::IntRect(960*4,582*5,960,582));
    
    

    
    currentAnimation = &animationDurante;
    InicializarAnimatedSprite(sf::seconds(1.f/29),true,false);
    SetScale(0.6f,0.6f);
    SetOriginAnimatedSprite(475,392);
    
}

hRayAdvanced::hRayAdvanced(const hRayAdvanced& orig) {
}

hRayAdvanced::~hRayAdvanced() {
}

void hRayAdvanced::cast(sf::Vector2f posicion) {

    if(tiempoCd.getElapsedTime().asSeconds()>hCd || primerCast){
        primerCast=false;
        draw=true;
        
        hSprite.setPosition(Motor2D::Instance()->getMousePosition());
        tiempoCast.restart();
        tiempoCd.restart();
    }
 

   
}
void hRayAdvanced::DrawWithOutInterpolation(){
	DrawAnimationWithOut(hSprite.getPosition() );
}