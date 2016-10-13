/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AtaqueBossB.hpp
 * Author: joselu
 *
 * Created on 3 de mayo de 2016, 10:04
 */

#ifndef ATAQUEBOSSB_HPP
#define ATAQUEBOSSB_HPP

#include "SFML/Graphics/CircleShape.hpp"

#include "../Headers/Hechizo.hpp"
#include "../Motor/Collisionable.hpp"
#include "../Motor/Motor2D.hpp"
#include "Animation.hpp"


class AtaqueBossB  : public Hechizo, public Collisionable {
public:
    AtaqueBossB();

    virtual ~AtaqueBossB();
    
    std::string getClassName() override;
    void CreateBody() override;
    
    
   
    void DrawWithOutInterpolation();
    
    Animation *animationAtaque;
    Animation *animationDiana;
    Animation **currentAnimation;

    Motor2D *motor;
    
    float angleshot2=0.0f;
    
    void Update2(sf::Vector2f velocity, sf::Time elapsedTime);

    sf::CircleShape disparo;
    
    sf::Vector2f posCaida;
    bool marca=true;
    Reloj relojitomagico;
    
    void Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer);
    void RenderDisparo(float interpolation);
    
    
    
private:

};

#endif /* DISPAROENEMIGO_HPP */

