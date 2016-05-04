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


    animationAtaque->setSpriteSheet("resources/Textures/sprite-agua.png");
    animationAtaque->addFrame(sf::IntRect(735, 0, 147, 147));
    animationAtaque->addFrame(sf::IntRect(735, 147, 147, 147));
    animationAtaque->addFrame(sf::IntRect(735, 294, 147, 147));
    animationAtaque->addFrame(sf::IntRect(735, 441, 147, 147));
    animationAtaque->addFrame(sf::IntRect(735, 588, 147, 147));
    animationAtaque->addFrame(sf::IntRect(588, 0, 147, 147));
    animationAtaque->addFrame(sf::IntRect(588, 147, 147, 147));
    animationAtaque->addFrame(sf::IntRect(588, 294, 147, 147));
    animationAtaque->addFrame(sf::IntRect(588, 441, 147, 147));
    animationAtaque->addFrame(sf::IntRect(588, 588, 147, 147));
    animationAtaque->addFrame(sf::IntRect(441, 0, 147, 147));
    animationAtaque->addFrame(sf::IntRect(441, 147, 147, 147));
    animationAtaque->addFrame(sf::IntRect(441, 294, 147, 147));
    animationAtaque->addFrame(sf::IntRect(441, 441, 147, 147));
    animationAtaque->addFrame(sf::IntRect(441, 588, 147, 147));
    animationAtaque->addFrame(sf::IntRect(294, 0, 147, 147));
    animationAtaque->addFrame(sf::IntRect(294, 147, 147, 147));
    animationAtaque->addFrame(sf::IntRect(294, 294, 147, 147));
    animationAtaque->addFrame(sf::IntRect(294, 441, 147, 147));
    animationAtaque->addFrame(sf::IntRect(294, 588, 147, 147));
    animationAtaque->addFrame(sf::IntRect(147, 0, 147, 147));
    animationAtaque->addFrame(sf::IntRect(147, 147, 147, 147));
    animationAtaque->addFrame(sf::IntRect(147, 294, 147, 147));
    animationAtaque->addFrame(sf::IntRect(147, 441, 147, 147));
    animationAtaque->addFrame(sf::IntRect(147, 588, 147, 147));
    animationAtaque->addFrame(sf::IntRect(0, 0, 147, 147));
    animationAtaque->addFrame(sf::IntRect(0, 147, 147, 147));
    animationAtaque->addFrame(sf::IntRect(0, 294, 147, 147));
    animationAtaque->addFrame(sf::IntRect(0, 441, 147, 147));
    animationAtaque->addFrame(sf::IntRect(0, 588, 147, 147));
    InicializarAnimatedSprite(sf::seconds(0.5f / 29), true, false);
    SetOriginAnimatedSprite(0, 147 / 2);
    SetScale(0.5f, 0.5f);
    
    
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
