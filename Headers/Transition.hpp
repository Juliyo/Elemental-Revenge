/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transition.hpp
 * Author: joselu
 *
 * Created on 26 de marzo de 2016, 19:50
 */

#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include "State.hpp"
#include "btree.hpp"
#include "tinystr.h"
#include "tinyxml.h"
#include "../Motor/Video.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Transition : public State {
public:
    Transition();
    Transition(const Transition& orig);
    virtual ~Transition();

    void Update(sf::Time elapsedTime);

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Maneja eventos
    void handleMouseInput(sf::Mouse::Button button, bool isPressed); // Maneja eventos

    void render(float interpolation, sf::Time elapsedTime);

    void updateView();

    bool preguntaContestada = false;
    int level = 0;

    node *currentNode;
    node *firstNode;
    sf::Music *musica;

private:

    
    
    //Recursos
    sf::Texture texturaFondo;
    sf::Texture texPregunta;
    sf::Texture texturaOpcionA;
    sf::Texture texturaOpcionB;
    sf::Texture texturaNextLevel;
    sf::Texture texturaRelleno;
    sf::Texture mouseTexture;
    sf::Texture cruzeta;
    sf::Texture simboloText;

    sf::Font contFonts;

    Sprite *spriteOpcionA;
    Sprite *pregunta;
    Sprite *spriteOpcionB;
    Sprite *nextLevel;
    Sprite *spriteRelleno;
    Sprite *spriteFondo;
    Sprite *mouseSprite;
    Sprite *cruzeta1;
    Sprite *cruzeta2;
    Sprite *simbolo;

    Motor2D *motor;

    Video *video;

    btree *arbol;
    bool buttonPressed = false;
    bool firstTime = false;
    sf::Color transparent = sf::Color::Transparent;
    bool fadeEffect = false;
    bool unfadeEffect = false;
    bool izq = false;
    bool der = false;
    bool drawOpciones = true;
    bool drawNextLevel;
    char mejora;

    bool isPointOverSprite(const sf::Vector2f Position, Sprite &Sprite);
    void changePregunta();
    bool pulsado = false;
    bool Bcruzeta = false;

};


#endif /* TRANSITION_HPP */

