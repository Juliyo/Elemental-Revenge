/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hWaterAdvanced.cpp
 * Author: joselu
 * 
 * Created on 11 de marzo de 2016, 13:01
 */

#include "hWaterAdvanced.hpp"
#include "Hud.hpp"
#include "States/InGame.hpp"

void hWaterAdvanced::CreateBody() {
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
    circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth()/2);
    sf::CircleShape *rs = new sf::CircleShape();
    rs->setPosition(entity->GetPosition());
    rs->setRadius(rectColision->GetWidth() / 2.f);
    rs->setFillColor(sf::Color::Transparent);
    rs->setOutlineColor(sf::Color::Red);
    rs->setOrigin(rectColision->GetWidth() / 2.f,rectColision->GetHeight() / 2.f);
    rs->setOutlineThickness(2);
    InGame::Instance()->player->shapesFuego->push_back(rs);
    //shape = new b2PolygonShape();
    //shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    //fixtureDef = new b2FixtureDef();
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::HECHIZO;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::ENEMIGO | Filtro::_entityCategory::HECHIZO;
    body->CreateFixture(&fixtureDef);
}


hWaterAdvanced::hWaterAdvanced(): Collisionable((Entity*)this) {

    animationDurante = new Animation();
    animationDurante->setSpriteSheet("resources/Textures/AguaHardcore.png");
    animationDurante->addFrame(sf::IntRect(5, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(100, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(200, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(300, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(400, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(505, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(605, 97, 95, 60));
    animationDurante->addFrame(sf::IntRect(705, 97, 95, 60));
    
    currentAnimation = &animationDurante;
    
    InicializarAnimatedSprite(sf::seconds(0.05f), true, false);
    SetOriginAnimatedSprite(95 / 2, 60 / 2);
    hDamage = 3;
    
    Collisionable::SetOriginColision(95 / 2,60 / 2);
    Collisionable::SetRectangleColision(7,99,99,155);
    CreateBody();
    setCD(10.f);
    //***********************************************
    clockCd.restart();

}

std::string hWaterAdvanced::getClassName() {
    return "hWaterAdvanced";
}

hWaterAdvanced::~hWaterAdvanced() {
    animationDurante=NULL;
    currentAnimation=NULL;
    //delete rectColision;
}

void hWaterAdvanced::cast(sf::Vector2f posicion, Hud *hud, float cdAguaAvanzadoPausa) {

    if ((clockCd.getTiempo()+cdAguaAvanzadoPausa) > hCd || primerCast == true) {
        SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/Aavanzado.wav");
        primerCast = false;
        tiempoInicio.restart();
        SetPosition(posicion);
        float angleShot = Motor2D::Instance()->getAngleShot(posicion);
        angleshot2 = angleShot;
        body->SetTransform(tmx::SfToBoxVec(posicion),0);
        //SetRotation(angleShot * 180 / 3.14);
        tiempoCast.restart();
        dibujar = true;
    }
}
void hWaterAdvanced::DrawWithInterpolation( float interpolation){
    DrawAnimation( GetPreviousPosition(), GetPosition(), interpolation);
}

void hWaterAdvanced::UpdateHechizo(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(velocity)*450.f));
    Update(elapsedTime);
}

void hWaterAdvanced::setDibujar(bool NuevoDibujar) {
    dibujar = NuevoDibujar;
}