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
#include "Window.hpp"
#include "btree.hpp"
#include "AnimatedSprite.hpp"

class Transition : public State {
public:
    Transition();
    Transition(const Transition& orig);
    virtual ~Transition();

    void Update(sf::Time elapsedTime);

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Maneja eventos
    void handleMouseInput(sf::Mouse::Button button, bool isPressed); // Maneja eventos

    void render(float interpolation, sf::Time elapsedTime);

    sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight);

    void updateView();
    Window &ref = *Window::Instance();


    sf::View mWorldView;
    sf::View mBackgroundView;
    sf::View mHud;
    
    bool preguntaContestada=false;
    int level = 0;
    
    node *currentNode;
    node *firstNode;

    
private:
    sf::RenderWindow *mWindow;

    //Recursos
    sf::Texture                 texturaFondo;
    
    sf::Sprite                  pregunta;
    sf::Texture                 texPregunta;
    
    sf::Sprite                  spriteOpcionA;
    sf::Sprite                  spriteOpcionB;
    sf::Sprite                  nextLevel;
    sf::Texture                 texturaOpcionA;
    sf::Texture                 texturaOpcionB;
    sf::Texture                 texturaNextLevel;
    
    sf::Sprite                  spriteRelleno;
    sf::Texture                 texturaRelleno;
    sf::Sprite                  spriteFondo;
    sf::Font                    contFonts;
    sf::Texture                 mouseTexture;
    sf::Sprite                  mouseSprite;
    sf::Texture                 cruzeta;
    sf::Sprite                  cruzeta1;
    sf::Sprite                  cruzeta2;
    
    sf::Texture                 simboloText;
    sf::Sprite                  simbolo;
    
    
    
    AnimatedSprite *animatedSprite;
    Animation *animation;
    sf::Texture pend;
    btree *arbol;
    bool buttonPressed = false;
    bool firstTime = false;
    sf::Color transparent = sf::Color::Transparent;
    bool fadeEffect = false;
    bool unfadeEffect = false;
    bool izq = false;
    bool der = false;
    bool drawOpciones=true;
    bool drawNextLevel;
    char mejora;
    
    bool isPointOverSprite(const sf::Vector2f Position, const sf::Sprite &Sprite);
    void changePregunta();
    bool                        pulsado = false;
    bool                        Bcruzeta = false;


};


#endif /* TRANSITION_HPP */

