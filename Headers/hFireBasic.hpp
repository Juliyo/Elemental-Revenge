/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hFireBasic.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 12:45
 */

#ifndef HFIREBASIC_HPP
#define HFIREBASIC_HPP

#include "../Headers/Hechizo.hpp"
#include "../Motor/Motor2D.hpp"

class hFireBasic : public Hechizo, public Collisionable {
public:
    hFireBasic();
    virtual ~hFireBasic();
    void Clear();
    void CreateBody() override;
    std::string getClassName() override;
    
    void cast(sf::Vector2f);
    void DrawWithInterpolation(float interpolation);
    void Colision();
    void ComprobarSiMuerto();
    void Update2(sf::Vector2f velocity, sf::Time elapsedTime);
    Animation **currentAnimation;
    Animation *animationInicio;
    Animation *animationFin;
private:
    Reloj *explosionTiempo;
};

#endif /* HFIREBASIC_HPP */