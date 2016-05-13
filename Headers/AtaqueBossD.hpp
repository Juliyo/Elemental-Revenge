/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AtaqueBossD.hpp
 * Author: julio
 *
 * Created on 13 de mayo de 2016, 18:47
 */

#ifndef ATAQUEBOSSD_HPP
#define ATAQUEBOSSD_HPP

#include "../Headers/Hechizo.hpp"
#include "../Motor/Collisionable.hpp"
#include "../Motor/Motor2D.hpp"

class AtaqueBossD : public Hechizo, public Collisionable{
public:
    AtaqueBossD();
    virtual ~AtaqueBossD();
    
    void CreateBody() override;
    std::string getClassName() override;
    
    Animation **currentAnimation;
    Animation *animationInicio;
    Animation *animationFin;
    
    void cast(sf::Vector2f pos, int numeroBol);
    void DrawWithInterpolation(float interpolation);
    void Colision();
    void ComprobarSiMuerto();
    void Update2(sf::Vector2f velocity, sf::Time elapsedTime);

private:
    Reloj *explosionTiempo;
};

#endif /* ATAQUEBOSSD_HPP */

