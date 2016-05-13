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
    setCD(1);
    
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
    SetScaleAnimation(0.6f,0.6f);
    SetOriginAnimatedSprite(475,392);
    SetOriginColision(475*0.6,392*0.6);
    SetRectangleColision(397*0.6,332*0.6,176*0.6,113*0.6);
    CreateBody();
    setDamage(4.f);
}

std::string hRayAdvanced::getClassName() {
    return "hRayAdvanced";
}

hRayAdvanced::~hRayAdvanced() {
    delete animationDurante;
    animationDurante;
    
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