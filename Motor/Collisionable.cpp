/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Collisionable.cpp
 * Author: julio
 * 
 * Created on 22 de abril de 2016, 15:40
 */

#include "Collisionable.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"
#include "../Otros/tmxHelper.hpp"
#include "../States/InGame.hpp"
#include "../Otros/Dummy.hpp"


Collisionable::Collisionable(Entity* ent) {
    entity = ent;
    rectColision = new BoundingBox(0,0,50,50);
}

Collisionable::~Collisionable() {
    delete rectColision;
    rectColision = NULL;
}

void Collisionable::CreateDynamicBody() {
    physicWorld = InGame::Instance()->physicWorld;
    
    //Creamos un objeto dinamico
    //bodyDef = new b2BodyDef();
    bodyDef.type = b2_dynamicBody; 
    bodyDef.position.Set(tmx::SfToBoxFloat(entity->GetPosition().x),tmx::SfToBoxFloat(entity->GetPosition().y));
    bodyDef.fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    //shape = new b2PolygonShape();
    shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    //fixtureDef = new b2FixtureDef();
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    body->CreateFixture(&fixtureDef);
    
}

void Collisionable::CreateKinematicBody(){
    /*physicWorld = InGame::Instance()->physicWorld;
    bodyDef = new b2BodyDef();
    bodyDef->type = b2_kinematicBody;
    bodyDef->position.Set(tmx::SfToBoxFloat(entity->GetPosition().x),tmx::SfToBoxFloat(entity->GetPosition().y));
    bodyDef->fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(bodyDef);
    
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    shape = new b2PolygonShape();
    shape->SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;
    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.0f;
    body->CreateFixture(fixtureDef);*/
}

void Collisionable::SetOriginColision(float x, float y) {
    entOrigin.x = x;
    entOrigin.y = y;
}

BoundingBox Collisionable::GetRectangleColisionAbsolute() const {
    return BoundingBox(
            this->entity->GetPosition().x + entOrigin.x + rectColision->GetTopLeft().x,
            this->entity->GetPosition().y + entOrigin.x + rectColision->GetTopLeft().y,
            rectColision->GetWidth(),
            rectColision->GetHeight()
            );
}

BoundingBox Collisionable::CalculateNextRect(const sf::Time& elapsedTime) {

    BoundingBox auxRect = GetRectangleColisionAbsolute();

    auxRect.SetX(auxRect.GetTopLeft().x + entity->GetSpeed().x * elapsedTime.asSeconds());
    auxRect.SetY(auxRect.GetTopLeft().y + entity->GetSpeed().y * elapsedTime.asSeconds());

    return auxRect;
}

void Collisionable::SetRectangleColision(float x, float y, float w, float h) {
    rectColision->Set(x, y, w, h);
}

bool Collisionable::CheckColision(const Collisionable& ent, const sf::Time& elapsedTime) {
    return CalculateNextRect(elapsedTime).Intersects(ent.GetRectangleColisionAbsolute());
}
bool Collisionable::CheckColision(const BoundingBox& rec, const sf::Time& elapsedTime) {
    return CalculateNextRect(elapsedTime).Intersects(rec);
}

bool Collisionable::CheckColision(const BoundingBox& rec) {
    return GetRectangleColisionAbsolute().Intersects(rec);
}

bool Collisionable::CheckColision(const Collisionable& ent) {
    return GetRectangleColisionAbsolute().Intersects(ent.GetRectangleColisionAbsolute());
}
int Collisionable::GetXDepth(const BoundingBox& rec){
    BoundingBox bPlayer = GetRectangleColisionAbsolute();
    if(bPlayer.IsInside(rec.GetBottomRight())){
        return abs(rec.GetBottomRight().x - bPlayer.GetTopLeft().x);
    }else if(bPlayer.IsInside(rec.GetBottomLeft())){
        return abs(rec.GetBottomLeft().x - bPlayer.GetTopRight().x);
    }else if(bPlayer.IsInside(rec.GetTopLeft())){
        return abs(rec.GetTopLeft().x - bPlayer.GetBottomRight().x);
    }else{
        return abs(rec.GetTopRight().x - bPlayer.GetBottomLeft().x);
    }
}
int Collisionable::GetYDepth(const BoundingBox& rec){
    BoundingBox bPlayer = GetRectangleColisionAbsolute();
    if(bPlayer.IsInside(rec.GetBottomRight())){
        return abs(rec.GetBottomRight().y - bPlayer.GetTopLeft().y);
    }else if(bPlayer.IsInside(rec.GetBottomLeft())){
        return abs(rec.GetBottomLeft().y - bPlayer.GetTopRight().y);
    }else if(bPlayer.IsInside(rec.GetTopLeft())){
        return abs(rec.GetTopLeft().y - bPlayer.GetBottomRight().y);
    }else{
        return abs(rec.GetTopRight().y - bPlayer.GetBottomLeft().y);
    }
}



