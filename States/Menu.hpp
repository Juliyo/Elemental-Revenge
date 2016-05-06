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

#include "../States/State.hpp"
#include "btree.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "../Motor/Text.hpp"


#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3   

class Menu : public State, public Render, public PhysicsState {
public:
    Menu();
    Menu(const Menu& orig);
    virtual ~Menu();

    void Inicializar();

    void Render(float interpolation, sf::Time elapsedTime);
    void Update(sf::Time elapsedTime);
    
    void HandleEvents(sf::Event& event);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed);
    
    void MoveUp();
    void MoveDown();
    
    sf::Vector2f getPosition();

    
    
    void updateView();

    int getSetectedItemIndex() {
        return selectedItemIndex;
    }

    int SetSetectedItemIndex(int a) {
        selectedItemIndex = a;
    }

    void pararMusica();

    Motor2D *motor;

    sf::View mWorldView;
    sf::View mBackgroundView;
    sf::View mHud;

private:
    
    void cargarAnimacionesMenu();
    
    bool tecladoActivo;
    bool ratonSelecciona;

    

    //Animations
    Animation *animationMenu;
    Animation *animationMenuFuego;
    Animation *animationMenuRayo;
    
    //Sprites
    Sprite *spriteFondoMenu;
    Sprite *spriteFondo;
    Sprite *spriteRelleno;
    Sprite *mouseSprite;
    Sprite *titulo;
    Sprite *mancha;
    
    //Texturas
    sf::Texture texturaAnimationFuego;
    sf::Texture texturaAnimationRayo;
    sf::Texture texturaFondoMenu;
    sf::Texture texturaFondo;
    sf::Texture texturaRelleno;
    sf::Texture mouseTexture;
    sf::Texture texturaTitulo;
    sf::Texture texturaMancha;
    sf::Texture texturaAnimation;
    sf::Texture texturaPersonaje;
    
    sf::RectangleShape rectanguloFondo;

    int selectedItemIndex;
    int random;
    sf::Font font;
    sf::Font fontTitulo;
    Text *textTitulo;

    Text menu[4];
};

#endif /* MENU_HPP */



