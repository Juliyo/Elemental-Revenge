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
#include "../States/State.hpp"
#include "SFML/System.hpp"
#include "AnimatedSprite.hpp"
#include "../Motor/Motor2D.hpp"
#include "../Motor/Text.hpp"

class Muerte: public State {
public:
    Muerte();
    void Inicializar();
    Muerte(const Muerte& orig);
    virtual ~Muerte();
    //void Update(sf::Time elapsedTime);
    void render(float interpolation, sf::Time elapsedTime);
    void updateView();
    
        void Render(float interpolation, sf::Time elapsedTime);
    void Update(sf::Time timeElapsed);
    
    void SetEscala();
    
        
    void HandleEvents(sf::Event& event);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed); // Maneja eventos
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Maneja eventos
    
    Motor2D *motor;
    
    bool restartReloj=true;
    
    sf::View mWorldView;
    sf::View mBackgroundView;
    sf::View mHud;
            sf::Clock relojMuerte;

private:
    AnimatedSprite *animatedSprite;
    Animation *animation;
    
    //Sprites
    Sprite                  *spriteRelleno;
    Sprite                  *spritePersonaje;
    Sprite                  *spriteFondo;
    Sprite                  *spriteFondoOpciones;
    Sprite                  *mouseSprite;
    
    int escala=1;
    
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

