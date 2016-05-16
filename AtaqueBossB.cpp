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
#include "../States/InGame.hpp"

void AtaqueBossB::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::DISPAROENE;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::PLAYER;
    body->CreateFixture(&fixtureDef);
}

AtaqueBossB::AtaqueBossB() : Collisionable((Entity*)this) {

    motor = Motor2D::Instance();

    posCaida = sf::Vector2f(-1000, -1000);


    animationAtaque = new Animation();
    animationDiana = new Animation();

    animationDiana->setSpriteSheet("resources/Textures/diana.png");
    animationDiana->addFrame(sf::IntRect(0, 0, 108, 61));

    animationAtaque->setSpriteSheet("resources/Textures/rayorojo.png");

    
        animationAtaque->addFrame(sf::IntRect(0,0,480,291));
    animationAtaque->addFrame(sf::IntRect(480,0,480,291));
    animationAtaque->addFrame(sf::IntRect(960,0,480,291));
    animationAtaque->addFrame(sf::IntRect(1440,0,480,291));

    animationAtaque->addFrame(sf::IntRect(0,291,480,291));
    animationAtaque->addFrame(sf::IntRect(480,291,480,291));
    animationAtaque->addFrame(sf::IntRect(960,291,480,291));
    animationAtaque->addFrame(sf::IntRect(1440,291,480,291));

    animationAtaque->addFrame(sf::IntRect(0,582,480,291));
    animationAtaque->addFrame(sf::IntRect(480,582,480,291));
    animationAtaque->addFrame(sf::IntRect(960,582,480,291));
    animationAtaque->addFrame(sf::IntRect(1440,582,480,291));

    animationAtaque->addFrame(sf::IntRect(0,873,480,291));
    animationAtaque->addFrame(sf::IntRect(480,873,480,291));
    animationAtaque->addFrame(sf::IntRect(960,873,480,291));
    animationAtaque->addFrame(sf::IntRect(1440,873,480,291));

    animationAtaque->addFrame(sf::IntRect(0,1164,480,291));
    animationAtaque->addFrame(sf::IntRect(480,1164,480,291));
    animationAtaque->addFrame(sf::IntRect(960,1164,480,291));
    animationAtaque->addFrame(sf::IntRect(1440,1164,480,291));
    
    animationAtaque->addFrame(sf::IntRect(0,1455,480,291));
    animationAtaque->addFrame(sf::IntRect(480,1455,480,291));
    animationAtaque->addFrame(sf::IntRect(960,1455,480,291));
    animationAtaque->addFrame(sf::IntRect(1440,1455,480,291));
    
    animationAtaque->addFrame(sf::IntRect(0,1746,480,291));
    animationAtaque->addFrame(sf::IntRect(480,1746,480,291));
    animationAtaque->addFrame(sf::IntRect(960,1746,480,291));
    animationAtaque->addFrame(sf::IntRect(1440,1746,480,291));
    InicializarAnimatedSprite(sf::seconds(1.f / 29), true, false);
    //SetScale(0.6f, 0.6f);
    SetOriginAnimatedSprite(54, 30);

    currentAnimation = &animationDiana;

    InicializarAnimatedSprite(sf::seconds(1.f / 29), true, false);
    SetOriginAnimatedSprite(240,145);
    SetOriginColision(240,145);
    SetRectangleColision(171,170,138,32);
    CreateBody();
    setDamage(4.f);

    disparo.setFillColor(sf::Color::Red);
    disparo.setRadius(30);

}

AtaqueBossB::~AtaqueBossB() {
}

void AtaqueBossB::Disparar(sf::Vector2f vector, sf::Vector2f vectorPlayer) {



    posCaida = vectorPlayer;

    body->SetTransform(tmx::SfToBoxVec(posCaida), 0);
    body->SetActive(false);
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

std::string AtaqueBossB::getClassName() {
    return "AtaqueB";
}