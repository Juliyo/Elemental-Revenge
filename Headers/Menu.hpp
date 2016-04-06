/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.hpp
 * Author: joselu
 *
 * Created on 6 de abril de 2016, 9:37
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3   

class Menu {
public:
    Menu();
    Menu(const Menu& orig);
    virtual ~Menu();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

#endif /* MENU_HPP */

