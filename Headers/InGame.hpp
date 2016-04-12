/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InGame.hpp
 * Author: joselu
 *
 * Created on 26 de marzo de 2016, 19:49
 */

#ifndef INGAME_HPP
#define INGAME_HPP

#include "State.hpp"
#include "../Motor/Motor2D.hpp"


class InGame:public State {
public:
    InGame();
    InGame(const InGame& orig);
    virtual ~InGame();
    void    run();

    void Update(sf::Time elapsedTime);
    
    void			handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    void			handleMouseInput(sf::Mouse::Button button, bool isPressed);  // Maneja eventos
    
    void			render(float interpolation, sf::Time elapsedTime);
    
    void                        updateView();
       

    

private:
    
    
    Player			*player;
    Enemigo			enemigo[20];
    
    
    Motor2D                     *motor;
    //Graficos

    
    //Recursos
    sf::Texture                 texturaFondo;
    //sf::Sprite                  spriteFondo;
    Sprite                      spriteFondo;
    sf::Texture                 texturaRelleno;
    //sf::Sprite                  spriteRelleno;
    Sprite                      spriteRelleno;
    sf::Font                    contFonts;
    sf::Texture                 mouseTexture;
   // sf::Sprite                  mouseSprite;
    Sprite                  mouseSprite;
    
    
    
    //Eventos
    bool			isMovingUp;
    bool			isMovingDown;
    bool			isMovingRight;
    bool			isMovingLeft;
    bool                        rayoAdvancedCast = false;
    bool                        rayoBasicCast = false;
    
    bool                        noKeyWasPressed = true;
    bool			firstTimeRayo=true;
    bool			firstTimeFuego=true;
    bool			firstTimeAgua=true;
    bool                        firstTimeHeal=true;
    bool			isInterpolating;
    bool                        isShooting;
    bool                        aux;
    int                         hActivo=0;

    //fuego
    bool                        fuegoBasicCast=false;
    bool                        fuegoAdvancedCast=false;
    //agua
    bool                        aguaAdvancedCast = false;
    bool                        aguaBasicCast = false;  
    //heal
    bool                        cantMove=false;
    bool                        isHealing = false;
    int                         anterior=0;
    
};

#endif /* INGAME_HPP */

