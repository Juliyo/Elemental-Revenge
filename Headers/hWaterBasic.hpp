/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hWaterBasic.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 23:06
 */

#ifndef HWATERBASIC_HPP
#define HWATERBASIC_HPP

#include "Hechizo.hpp"
#include "../Motor/Motor2D.hpp"
#include "Hud.hpp"


class hWaterBasic:public Hechizo, public Collisionable {
public:
    hWaterBasic();
    virtual ~hWaterBasic();
    std::string getClassName() override;
    void CreateBody() override;

    void cast(sf::Vector2f, Hud *hud);
    void DrawWithInterpolation( float interpolation);
    void Update(sf::Vector2f velocity, sf::Time elapsedTime, float playerV);
    void setDibujar(bool NuevoDibujar);
    
    Animation *animation;
};

#endif /* HWATERBASIC_HPP */