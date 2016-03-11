/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayBasic.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 23:05
 */

#ifndef HRAYBASIC_HPP
#define HRAYBASIC_HPP

#include "../Headers/Hechizo.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>


class hRayBasic:public Hechizo {
public:
    hRayBasic();
    hRayBasic(const hRayBasic& orig);
    virtual ~hRayBasic();
    void cast(sf::Vector2f vector, sf::RenderWindow *w);
    void DrawWithInterpolation(sf::RenderWindow& window, float interpolation, PhysicsState *physicsState);
    
    sf::Clock tiempoCast;
    sf::Clock tiempoCd;
    float angleshot2=0.0f;
    //void cast(sf::Vector2f vector, sf::RenderWindow *w);
private:

};

#endif /* HRAYBASIC_HPP */

