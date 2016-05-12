/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AtaqueBossB.cpp
 * Author: joselu
 * 
 * Created on 3 de mayo de 2016, 10:04
 */

#include "AtaqueBossB.hpp"

AtaqueBossB::AtaqueBossB() {
    
    motor = Motor2D::Instance();
    
    posCaida=sf::Vector2f(-1000,-1000);


    animationAtaque = new Animation();
    animationDiana = new Animation();
    
    animationDiana->setSpriteSheet("resources/Textures/diana.png");
    animationDiana->addFrame(sf::IntRect(0, 0, 108, 61));

animationAtaque->setSpriteSheet("resources/Textures/rayorojo.png");
    
    animationAtaque->addFrame(sf::IntRect(0,0,960,582));
    animationAtaque->addFrame(sf::IntRect(960,0,960,582));
    animationAtaque->addFrame(sf::IntRect(960*2,0,960,582));
    animationAtaque->addFrame(sf::IntRect(960*3,0,960,582));
    animationAtaque->addFrame(sf::IntRect(960*4,0,960,582));
    
    animationAtaque->addFrame(sf::IntRect(0,582,960,582));
    animationAtaque->addFrame(sf::IntRect(960,582,960,582));
    animationAtaque->addFrame(sf::IntRect(960*2,582,960,582));
    animationAtaque->addFrame(sf::IntRect(960*3,582,960,582));
    animationAtaque->addFrame(sf::IntRect(960*4,582,960,582));
    
    animationAtaque->addFrame(sf::IntRect(0,582*2,960,582));
    animationAtaque->addFrame(sf::IntRect(960,582*2,960,582));
    animationAtaque->addFrame(sf::IntRect(960*2,582*2,960,582));
    animationAtaque->addFrame(sf::IntRect(960*3,582*2,960,582));
    animationAtaque->addFrame(sf::IntRect(960*4,582*2,960,582));
    
    animationAtaque->addFrame(sf::IntRect(0,582*3,960,582));
    animationAtaque->addFrame(sf::IntRect(960,582*3,960,582));
    animationAtaque->addFrame(sf::IntRect(960*2,582*3,960,582));
    animationAtaque->addFrame(sf::IntRect(960*3,582*3,960,582));
    animationAtaque->addFrame(sf::IntRect(960*4,582*3,960,582));
    
    animationAtaque->addFrame(sf::IntRect(0,582*4,960,582));
    animationAtaque->addFrame(sf::IntRect(960,582*4,960,582));
    animationAtaque->addFrame(sf::IntRect(960*2,582*4,960,582));
    animationAtaque->addFrame(sf::IntRect(960*3,582*4,960,582));
    animationAtaque->addFrame(sf::IntRect(960*4,582*4,960,582));
    
    animationAtaque->addFrame(sf::IntRect(0,582*5,960,582));
    animationAtaque->addFrame(sf::IntRect(960,582*5,960,582));
    animationAtaque->addFrame(sf::IntRect(960*2,582*5,960,582));
    animationAtaque->addFrame(sf::IntRect(960*3,582*5,960,582));
    animationAtaque->addFrame(sf::IntRect(960*4,582*5,960,582));
    InicializarAnimatedSprite(sf::seconds(1.f/29),true,false);
    SetScale(0.6f,0.6f);
    SetOriginAnimatedSprite(54,30);
    
    currentAnimation = &animationDiana;
    
    
    disparo.setFillColor(sf::Color::Red);
    disparo.setRadius(30);
    
}

AtaqueBossB::AtaqueBossB(const AtaqueBossB& orig) {
}

AtaqueBossB::~AtaqueBossB() {
}

void AtaqueBossB::Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer) {

    

    posCaida=vectorPlayer;
    
    
  /*  float angleShot = atan2(vectorPlayer.y-vector.y, vectorPlayer.x-vector.x);
    angleshot2 = angleShot; //so it goes in a straight line
    SetRotation(angleshot2);*/
    
}

void AtaqueBossB::RenderDisparo(float interpolation) {

    Draw(GetPreviousPosition(), GetPosition(), interpolation);
}


void AtaqueBossB::Update2(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    PhysicsState::Update(elapsedTime);
}
