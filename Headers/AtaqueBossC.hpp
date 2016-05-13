/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AtaqueBossC.hpp
 * Author: joselu
 *
 * Created on 3 de mayo de 2016, 10:04
 */

#ifndef ATAQUEBOSSC_HPP
#define ATAQUEBOSSC_HPP


#include "../Headers/Hechizo.hpp"
#include "../Motor/Collisionable.hpp"
#include "../Motor/Motor2D.hpp"
#include "Animation.hpp"

class AtaqueBossC : public Hechizo, public Collisionable {
public:
    AtaqueBossC();
    virtual ~AtaqueBossC();
    
    void CreateBody() override;
    std::string getClassName() override;

    Animation *animationAtaque;
    Animation *animationFin;
    Animation **currentAnimation;
    
    Motor2D *motor;
    Reloj ClockResetEspiral;
    float cdResetEspiral=100.0f;

    float angleshot2=0.0f;
   

    sf::CircleShape disparo;
    
    
    void Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer);
    void RenderDisparo(float interpolation);
    
    void Colision();
    void ComprobarSiMuerto();
    
    
    
private:
    Reloj *explosionTiempo;
};

#endif /* DISPAROENEMIGO_HPP */

