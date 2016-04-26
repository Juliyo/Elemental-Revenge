/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Entity.hpp
 * Author: julio
 *
 * Created on 22 de abril de 2016, 16:06
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Headers/PhysicsState.hpp"
#include "../Headers/Render.hpp"

class Entity : public PhysicsState, public Render{
public:
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
    
    //virtual void Update(const sf::Time elapsedTime) = 0;
    
private:

};

#endif /* ENTITY_HPP */

