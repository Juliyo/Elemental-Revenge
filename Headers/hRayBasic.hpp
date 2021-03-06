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
#include <SFML/Audio.hpp>

class hRayBasic:public Hechizo, public Collisionable {
public:
    hRayBasic();
    virtual ~hRayBasic();
    void cast(sf::Vector2f vector);
    void DrawWithInterpolation( float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew );
    std::string getClassName() override;
    void CreateBody() override;

    void rotateObject(b2Body *body, float x1, float y1, float width1, float height1, float rotation,float PPM);
    
    void stopSound();
    void update();
    
    Reloj tiempoCast;
    Reloj tiempoCd;

    float angleshot2=0.0f;
    Animation *animation;
    Animation **currentAnimation;
    Animation *animationDurante;
    Animation *PrimeraAnimacion;
    //void cast(sf::Vector2f vector, sf::RenderWindow *w);
    bool primeraVez=true;
private:
    
};

#endif /* HRAYBASIC_HPP */