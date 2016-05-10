/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hFireAdvanced.cpp
 * Author: joselu
 * 
 * Created on 14 de marzo de 2016, 13:06
 */

#include "hFireAdvanced.hpp"
#include "../States/InGame.hpp"

void hFireAdvanced::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;
    
    //Creamos un objeto dinamico
    //bodyDef = new b2BodyDef();
    bodyDef.type = b2_staticBody; 
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    //circleShape = new b2CircleShape();
    circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);
    /*sf::CircleShape *rs = new sf::CircleShape();
    rs->setPosition(InGame::Instance()->player->GetPosition().x,InGame::Instance()->player->GetPosition().y*-1);
    rs->setRadius(rectColision->GetWidth() / 2.f);
    rs->setFillColor(sf::Color::Transparent);
    rs->setOutlineColor(sf::Color::Blue);
    rs->setOrigin(rectColision->GetWidth() / 2.f,rectColision->GetHeight() / 2.f);
    rs->setOutlineThickness(2);
    InGame::Instance()->player->shapesFuego->push_back(rs);*/
    //shape = new b2PolygonShape();
    //shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    //fixtureDef = new b2FixtureDef();
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.7f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::HECHIZO;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::ENEMIGO | Filtro::_entityCategory::BOUNDARY;
    body->CreateFixture(&fixtureDef);
}

hFireAdvanced::hFireAdvanced(): Collisionable((Entity*)this) {


    SetTexture("resources/Textures/girofuego.png");
    SetOrigin(125, 124);
    SetScale(0.1, 0.1);
    SetPosition(-10000, -10000);
    setCD(5.f);
    setCast(2.f);
    hDamage = 0;
    actualSize = sf::Vector2f(0.3, 0.3);
    primerCast = true;
    SetRectangleColision(0,0,250,248);
    SetOriginColision(250/2,248/2);
    
    CreateBody();

}

std::string hFireAdvanced::getClassName() {
    return "hFireAdvanced";
}


hFireAdvanced::~hFireAdvanced() {
    //delete rectColision;
}

void hFireAdvanced::cast(sf::Vector2f posicion) {
    body->SetActive(true);
    printf("llego me cago en todo\n");
    SoundManager *sonido = SoundManager::Instance();
    sonido->play("resources/Sounds/Favanzado.wav");
    hSprite.setPosition(posicion.x, posicion.y);
    body->SetTransform(tmx::SfToBoxVec(posicion),0);
    hSprite.setRotation(90);

}

void hFireAdvanced::DrawWithInterpolation( float interpolation, const sf::Vector2f& posPrev, const sf::Vector2f& posNew) {
   
    Draw90( posPrev, posNew, interpolation);
}
