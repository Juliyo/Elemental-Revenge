/* 
 * File:   Hud.cpp
 * Author: tonir
 * 
 * Created on 11 de marzo de 2016, 13:12
 */


#include "StringHelpers.hpp"
#include "Hud.hpp"
Hud::Hud() {
    tBarraVida.loadFromFile("resources/Textures/hudHealthBar.png");
    tUnidadVida.loadFromFile("resources/Textures/unidadVida.png");
    fVida.loadFromFile("resources/Fonts/Minecraft.ttf");
    tUnidadVida.setSmooth(1);
    tUnidadVida.setRepeated(1);
    tBarraVida.setSmooth(1);
    
    barraVida.setTexture(tBarraVida);
    barraVida.setScale(0.5,1);
    barraVida.setPosition(10,10);
    
    shapeVida.height = tUnidadVida.getSize().y;
    shapeVida.width = tUnidadVida.getSize().x * 15; //15 vidas
    
    sVida.setTextureRect(shapeVida);
    sVida.setTexture(tUnidadVida);
    sVida.setScale(0.5,1);
    sVida.setPosition(15,24);
    
    tVida.setFont(fVida);
    tVida.setString("15/15");
    tVida.setOrigin(tVida.getGlobalBounds().width/2,tVida.getGlobalBounds().height/2);
    tVida.setPosition(110,32);
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

void Hud::renderHud(sf::RenderWindow *window){
    window->draw(sVida);
    window->draw(tVida);
    window->draw(barraVida);
}

void Hud::updateHud(int vidas){
    shapeVida.height = tUnidadVida.getSize().y;
    shapeVida.width = tUnidadVida.getSize().x * vidas; //15 vidas
    
    sVida.setTextureRect(shapeVida);
    sVida.setTexture(tUnidadVida);
    std::string str;
    str = toString(vidas) + "/15";
    tVida.setString(str);
}