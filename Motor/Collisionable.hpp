/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Collisionable.hpp
 * Author: julio
 *
 * Created on 22 de abril de 2016, 15:40
 */

#ifndef COLLISIONABLE_HPP
#define COLLISIONABLE_HPP
#include "../Otros/BoundingBox.h"
#include "../Entities/Entity.hpp"
#include <Box2D/Box2D.h>

namespace Colision {

    enum Type {
        RIGHT, LEFT, BOTTOM, TOP, NONE
    };
}

class Collisionable {
public:
    Collisionable(Entity* ent);
    //Collisionable(const Collisionable& orig);
    virtual ~Collisionable();

    void SetRectangleColision(float x, float y, float w, float h);
    void SetOriginColision(float x, float y){
        entOrigin.x = x;
        entOrigin.y = y;
    }
    
    BoundingBox GetRectangleColisionAbsolute() const;
    BoundingBox CalculateNextRect(const sf::Time& elapsedTime);
    
    int GetXDepth(const BoundingBox& rec);
    int GetYDepth(const BoundingBox& rec);

    virtual void OnColision(std::vector<Colision::Type> type) = 0;
    
    b2Body  *body;

protected:

    BoundingBox* rectColision;
    Entity* entity;
    sf::Vector2f entOrigin;
    

    bool CheckColision(const Collisionable& ent, const sf::Time& elapsedTime);
    bool CheckColision(const BoundingBox& rec, const sf::Time& elapsedTime);

    bool CheckColision(const Collisionable& ent);
    bool CheckColision(const BoundingBox& rec);
    
    b2BodyDef *bodyDef;
    b2PolygonShape *shape;
    b2FixtureDef *fixtureDef;
    b2World *physicWorld;
    
    //std::vector<Colision::Type> TypeOfColision(const BoundingBox& rec, const sf::Time& elapsedTime);
};

#endif /* COLLISIONABLE_HPP */

