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


class hWaterAdvanced:public Hechizo {
public:
    hWaterAdvanced();
    hWaterAdvanced(const hWaterAdvanced& orig);
    virtual ~hWaterAdvanced();
    void cast(sf::Vector2f , sf::RenderWindow *mWindow);
    void UpdateHechizo(sf::Vector2f velocity, sf::Time elapsedTime);
    void setDibujar(bool NuevoDibujar);
    void DrawWithInterpolation(sf::RenderWindow& window, float interpolation);
    
    sf::Clock tiempoInicio;
    
    Animation **currentAnimation;
    Animation *animationDurante;
private:
    
};

#endif /* HWATERADVANCED_HPP */

