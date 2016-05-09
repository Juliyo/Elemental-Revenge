/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AtaqueBossA.hpp
 * Author: joselu
 *
 * Created on 3 de mayo de 2016, 10:04
 */

#ifndef ATAQUEBOSSA_HPP
#define ATAQUEBOSSA_HPP

#include "SFML/Graphics/CircleShape.hpp"

#include "Render.hpp"
#include "PhysicsState.hpp"
#include "../Motor/Motor2D.hpp"
#include "Animation.hpp"

class AtaqueBossA : public Render, public PhysicsState {
public:
    AtaqueBossA();
    AtaqueBossA(const AtaqueBossA& orig);
    virtual ~AtaqueBossA();
    
    
    Animation *animationAtaque;
    Motor2D *motor;

    float angleshot2=0.0f;
    
    void Update2(sf::Vector2f velocity, sf::Time elapsedTime);

    
    
    void Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer);
    void RenderDisparo(float interpolation);
    
    
    
private:

};

#endif /* DISPAROENEMIGO_HPP */

