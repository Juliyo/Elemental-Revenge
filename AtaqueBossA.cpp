/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AtaqueBossA.cpp
 * Author: joselu
 * 
 * Created on 3 de mayo de 2016, 10:04
 */

#include "AtaqueBossA.hpp"

AtaqueBossA::AtaqueBossA() {
    
    motor = Motor2D::Instance();
    
    animationAtaque = new Animation();



    animationAtaque = new Animation();
    animationAtaque->setSpriteSheet("resources/Textures/FuegoSpriteSheetAzul.png");
    animationAtaque->addFrame(sf::IntRect(0, 0, 152, 148));
    animationAtaque->addFrame(sf::IntRect(152, 0, 152, 148));
    animationAtaque->addFrame(sf::IntRect(304, 0, 152, 148));
    animationAtaque->addFrame(sf::IntRect(456, 0, 152, 148));
    animationAtaque->addFrame(sf::IntRect(608, 0, 152, 148));

    animationAtaque->addFrame(sf::IntRect(0, 148, 152, 148));
    animationAtaque->addFrame(sf::IntRect(152, 148, 152, 148));
    animationAtaque->addFrame(sf::IntRect(304, 148, 152, 148));
    animationAtaque->addFrame(sf::IntRect(456, 148, 152, 148));
    animationAtaque->addFrame(sf::IntRect(608, 148, 152, 148));

    animationAtaque->addFrame(sf::IntRect(0, 296, 152, 148));
    animationAtaque->addFrame(sf::IntRect(152, 296, 152, 148));
    animationAtaque->addFrame(sf::IntRect(304, 296, 152, 148));
    animationAtaque->addFrame(sf::IntRect(456, 296, 152, 148));
    animationAtaque->addFrame(sf::IntRect(608, 296, 152, 148));

    animationAtaque->addFrame(sf::IntRect(0, 444, 152, 148));
    animationAtaque->addFrame(sf::IntRect(152, 444, 152, 148));
    animationAtaque->addFrame(sf::IntRect(304, 444, 152, 148));
    animationAtaque->addFrame(sf::IntRect(456, 444, 152, 148));
    animationAtaque->addFrame(sf::IntRect(608, 444, 152, 148));

    animationAtaque->addFrame(sf::IntRect(0, 592, 152, 148));
    animationAtaque->addFrame(sf::IntRect(152, 592, 152, 148));
    animationAtaque->addFrame(sf::IntRect(304, 592, 152, 148));
    animationAtaque->addFrame(sf::IntRect(456, 592, 152, 148));
    animationAtaque->addFrame(sf::IntRect(608, 592, 152, 148));

    animationAtaque->addFrame(sf::IntRect(0, 740, 152, 148));
    animationAtaque->addFrame(sf::IntRect(152, 740, 152, 148));
    animationAtaque->addFrame(sf::IntRect(304, 740, 152, 148));
    animationAtaque->addFrame(sf::IntRect(456, 740, 152, 148));
    animationAtaque->addFrame(sf::IntRect(608, 740, 152, 148));
    InicializarAnimatedSprite(sf::seconds(0.02f), true, false);
    SetOriginAnimation(0, 147 / 2);
    SetScaleAnimation(0.8, 0.8);
    
    
}

AtaqueBossA::AtaqueBossA(const AtaqueBossA& orig) {
}

AtaqueBossA::~AtaqueBossA() {
}

void AtaqueBossA::Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer) {

    
    PhysicsState::SetPosition(vector);

    float angleShot = atan2(vectorPlayer.y-vector.y, vectorPlayer.x-vector.x);
    angleshot2 = angleShot; //so it goes in a straight line
    SetRotation(angleshot2);
    
}

void AtaqueBossA::RenderDisparo(float interpolation) {

    Draw(GetPreviousPosition(), GetPosition(), interpolation);
}


void AtaqueBossA::Update2(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    PhysicsState::Update(elapsedTime);
}
