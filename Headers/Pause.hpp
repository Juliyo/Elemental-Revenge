/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pause.hpp
 * Author: kike
 *
 * Created on 6 de abril de 2016, 9:38
 */

#ifndef PAUSE_HPP
#define PAUSE_HPP
#include "State.hpp"
#include "SFML/System.hpp"
#include "Window.hpp"
#include "AnimatedSprite.hpp"

#define MAX_NUMBER_OF_ITEMS 3   

class Pause: public State {
public:
    Pause();
    Pause(const Pause& orig);
    virtual ~Pause();
    
    void Update(sf::Time elapsedTime);
    void render(float interpolation, sf::Time elapsedTime);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed); // Maneja eventos
    sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight);
    void updateView();
    void MoveUp();
    void MoveDown();
        void MoveLeft();
    void MoveRight();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed ); // Maneja eventos
        void handlePlayerInput2(sf::Keyboard::Key key, bool isPressed ); // Maneja eventos
    int getSetectedItemIndexPause(){
        return selectedItemIndexPausa;
    };
      int SetSetectedItemIndexPause(int a){
        selectedItemIndexPausa =a;
    };
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
    sf::Texture                 texturaMancha;
    sf::Sprite                  spriteMancha;
    sf::Sprite                  spriteMancha2;
    sf::Texture                 mouseTexture;
    sf::Sprite                  mouseSprite;
    sf::Color transparent = sf::Color::Transparent;
    bool buttonPressed;
    
    
    int selectedItemIndexPausa;
    sf::Font fontPausa;
    sf::Text menuPausa[10];
    sf::Text textoPausa;
    sf::Color colorAzul;
};

#endif /* PAUSE_HPP */

