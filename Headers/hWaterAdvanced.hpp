/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hWaterAdvanced.hpp
 * Author: joselu
 *
 * Created on 11 de marzo de 2016, 13:01
 */

#ifndef HWATERADVANCED_HPP
#define HWATERADVANCED_HPP

#include "Hechizo.hpp"
#include "../Motor/Motor2D.hpp"
#include "../Motor/Reloj.hpp"
#include "Hud.hpp"


class hWaterAdvanced:public Hechizo, public Collisionable {
public:
    hWaterAdvanced();
    virtual ~hWaterAdvanced();
    std::string getClassName() override;
    void CreateBody() override;

    void cast(sf::Vector2f pos, Hud *hud, float cdAguaAvanzadoPausa);
    void UpdateHechizo(sf::Vector2f velocity, sf::Time elapsedTime);
    void setDibujar(bool NuevoDibujar);
    void DrawWithInterpolation( float interpolation);
    
    Reloj tiempoInicio;
    
    Animation **currentAnimation;
    Animation *animationDurante;
private:
    
};

#endif /* HWATERADVANCED_HPP */

