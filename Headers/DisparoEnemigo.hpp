/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisparoEnemigo.hpp
 * Author: joselu
 *
 * Created on 3 de mayo de 2016, 10:04
 */

#ifndef DISPAROENEMIGO_HPP
#define DISPAROENEMIGO_HPP

#include "SFML/Graphics/CircleShape.hpp"

#include "Render.hpp"
#include "PhysicsState.hpp"
#include "../Motor/Motor2D.hpp"

class DisparoEnemigo : public Render, public PhysicsState {
public:
    DisparoEnemigo();
    DisparoEnemigo(const DisparoEnemigo& orig);
    virtual ~DisparoEnemigo();
    
    Motor2D *motor;

    float angleshot2=0.0f;
    
    void Update2(sf::Vector2f velocity, sf::Time elapsedTime);

    sf::CircleShape disparo;
    
    
    void Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer);
    void RenderDisparo(float interpolation);
    
    
    
private:

};

#endif /* DISPAROENEMIGO_HPP */

