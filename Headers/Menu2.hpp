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


#include "State.hpp"
#include "Window.hpp"
#include "btree.hpp"
#include "AnimatedSprite.hpp"

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3   

class Menu2: public State  {
public:
    Menu2();
    Menu2(const Menu2& orig);
    virtual ~Menu2();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed, sf::RenderWindow &window); // Maneja eventos

    int getSetectedItemIndex(){
        return selectedItemIndex;
    };
    
private:
    
        sf::RenderWindow *mWindow;

    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[4];
};

#endif /* MENU_HPP */



