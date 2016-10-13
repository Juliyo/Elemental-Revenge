/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Carga2.hpp
 * Author: Julio
 *
 * Created on 18 de abril de 2016, 20:38
 */

#ifndef CARGA2_HPP
#define CARGA2_HPP

#include "../States/State.hpp"
#include "../Motor/Motor2D.hpp"
#include "../Motor/Video.hpp"

class Carga2 : public State{
public:
    Carga2();
    Carga2(const Carga2& orig);
    virtual ~Carga2();
    
    void Update(sf::Time elapsedTime);
    void render(float interpolation, sf::Time elapsedTime);
private:

    void updateView();
    
    Motor2D *motor;
    
    Sprite *mouseSprite;
    Sprite *spriteRelleno;
    Sprite *spriteFondo;
    
    sf::Texture texturaRelleno;
    sf::Texture mouseTexture;
    sf::Texture texturaFondo;
    
    Text *cargando;
    Text *mensaje;
    
    Reloj *reloj1;
    
    Video *video;
    
};

#endif /* CARGA2_HPP */

