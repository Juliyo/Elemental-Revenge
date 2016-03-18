/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayAdvanced.hpp
 * Author: joselu
 *
 * Created on 11 de marzo de 2016, 23:04
 */

#ifndef HRAYADVANCED_HPP
#define HRAYADVANCED_HPP

#include "../Headers/Hechizo.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

class hRayAdvanced:public Hechizo {
public:
    hRayAdvanced();
    hRayAdvanced(const hRayAdvanced& orig);
    virtual ~hRayAdvanced();
    void cast(sf::Vector2f vector, sf::RenderWindow *w);
    sf::Clock tiempoCast;
    sf::Clock tiempoCd;
    
void DrawWithOutInterpolation(sf::RenderWindow &window);
    Animation **currentAnimation;
    Animation *animationDurante;
private:

};

#endif /* HRAYADVANCED_HPP */