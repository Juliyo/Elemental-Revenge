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

Collisionable::Collisionable(Entity* ent) {
    entity = ent;
    rectColision = new BoundingBox(0, 0, 50, 50);
}

/*Collisionable::Collisionable(const Collisionable& orig) {
}*/

Collisionable::~Collisionable() {
}

BoundingBox Collisionable::GetRectangleColisionAbsolute() const {
    return BoundingBox(
            this->entity->GetPosition().x + rectColision->GetTopLeft().x,
            this->entity->GetPosition().y + rectColision->GetTopLeft().y,
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

bool Collisionable::CheckColision(const BoundingBox& rec) {
    return GetRectangleColisionAbsolute().Intersects(rec);
}

bool Collisionable::CheckColision(const Collisionable& ent) {
    return GetRectangleColisionAbsolute().Intersects(ent.GetRectangleColisionAbsolute());
}

std::vector<Colision::Type> Collisionable::TypeOfColision(const BoundingBox& rec, const sf::Time& elapsedTime) {
    BoundingBox entRec = CalculateNextRect(elapsedTime);
    std::vector<Colision::Type> colisions;

    if (rec.GetTopLeft().x >= entRec.GetTopLeft().x && rec.GetTopLeft().x <= entRec.GetTopRight().x)
        colisions.push_back(Colision::Type::LEFT);
    if (rec.GetTopRight().x >= entRec.GetTopLeft().x && rec.GetTopRight().x <= entRec.GetTopRight().x)
        colisions.push_back(Colision::Type::RIGHT);
    if (rec.GetTopLeft().y <= entRec.GetBottomLeft().y && rec.GetTopLeft().y >= entRec.GetTopLeft().y)
        colisions.push_back(Colision::Type::BOTTOM);
    if (rec.GetBottomLeft().y <= entRec.GetBottomLeft().y && rec.GetBottomLeft().y >= entRec.GetTopLeft().y) // Techo
        colisions.push_back(Colision::Type::TOP);
    
    return colisions;

}


