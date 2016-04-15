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
#include "Window.hpp"
#include "AnimatedSprite.hpp"

class Muerte: public State {
public:
    Muerte();
    Muerte(const Muerte& orig);
    virtual ~Muerte();
    void Update(sf::Time elapsedTime);
    void render(float interpolation, sf::Time elapsedTime);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed); // Maneja eventos
    sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight);
    void updateView();
    
    Window &ref = *Window::Instance();
    sf::View mWorldView;
    sf::View mBackgroundView;
    sf::View mHud;
    
private:
    sf::RenderWindow *mWindow;
    AnimatedSprite *animatedSprite;
    Animation *animation;
    sf::Texture                 texturaRelleno;
    sf::Sprite                  spriteRelleno;
    sf::Texture                 texturaPersonaje;
    sf::Sprite                  spritePersonaje;
    sf::Texture                 texturaFondo;
    sf::Sprite                  spriteFondo;
    sf::Sprite                  spriteFondoOpciones;
    sf::Texture                 mouseTexture;
    sf::Sprite                  mouseSprite;
    sf::Color transparent = sf::Color::Transparent;
    bool buttonPressed;
    
    
    sf::Font fontMuerte;
    sf::Text textoMuerte;
};

#endif /* MUERTE_HPP */

