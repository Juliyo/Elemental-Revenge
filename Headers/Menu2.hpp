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


#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3   

class Menu2 {
public:
    Menu2();
    Menu2(const Menu2& orig);
    virtual ~Menu2();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Maneja eventos

    
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

#endif /* MENU_HPP */



