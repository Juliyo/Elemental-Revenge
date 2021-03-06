/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AtaqueBossD.cpp
 * Author: julio
 * 
 * Created on 13 de mayo de 2016, 18:47
 */

#include "AtaqueBossD.hpp"
#include "States/InGame.hpp"

AtaqueBossD::AtaqueBossD(): Collisionable((Entity*)this){
    animationInicio = new Animation();
    animationFin = new Animation();
    
    animationInicio->setSpriteSheet("resources/Textures/FuegoSpriteSheetAzul.png");
    animationInicio->addFrame(sf::IntRect(0, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 0, 152, 148));

//    animationInicio->addFrame(sf::IntRect(0, 148, 152, 148));
//    animationInicio->addFrame(sf::IntRect(152, 148, 152, 148));
//    animationInicio->addFrame(sf::IntRect(304, 148, 152, 148));
//    animationInicio->addFrame(sf::IntRect(456, 148, 152, 148));
//    animationInicio->addFrame(sf::IntRect(608, 148, 152, 148));
//
//    animationInicio->addFrame(sf::IntRect(0, 296, 152, 148));
//    animationInicio->addFrame(sf::IntRect(152, 296, 152, 148));
//    animationInicio->addFrame(sf::IntRect(304, 296, 152, 148));
//    animationInicio->addFrame(sf::IntRect(456, 296, 152, 148));
//    animationInicio->addFrame(sf::IntRect(608, 296, 152, 148));
//
//    animationInicio->addFrame(sf::IntRect(0, 444, 152, 148));
//    animationInicio->addFrame(sf::IntRect(152, 444, 152, 148));
//    animationInicio->addFrame(sf::IntRect(304, 444, 152, 148));
//    animationInicio->addFrame(sf::IntRect(456, 444, 152, 148));
//    animationInicio->addFrame(sf::IntRect(608, 444, 152, 148));
//
//    animationInicio->addFrame(sf::IntRect(0, 592, 152, 148));
//    animationInicio->addFrame(sf::IntRect(152, 592, 152, 148));
//    animationInicio->addFrame(sf::IntRect(304, 592, 152, 148));
//    animationInicio->addFrame(sf::IntRect(456, 592, 152, 148));
//    animationInicio->addFrame(sf::IntRect(608, 592, 152, 148));
//
//    animationInicio->addFrame(sf::IntRect(0, 740, 152, 148));
//    animationInicio->addFrame(sf::IntRect(152, 740, 152, 148));
//    animationInicio->addFrame(sf::IntRect(304, 740, 152, 148));
//    animationInicio->addFrame(sf::IntRect(456, 740, 152, 148));
//    animationInicio->addFrame(sf::IntRect(608, 740, 152, 148));
    
    animationFin->setSpriteSheet("resources/Textures/fuegoMuriendoAzul.png");
    
    animationFin->addFrame(sf::IntRect(0,0,172,159));
    animationFin->addFrame(sf::IntRect(172,0,172,159));
    animationFin->addFrame(sf::IntRect(344,0,172,159));
    animationFin->addFrame(sf::IntRect(516,0,172,159));
    animationFin->addFrame(sf::IntRect(688,0,172,159));
    
    currentAnimation = &animationInicio;
    
    
    Render::InicializarAnimatedSprite(sf::seconds(0.02f), true, false);
    Render::SetOriginAnimatedSprite(76, 74);
    SetOriginColision(14,15);
    Render::SetScaleAnimation(0.2, 0.2);
    SetRectangleColision(0,0,30,29);
    CreateBody();
    SetEstado(Estado::ID::Vivo);
    explosionTiempo = new Reloj();
    
    Hechizo::setDamage(1.f);
}


AtaqueBossD::~AtaqueBossD() {
}

void AtaqueBossD::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;
    //Creamos un objeto dinamico
    //bodyDef = new b2BodyDef();
    bodyDef.type = b2_dynamicBody; 
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    //bodyDef.bullet = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    //circleShape = new b2CircleShape();
    circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::DISPAROENE;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::PLAYER | Filtro::_entityCategory::BOUNDARY;
    body->CreateFixture(&fixtureDef);
}

std::string AtaqueBossD::getClassName() {
    return "AtaqueD";
}

void AtaqueBossD::cast(sf::Vector2f pos, int numeroBola) {
    SoundManager *sonido = SoundManager::Instance();
    //sonido->setVolumen("resources/Sounds/Fbasico.wav",SoundManager::Instance()->volumen);
    sonido->play("resources/Sounds/Fbasico.wav");
    currentAnimation = &animationInicio;
    Render::SetOriginAnimatedSprite(76, 74);
    Render::SetFrameTime(sf::seconds(0.02f));
    Render::SetScaleAnimation(0.2, 0.2);
    SetEstado(Estado::ID::Vivo);
    body->SetActive(true);
    SetPosition(pos);
    float angleShot = numeroBola * 36.f;
    angleshot2 = angleShot; //so it goes in a straight line
    body->SetTransform(tmx::SfToBoxVec(pos),0);
}

void AtaqueBossD::Colision() {
    if(GetEstado() == Estado::Vivo){
        //SetPosition(sf::Vector2f(0,0));
        //body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(0,0)),0);
        explosionTiempo->restart();
        currentAnimation = &animationFin;
        Render::SetOriginAnimatedSprite(86, 79);
        Render::SetFrameTime(sf::seconds(0.15f));
        Render::SetLooped(false);
        Render::SetScaleAnimation(0.4, 0.4);
        SetEstado(Estado::ID::Muriendo);
    }
}

void AtaqueBossD::ComprobarSiMuerto() {
    if (explosionTiempo->getTiempo() > 0.5f) {
        SetEstado(Estado::ID::Muerto);
    }
}

void AtaqueBossD::DrawWithInterpolation(float interpolation) {
    Draw(GetPreviousPosition(), GetPosition(), interpolation);
}

void AtaqueBossD::Update2(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    //sf::Vector2f movement(0.f, 0.f);
     //Hay que setear al BodyDef el vector velocidad que hallamos calculado
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(velocity)*200.f));
    //Actualizamos la posicion del player con la posicion del bodyDef
    SetPosition(tmx::BoxToSfVec(body->GetPosition()));
    //Update(elapsedTime);
}
