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

#include "Headers/Menu2.hpp"

Menu2::Menu2() {
    
    EstadoActivo=true;
    
    if(!font.loadFromFile("resources/Fonts/Minecraft.ttf")){
        
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
    
    
    menu[3].setFont(font);
    menu[3].setColor(sf::Color::Red);
    menu[3].setString("OPTIONS");
    menu[3].setPosition(sf::Vector2f(width/2, height/(MAX_NUMBER_OF_ITEMS+1) *1));
    
    selectedItemIndex=0;
    
}

Menu2::Menu2(const Menu2& orig) {
}

Menu2::~Menu2() {
}

void Menu2::draw(sf::RenderWindow &window){
    

    if(selectedItemIndex<3){
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){

        window.draw(menu[i]);
       
    }
    }
    else{
        window.draw(menu[3]);
    }
    
}

void Menu2::MoveUp(){
    
    
        if(selectedItemIndex<3){

    if(selectedItemIndex-1>=0){
        
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
        
    }
        }
}

void Menu2::MoveDown(){
    
    
        if(selectedItemIndex<3){

    if(selectedItemIndex+1<MAX_NUMBER_OF_ITEMS){
        
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
        
    }
        }
    
}


void Menu2::handlePlayerInput(sf::Keyboard::Key key, bool isPressed, sf::RenderWindow &window) {
    
    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        MoveUp();
    } else if (key == sf::Keyboard::S) {
        MoveDown();
    } else if (key == sf::Keyboard::Return) {
        if(selectedItemIndex==1){
        selectedItemIndex=3;
        }
        if(selectedItemIndex==2){
            window.close();
        }

    } else if (key == sf::Keyboard::Escape) {
        if(selectedItemIndex<3){
        window.close();}
        else{
            selectedItemIndex=1;
        }
    } 
}
