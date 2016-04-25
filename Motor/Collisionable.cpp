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


Collisionable::Collisionable(Entity* ent, BoundingBox *rP) {
    entity = ent;
    rectColision = rP;
    physicWorld = InGame::Instance()->physicWorld;
    bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(ent->GetPosition().x,ent->GetPosition().y);
    bodyDef->fixedRotation = true;
    body = physicWorld->CreateBody(bodyDef);
    shape = new b2PolygonShape();
    shape->SetAsBox(tmx::SfToBoxFloat(GetRectangleColisionAbsolute().GetWidth() / 2.f), tmx::SfToBoxFloat(GetRectangleColisionAbsolute().GetHeight() / 2.f));
    
    fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;
    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.0f;
    body->CreateFixture(fixtureDef);
}

/*Collisionable::Collisionable(const Collisionable& orig) {
}*/

Collisionable::~Collisionable() {
}

BoundingBox Collisionable::GetRectangleColisionAbsolute() const {
    return BoundingBox(
            this->entity->GetPosition().x - entOrigin.x + rectColision->GetTopLeft().x,
            this->entity->GetPosition().y - entOrigin.y + rectColision->GetTopLeft().y,
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

/*std::vector<Colision::Type> Collisionable::TypeOfColision(const BoundingBox& rec, const sf::Time& elapsedTime) {
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

}*/

/*Colision::Type Collisionable::TypeOfColision(const BoundingBox& rec, const sf::Time& elapsedTime) {
    BoundingBox entRec = CalculateNextRect(elapsedTime);
    std::vector<Colision::Type> colisions;

    //***** Comprobamos en los ejes en los que colisiona
    if (rec.GetTopLeft().x >= entRec.GetTopLeft().x && rec.GetTopLeft().x <= entRec.GetTopRight().x)
        colisions.push_back(Colision::Type::LEFT);
    if (rec.GetTopRight().x >= entRec.GetTopLeft().x && rec.GetTopRight().x <= entRec.GetTopRight().x)
        colisions.push_back(Colision::Type::RIGHT);
    if (rec.GetTopLeft().y <= entRec.GetBottomLeft().y && rec.GetTopLeft().y >= entRec.GetTopLeft().y) // Suelo
        colisions.push_back(Colision::Type::BOTTOM);
    if (rec.GetBottomLeft().y <= entRec.GetBottomLeft().y && rec.GetBottomLeft().y >= entRec.GetTopLeft().y) // Techo
        colisions.push_back(Colision::Type::TOP);



    //***** COLISION 1 EJE: ya lo tenemos
    if (colisions.size() == 1)
        return colisions.at(0);

        //***** COLISION 3 EJES: si hay 2 verticales y 1 horizontal, será el horizontal, y viceversa.
    else if (colisions.size() == 3) {
        if (colisions.at(0) == Colision::Type::LEFT && colisions.at(1) == Colision::Type::BOTTOM && colisions.at(2) == Colision::Type::TOP)
            return Colision::Type::LEFT;
        else if (colisions.at(0) == Colision::Type::RIGHT && colisions.at(1) == Colision::Type::BOTTOM && colisions.at(2) == Colision::Type::TOP)
            return Colision::Type::RIGHT;
        else if (colisions.at(0) == Colision::Type::LEFT && colisions.at(1) == Colision::Type::RIGHT && colisions.at(2) == Colision::Type::TOP)
            return Colision::Type::TOP;
        else if (colisions.at(0) == Colision::Type::LEFT && colisions.at(1) == Colision::Type::RIGHT && colisions.at(2) == Colision::Type::BOTTOM)
            return Colision::Type::BOTTOM;
    }
        //***** COLISION 2 EJES: comprobación estadística respecto a la posición anterior
    else {
        BoundingBox rectPrev = GetRectangleColisionAbsolute();
        sf::Vector2f posAux;

        // Si es la esquina TOP-LEFT, comprobamos con la BOTTOM-RIGHT del Sprite, pero primero miramos la VELOCIDAD
        if (colisions.at(0) == Colision::Type::LEFT && colisions.at(1) == Colision::Type::BOTTOM) {
            posAux = rectPrev.GetBottomRight();

            if (posAux.y > rec.GetTopLeft().y && posAux.y < rec.GetTopLeft().y + 3.f)
                return Colision::Type::BOTTOM;
            else if (posAux.y < rec.GetTopLeft().y + 25.f)
                return Colision::Type::BOTTOM;
            else
                return Colision::Type::LEFT;

        }

        if (colisions.at(0) == Colision::Type::RIGHT && colisions.at(1) == Colision::Type::BOTTOM) {
            posAux = rectPrev.GetBottomLeft();

            if (posAux.y < rec.GetTopRight().y && posAux.y < rec.GetTopLeft().y + 3.f)
                return Colision::Type::BOTTOM;
            else if (posAux.y < rec.GetTopLeft().y + 25.f)
                return Colision::Type::BOTTOM;
            else
                return Colision::Type::RIGHT;
        }

        if (colisions.at(0) == Colision::Type::LEFT && colisions.at(1) == Colision::Type::TOP) {
            posAux = rectPrev.GetTopRight();

            if (posAux.y > rec.GetBottomLeft().y + 1.3f) //Si está arriba a la derecha de la esquina
                return Colision::Type::TOP;
            else
                return Colision::Type::LEFT;
        }

        if (colisions.at(0) == Colision::Type::RIGHT && colisions.at(1) == Colision::Type::TOP) {
            posAux = rectPrev.GetTopLeft();

            if (posAux.y < rec.GetBottomRight().y - 1.3f) //Si está arriba a la derecha de la esquina
                return Colision::Type::TOP;
            else
                return Colision::Type::RIGHT;
        }
    }
}*/


