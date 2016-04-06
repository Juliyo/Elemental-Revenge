/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.cpp
 * Author: joselu
 * 
 * Created on 6 de abril de 2016, 9:37
 */

#include "Headers/Menu.hpp"

Menu::Menu() {
    
    if(!font.loadFromFile("arial.ttf")){
        
    }
    
    float width=1280;
    float height=720;
    
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1) *1));
    
    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1) *2));
    
    
    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1) *3));
    
    
    
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

void Menu::draw(sf::RenderWindow &window){
    
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){
        
        window.draw(menu[i]);
       
    }
    
}