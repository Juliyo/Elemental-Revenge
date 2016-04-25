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


class Collisionable {
public:
    //Un objeto collisionable recibe el puntero al entity que representa
    Collisionable(Entity* ent);     
    virtual ~Collisionable();
    
    void CreateDynamicBody();

    void SetRectangleColision(float x, float y, float w, float h);
    void SetOriginColision(float x, float y);
    
    BoundingBox GetRectangleColisionAbsolute() const;
    
    //Obtiene el bounding de la proxima posicion del jugador
    BoundingBox CalculateNextRect(const sf::Time& elapsedTime); 
    
    //Obtiene la profundidad de una colision (No lo usamos)
    int GetXDepth(const BoundingBox& rec);  
    int GetYDepth(const BoundingBox& rec);

    //virtual void OnColision(std::vector<Colision::Type> type) = 0;
    
    b2Body  *body;

protected:
    
    //Puntero al bounding box de la entidad collisionable
    BoundingBox* rectColision;
    Entity* entity;
    //Origin del sprite, en caso de que no se de valor sera 0,0
    sf::Vector2f entOrigin = sf::Vector2f(0,0);
    
    //Metodos que llaman al intersects de sfml y devuelve true si intersecciona
    bool CheckColision(const Collisionable& ent, const sf::Time& elapsedTime);
    bool CheckColision(const BoundingBox& rec, const sf::Time& elapsedTime);

    bool CheckColision(const Collisionable& ent);
    bool CheckColision(const BoundingBox& rec);
    
    /******Variables para el motor de físicas*****/
    b2BodyDef *bodyDef;         //Objeto que representaria a nuestro sprite en el motor de físicas
        
    b2PolygonShape *shape;      //Representa un cuadrado o un circulo
    
    b2FixtureDef *fixtureDef;   //Añade una shape al BodyDef y define unas propiedades
                                //fisicas. p ej: friccion, densidad
    
    b2World *physicWorld;       //Puntero al objeto principal del motor
    
};

#endif /* COLLISIONABLE_HPP */

