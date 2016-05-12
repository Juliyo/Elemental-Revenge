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
#include "../States/InGame.hpp"

AtaqueBossA::AtaqueBossA(): Collisionable((Entity*)this) {
    
    motor = Motor2D::Instance();
    
    animationAtaque = new Animation();
    animationFin = new Animation();
    
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
    
    animationFin->setSpriteSheet("resources/Textures/fuegoMuriendoAzul.png");
    animationFin->addFrame(sf::IntRect(0,0,172,159));
    animationFin->addFrame(sf::IntRect(172,0,172,159));
    animationFin->addFrame(sf::IntRect(344,0,172,159));
    animationFin->addFrame(sf::IntRect(516,0,172,159));
    animationFin->addFrame(sf::IntRect(688,0,172,159));
    
    
    currentAnimation = &animationAtaque;
    InicializarAnimatedSprite(sf::seconds(0.02f), true, false);
    
    Render::SetScaleAnimation(0.4, 0.4);
    Render::SetOriginAnimatedSprite(76, 74);
    SetOriginColision(76*0.4,74*0.4);
    SetRectangleColision(0,0,152*0.4,148*0.4);
    CreateBody();
    
    setDamage(3.f);
    //Render::GetSpriteAnimated().setColor(sf::Color::Blue);
    SetEstado(Estado::ID::Vivo);
    explosionTiempo = new Reloj();
    
}

AtaqueBossA::~AtaqueBossA() {
}

void AtaqueBossA::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;
    //Creamos un objeto dinamico
    bodyDef.type = b2_dynamicBody; 
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::DISPAROENE;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::BOUNDARY | Filtro::_entityCategory::PLAYER;
    body->CreateFixture(&fixtureDef);
}

std::string AtaqueBossA::getClassName() {
    return "AtaqueA";
}

void AtaqueBossA::Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer) {
    body->SetActive(true);
    SetEstado(Estado::ID::Vivo);
    PhysicsState::SetPosition(vector);
    body->SetTransform(tmx::SfToBoxVec(vector),0);
    currentAnimation = &animationAtaque;
    Render::SetOriginAnimatedSprite(76, 74);
    Render::SetFrameTime(sf::seconds(0.02f));
    Render::SetScaleAnimation(0.4, 0.4);
    float angleShot = atan2(vectorPlayer.y-vector.y, vectorPlayer.x-vector.x);
    angleshot2 = angleShot; //so it goes in a straight line
}

void AtaqueBossA::Colision() {
    if (GetEstado() == Estado::Vivo) {
        //SetPosition(sf::Vector2f(0,0));
        //body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(0,0)),0);
        explosionTiempo->restart();
        currentAnimation = &animationFin;
        Render::SetOriginAnimatedSprite(86, 79);
        Render::SetFrameTime(sf::seconds(0.04));
        Render::SetLooped(false);
        Render::SetScaleAnimation(0.8, 0.8);
        SetEstado(Estado::ID::Muriendo);
    }
}

void AtaqueBossA::ComprobarSiMuerto() {
    if (explosionTiempo->getTiempo() > 0.2) {
        SetEstado(Estado::ID::Muerto);
    }
}

void AtaqueBossA::RenderDisparo(float interpolation) {

    Draw(GetPreviousPosition(), GetPosition(), interpolation);
}


void AtaqueBossA::Update2(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    //Hay que setear al BodyDef el vector velocidad que hallamos calculado
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(velocity)*250.f));
    //Actualizamos la posicion del player con la posicion del bodyDef
    SetPosition(tmx::BoxToSfVec(body->GetPosition()));
}
