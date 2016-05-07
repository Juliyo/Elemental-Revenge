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
#include "../Motor/Music.hpp"
#include "../Motor/Video.hpp"
#include "SFML/System.hpp"
#include <../Motor/Mapa.hpp>
#include <SFML/Audio.hpp>
#include "../Motor/Level.hpp"
#include <vector>
#include <tmx/MapObject.h>
#include "../Entities/Player.hpp"
#include "../Entities/Melee.hpp"
#include <Box2D/Box2D.h>
#include "../Otros/Dummy.hpp"
#include "../Otros/ContactListener.hpp"
#include "../Motor/PathFinding.hpp"

class InGame : public State {
public:
    InGame();
    static InGame* Instance();
    InGame(const InGame& orig);
    virtual ~InGame();
    
    void Inicializar();
    void LoadResources();

    void                        Update(sf::Time elapsedTime);
    void			Render(float interpolation, sf::Time elapsedTime);
    
    void                        HandleEvents(sf::Event& event);
    void			handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    void			handleMouseInput(sf::Mouse::Button button, bool isPressed);  // Maneja eventos
    
    void primerosDeLaCola();
    bool                        cambioInGame2Pausa=true;
   
    
    float                       cdFuegoAvanzadoPausa=0;
    float                       cdFuegoBasicoPausa=0;    
    float                       cdAguaAvanzadoPausa=0;
    float                       cdAguaBasicoPausa=0;
    float                       cdRayoBasicoPausa=0;
    float                       cdRayoAvanzadoPausa=0;
    
    float                       cdFlashPausa=0;
    
    bool auxRayo;
    
    Level                       *level;
    Music                       *music;
    b2World                     *physicWorld;
    Video                       *video;
    Player			*player;
    std::vector<Melee*>         *melee;
    std::vector<sf::CircleShape*> *meleeShapes;
    PathFinding                 *pathfingind;
    std::deque<Melee*>          *colaMelees;
private:
    
    std::vector<bool>           *VectorBools;
    
    //Recursos
    sf::Texture texturaFondo;
    sf::Texture texturaRelleno;
    Sprite spriteFondo;
    Sprite                      spriteRelleno;
    sf::Font                    contFonts;
    
    //Eventos
    
    bool                        rayoAdvancedCast = false;
    bool                        rayoBasicCast = false;
    
    bool                        noKeyWasPressed = true;
    bool			firstTime=true;
    bool			isInterpolating;
    bool                        isShooting;
    bool                        aux;
    
    int                         hActivo=0;
    //fuego
    bool                        fuegoBasicCast = false;
    bool                        fuegoAdvancedCast = false;
    //agua
    bool                        aguaAdvancedCast = false;
    bool                        aguaBasicCast = false;
    //heal
    bool                        isHealing = false;
    int                         anterior=0;
    
    static InGame* mInstance;
    ContactListener             *ct;
};

#endif /* INGAME_HPP */

