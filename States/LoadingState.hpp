/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Carga1.hpp
 * Author: Julio
 *
 * Created on 18 de abril de 2016, 12:32
 */

#ifndef CARGA1_HPP
#define CARGA1_HPP

#include "../States/State.hpp"
#include "../Motor/Motor2D.hpp"
#include "../Motor/Video.hpp"
class LoadingState : public State{
public:
    LoadingState();
    LoadingState(const LoadingState& orig);
    virtual ~LoadingState();
    
    void Inicializar();
    
    void HandleEvents(sf::Event& event);

    void Update(sf::Time elapsedTime);
    void Render(float interpolation, sf::Time elapsedTime);
    
    void transitionCargado();
    void ingameCargado();
    
    
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

#endif /* CARGA1_HPP */

