/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hechizo.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 12:30
 */

#ifndef HECHIZO_HPP
#define HECHIZO_HPP

#include <SFML/Graphics.hpp>
#include "PhysicsState.hpp"
#include "Render.hpp"
#include "Animation.hpp"
#include "AnimatedSprite.hpp"

class Hechizo:public Render,public PhysicsState {
public:
    Hechizo();
    Hechizo(const Hechizo& orig);
    virtual ~Hechizo();
    sf::Sprite hSprite;
    sf::Texture hTexture;
    sf::Clock tiempoCast;
    sf::Clock clockCd;
    float angleshot2=0.0f;
    bool primerCast;
    
    
    float getDamage();
    void setDamage(float dmg);
    float getCD();
    void setCD(float cd);
    void setLevel(int lvl);
    int getLevel();
    bool dibujar;
    
    
private:
    float hCd;
    float hDamage;
    int hLVL;
    void cast();
};

#endif /* HECHIZO_HPP */
