/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 23:05
 */

#include "../Headers/hRayBasic.hpp"
#include "Entities/Player.hpp"
#include "Motor/Motor2D.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>
#include "States/InGame.hpp"

void hRayBasic::CreateBody() {
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
    shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);
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
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.7f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::HECHIZO;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::ENEMIGO;
    body->CreateFixture(&fixtureDef);
}

hRayBasic::hRayBasic(): Collisionable((Entity*)this) {
    
    draw = false;
    animation = new Animation();
    animationDurante = new Animation();
    PrimeraAnimacion = new Animation();
    setCD(5);
    hDamage = 3;
    setCast(3);
    if (!hTexture.loadFromFile("resources/Textures/RayoSpriteSheet.png")) {

        //comentario error
        exit(0);
    }
    // hSprite.setTexture(hTexture);
    //SetPosition()
    PrimeraAnimacion->setSpriteSheet("resources/Textures/RayoSpriteSheet.png");
    animationDurante->setSpriteSheet("resources/Textures/RayoSpriteSheet.png");

    animationDurante->addFrame(sf::IntRect(0, 445, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(0, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(0, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(0, 890, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(89, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89, 890, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 890, 89, 445));

    //PrimeraAnimacion->addFrame(sf::IntRect(0,0,89,445));

    animationDurante->addFrame(sf::IntRect(89 * 3, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 3, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 3, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 4, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 4, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 4, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 5, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 5, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 5, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 6, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 6, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 6, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 7, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 7, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 7, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 8, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 8, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 8, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 9, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 9, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 9, 890, 89, 445));

    currentAnimation = &PrimeraAnimacion;
    InicializarAnimatedSprite(sf::seconds(0.5f / 8), true, false);
    SetOriginAnimatedSprite(40, -30);
    Collisionable::SetOriginColision(40,-30);
    CreateBody();
}


hRayBasic::~hRayBasic() {

}

std::string hRayBasic::getClassName() {
    return "hRayBasic";
}

void hRayBasic::cast(sf::Vector2f posicion) {

      /*if(!buffer.loadFromFile("resources/Sounds/Pistola.wav")){
        exit(0);
    }

    sound.setBuffer(buffer);
    sound.play();
*/
    if(primeraVez){
        SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/Rbasico.wav");
        primeraVez=false;
    }

    draw = true;
    float angleShot = Motor2D::Instance()->getAngleShot(posicion);

    angleShot = (angleShot * 180 / 3.14) + 270;
    SetAngle(angleshot2, angleShot);
    body->SetTransform(tmx::SfToBoxVec(posicion),angleShot);

    angleshot2 = angleShot; //so it goes in a straight line
}

void hRayBasic::stopSound() {
    SoundManager *sonido = SoundManager::Instance();
    sonido->stop("resources/Sounds/Rbasico.wav");
}


void hRayBasic::DrawWithInterpolation(float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew) {
    //std::cout<<"Llega"<<std::endl;
    DrawAnimation(posPrev, posNew, interpolation, &anglePrev, &angleNew);
}
void hRayBasic::update(){
    
}