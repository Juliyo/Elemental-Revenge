/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Muerte.hpp
 * Author: kike
 *
 * Created on 13 de abril de 2016, 18:20
 */

#ifndef MUERTE_HPP
#define MUERTE_HPP
#include "State.hpp"
#include "SFML/System.hpp"
#include "AnimatedSprite.hpp"

class Muerte: public State {
public:
    Muerte();
    Muerte(const Muerte& orig);
    virtual ~Muerte();
    //void Update(sf::Time elapsedTime);
    void render(float interpolation, sf::Time elapsedTime);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed); // Maneja eventos
    void updateView();
    
    Motor2D *motor;
    
    sf::View mWorldView;
    sf::View mBackgroundView;
    sf::View mHud;
    
private:
    AnimatedSprite *animatedSprite;
    Animation *animation;
    //Sprites
    Sprite                  *spriteRelleno;
    Sprite                  *spritePersonaje;
    Sprite                  *spriteFondo;
    Sprite                  *spriteFondoOpciones;
    Sprite                  *mouseSprite;
    
    sf::Texture                 texturaRelleno;
    sf::Texture                 texturaPersonaje;
    sf::Texture                 texturaFondo;
    sf::Texture                 mouseTexture;
    
    sf::Color transparent = sf::Color::Transparent;
    bool buttonPressed;
    
    sf::Font     fontMuerte;
    Text        *textoMuerte;
};

#endif /* MUERTE_HPP */

