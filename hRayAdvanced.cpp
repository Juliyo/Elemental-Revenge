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

void hRayAdvanced::CreateBody() {

}

hRayAdvanced::hRayAdvanced(): Collisionable((Entity*)this) {
    draw=false;
    animationDurante = new Animation();
    setCast(1);
    setCD(4);
    
    printf("llego a textura del rayo HRAYADVANCED\n");
    if(!hTexture.loadFromFile("resources/Textures/rayo.png")){
        exit(0);
    }
    animationDurante->setSpriteSheet("resources/Textures/rayo.png");
    printf("termino a textura del rayo HRAYADVANCED\n");
    
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

std::string hRayAdvanced::getClassName() {

}

hRayAdvanced::~hRayAdvanced() {
}

void hRayAdvanced::cast(sf::Vector2f posicion, Hud *hud, float cdRayoAvanzadoPausa) {

    if((clockCd.getTiempo()+cdRayoAvanzadoPausa) > getCD() || primerCast){
        primerCast=false;
        draw=true;
        
        hSprite.setPosition(Motor2D::Instance()->getMousePosition().x,Motor2D::Instance()->getMousePosition().y);
        tiempoCast.restart();

    }
}
void hRayAdvanced::DrawWithOutInterpolation(){
	DrawAnimationWithOut(hSprite.getPosition() );
}