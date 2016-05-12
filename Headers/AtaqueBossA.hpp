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

#include "../Headers/Hechizo.hpp"
#include "../Motor/Collisionable.hpp"
#include "../Motor/Motor2D.hpp"
#include "Animation.hpp"


class AtaqueBossA : public Hechizo, public Collisionable {
public:
    AtaqueBossA();
    virtual ~AtaqueBossA();
    
    void CreateBody() override;
    std::string getClassName() override;    //AtaqueA

    Animation *animationAtaque;
    Animation *animationFin;
    Animation **currentAnimation;
    
    Motor2D *motor;

    float angleshot2=0.0f;
    
    void Update2(sf::Vector2f velocity, sf::Time elapsedTime);
    
    void Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer);
    void RenderDisparo(float interpolation);
    
    void Colision();

    void ComprobarSiMuerto();
    
private:
    Reloj *explosionTiempo;
};

#endif /* DISPAROENEMIGO_HPP */

