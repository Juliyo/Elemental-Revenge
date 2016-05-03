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


#include "../Motor/Motor2D.hpp"

class DisparoEnemigo {
public:
    DisparoEnemigo();
    DisparoEnemigo(const DisparoEnemigo& orig);
    virtual ~DisparoEnemigo();
    
    Motor2D *motor;

    float angleshot2=0.0f;

    sf::CircleShape disparo;
    
    void Disparar(float x, float y);
    void Update();
    void RenderDisparo();
    
    
    
private:

};

#endif /* DISPAROENEMIGO_HPP */

