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
#include "../Motor/Video.hpp"
#include "SFML/System.hpp"
#include <../Motor/Mapa.hpp>
#include <SFML/Audio.hpp>
#include "Pause.hpp"
#include "Muerte.hpp"
#include "../Motor/Level.hpp"
#include <vector>
#include <tmx/MapObject.h>

class InGame:public State {
public:
    InGame();
    InGame(const InGame& orig);
    virtual ~InGame();
    void    run();
    
    
   // void Init();
   // void Clean();
    void Inicializar();

    void LoadResources();

    void                        Update(sf::Time elapsedTime);
    void			Render(float interpolation, sf::Time elapsedTime);
    
    void                        HandleEvents(sf::Event& event);
    void			handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    void			handleMouseInput(sf::Mouse::Button button, bool isPressed);  // Maneja eventos
    
    
    void			renderForPause(float interpolation, sf::Time elapsedTime);
    void			renderForMuerte(float interpolation, sf::Time elapsedTime);
    
    void                        SetPlayer(float x, float y);
    
    void                        updateView();
    void                        updateViewForPause();
    Level                       *level;
    sf::Music                   *musica;
    sf::Music                   *musica2;
    
    Video *video;
private:
    
    std::pair<States::ID , bool> requestStateChange;
    
    
    Player			*player;
    Enemigo			enemigo[20];
    
    //Singletones
    Pause                       *pause;
    Muerte                      *muerte;
    
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
    Sprite                      mouseSprite;
    
    
   
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
    
    std::vector<tmx::MapObject*> objetosCercanos;
};

#endif /* INGAME_HPP */

