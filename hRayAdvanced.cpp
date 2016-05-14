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
#include "../States/InGame.hpp"

void hRayAdvanced::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;
    bodyDef.type = b2_dynamicBody; 
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth()/2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::HECHIZO;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::ENEMIGO;
    body->CreateFixture(&fixtureDef);
}

hRayAdvanced::hRayAdvanced(): Collisionable((Entity*)this) {
    draw=false;
    animationDurante = new Animation();
    setCast(1);
    setCD(20.f);
    
   
    if(!hTexture.loadFromFile("resources/Textures/rayo.png")){
        exit(0);
    }
    animationDurante->setSpriteSheet("resources/Textures/rayo.png");
   
    
        animationDurante->addFrame(sf::IntRect(0,0,480,291));
    animationDurante->addFrame(sf::IntRect(480,0,480,291));
    animationDurante->addFrame(sf::IntRect(960,0,480,291));
    animationDurante->addFrame(sf::IntRect(1440,0,480,291));

    animationDurante->addFrame(sf::IntRect(0,291,480,291));
    animationDurante->addFrame(sf::IntRect(480,291,480,291));
    animationDurante->addFrame(sf::IntRect(960,291,480,291));
    animationDurante->addFrame(sf::IntRect(1440,291,480,291));

    animationDurante->addFrame(sf::IntRect(0,582,480,291));
    animationDurante->addFrame(sf::IntRect(480,582,480,291));
    animationDurante->addFrame(sf::IntRect(960,582,480,291));
    animationDurante->addFrame(sf::IntRect(1440,582,480,291));

    animationDurante->addFrame(sf::IntRect(0,873,480,291));
    animationDurante->addFrame(sf::IntRect(480,873,480,291));
    animationDurante->addFrame(sf::IntRect(960,873,480,291));
    animationDurante->addFrame(sf::IntRect(1440,873,480,291));

    animationDurante->addFrame(sf::IntRect(0,1164,480,291));
    animationDurante->addFrame(sf::IntRect(480,1164,480,291));
    animationDurante->addFrame(sf::IntRect(960,1164,480,291));
    animationDurante->addFrame(sf::IntRect(1440,1164,480,291));
    
    animationDurante->addFrame(sf::IntRect(0,1455,480,291));
    animationDurante->addFrame(sf::IntRect(480,1455,480,291));
    animationDurante->addFrame(sf::IntRect(960,1455,480,291));
    animationDurante->addFrame(sf::IntRect(1440,1455,480,291));
    
    animationDurante->addFrame(sf::IntRect(0,1746,480,291));
    animationDurante->addFrame(sf::IntRect(480,1746,480,291));
    animationDurante->addFrame(sf::IntRect(960,1746,480,291));
    animationDurante->addFrame(sf::IntRect(1440,1746,480,291));

    currentAnimation = &animationDurante;
    InicializarAnimatedSprite(sf::seconds(1.f/29),true,false);
    //SetScaleAnimation(0.6f,0.6f);
    SetOriginAnimatedSprite(240,145);
    SetOriginColision(240,145);
    SetRectangleColision(120,163,274,378);
    CreateBody();
    setDamage(4.f);
}

std::string hRayAdvanced::getClassName() {
    return "hRayAdvanced";
}

hRayAdvanced::~hRayAdvanced() {
    delete animationDurante;
    animationDurante = nullptr;
    
    currentAnimation=nullptr;
}

void hRayAdvanced::cast(sf::Vector2f posicion, Hud *hud, float cdRayoAvanzadoPausa) {

    if((clockCd.getTiempo()+cdRayoAvanzadoPausa) > getCD() || primerCast){
        body->SetActive(true);
        SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/Ravanzado.wav");
        primerCast=false;
        draw=true;
        sf::Vector2f pos(Motor2D::Instance()->getMousePosition().x,Motor2D::Instance()->getMousePosition().y);
        hSprite.setPosition(pos.x,pos.y);
        body->SetTransform(tmx::SfToBoxVec(pos),0);
        tiempoCast.restart();
    }
}
void hRayAdvanced::DrawWithOutInterpolation(){
	DrawAnimationWithOut(hSprite.getPosition() );
}