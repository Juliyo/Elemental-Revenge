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
#include "../States/State.hpp"
#include "SFML/System.hpp"
#include "AnimatedSprite.hpp"
#include "../Motor/Motor2D.hpp"

#define MAX_NUMBER_OF_ITEMS 3   

class Pause : public State {
public:
    Pause();
    //static Pause* Instance();
    Pause(const Pause& orig);
    virtual ~Pause();

    void render(float interpolation, sf::Time elapsedTime);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed); // Maneja eventos
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Maneja eventos

    int getSetectedItemIndexPause() {
        return selectedItemIndexPausa;
    };

    int SetSetectedItemIndexPause(int a) {
        selectedItemIndexPausa = a;
    };
    
    Motor2D *motor;
    
private:
    AnimatedSprite *animatedSprite;
    Animation *animation;
    
    //Sprites
    Sprite *spriteRelleno;
    Sprite *spritePersonaje;
    Sprite *spriteFondo;
    Sprite *spriteFondoOpciones;
    Sprite *spriteMancha;
    Sprite *spriteMancha2;
    Sprite *mouseSprite;
    
    //Texturas
    sf::Texture texturaRelleno;
    sf::Texture texturaPersonaje;
    sf::Texture texturaFondo;
    sf::Texture texturaMancha;
    sf::Texture mouseTexture;
    
    sf::Color transparent = sf::Color::Transparent;
    bool buttonPressed;

    int selectedItemIndexPausa;
    sf::Font fontPausa;
    Text *menuPausa;
    Text *textoPausa;
    sf::Color colorAzul;
    
    //static Pause *mInstance;
};

#endif /* PAUSE_HPP */

