/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu2.hpp
 * Author: joselu
 *
 * Created on 6 de abril de 2016, 10:17
 */

#ifndef MENU2_HPP
#define MENU2_HPP

#include <random>   // rng

#include "State.hpp"
#include "Window.hpp"
#include "btree.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Audio.hpp>


#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3   

class Menu2: public State, public Render, public PhysicsState {
public:
    Menu2();
    Menu2(const Menu2& orig);
    virtual ~Menu2();
    
    void render();
    
    void MoveUp();
    void MoveDown();
    sf::Vector2f getPosition();

    void    Update(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Maneja eventos
    sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight);

    void handleMouseInput(sf::Mouse::Button button, bool isPressed);
        void updateView();
    int getSetectedItemIndex(){
        return selectedItemIndex;
    }
    
    int SetSetectedItemIndex(int a){
        selectedItemIndex=a;
    }
    
    void pararMusica();

        Window &ref = *Window::Instance();

    sf::View mWorldView;
    sf::View mBackgroundView;
    sf::View mHud;
    
private:
    bool tecladoActivo;
    bool ratonSelecciona;
    
            sf::Music                   *musica;

    sf::Texture                 texturaAnimation;

    Animation                   *animationMenu;
    
    
    sf::Texture                 texturaAnimationFuego;

    Animation                   *animationMenuFuego;
        
    sf::Texture                 texturaAnimationRayo;

    Animation                   *animationMenuRayo;
    
    sf::RenderWindow            *mWindow;
    sf::Texture                 texturaFondoMenu;
    sf::Sprite                  spriteFondoMenu;
    
    sf::Texture                 texturaFondo;
    sf::Sprite                  spriteFondo;
    
    sf::Texture                 texturaRelleno;
    sf::Sprite                  spriteRelleno;
    
    sf::RectangleShape          rectanguloFondo;
    
    sf::Texture                 mouseTexture;
    sf::Sprite                  mouseSprite;
    
    sf::Texture                 texturaTitulo;
    sf::Sprite                  Titulo;
    
        
    sf::Texture                 texturaMancha;
    sf::Sprite                  Mancha[3];
    
    int selectedItemIndex;
    int Random;
    sf::Font font;
    sf::Font fontTitulo;
    sf::Text textTitulo;

    sf::Text menu[4];
};

#endif /* MENU_HPP */



