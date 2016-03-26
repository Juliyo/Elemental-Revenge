/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.hpp
 * Author: joselu
 *
 * Created on 26 de marzo de 2016, 19:49
 */

#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemigo.hpp"


class State {
public:
    State();
    State(const State& orig);
    virtual ~State();
protected:
    sf::Texture                 texturaFondo;
    sf::Sprite                  spriteFondo;
    sf::Texture                 texturaRelleno;
    sf::Sprite                  spriteRelleno;
    sf::Font                    contFonts;
    sf::Texture                 mouseTexture;
    sf::Sprite                  mouseSprite;
    
    //Graficos
    sf::RenderWindow		mWindow;
    sf::View                    mWorldView;
    sf::View                    mBackgroundView;
    sf::View                    mHud;
    Player			*player;
    Enemigo			enemigo[20];
    
    //Estadisticas
    sf::Text			mStatisticsText;
    
    float                       interpolation;
	
    //Eventos
    bool			isMovingUp;
    bool			isMovingDown;
    bool			isMovingRight;
    bool			isMovingLeft;
    bool                        rayoAdvancedCast = false;
    bool                        rayoBasicCast = false;
    
    bool                        noKeyWasPressed = true;
    bool			firstTime;
    bool			isInterpolating;
    bool                        isShooting;
    bool                        aux;
};

#endif /* STATE_HPP */

