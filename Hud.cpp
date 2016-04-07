/* 
 * File:   Hud.cpp
 * Author: tonir
 * 
 * Created on 11 de marzo de 2016, 13:12
 */


#include "StringHelpers.hpp"
#include "Hud.hpp"
#include "Motor/Sprite.hpp"

Hud::Hud() {

    fVida.loadFromFile("resources/Fonts/Minecraft.ttf");

    std::string ruta = "resources/Textures/hudHealthBar.png";
    std::string ruta2 = "resources/Textures/unidadVida.png";
    barraVida.setTexture(ruta);
    barraVida.setScale(0.5, 1);
    barraVida.setPosition(10, 10);

    sVida.setTexture(ruta2);
    sVida.setRepeated(true);
    sVida.setScale(0.5, 1);
    sVida.setPosition(15, 24);
    
    shapeVida.height = sVida.getTextureSize().y;
    shapeVida.width = sVida.getTextureSize().x * 15; //15 vidas

    sVida.setTextRect(shapeVida.top, shapeVida.left, shapeVida.width, shapeVida.height);
    
    tVida.setFont(fVida);
    tVida.setString("15/15");
    tVida.setOrigin(tVida.getGlobalBounds().width / 2, tVida.getGlobalBounds().height / 2);
    tVida.setPosition(110, 32);
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

void Hud::renderHud() {
    Motor2D *m = Motor2D::Instance();
    m->draw(sVida);
    m->draw(tVida);
    m->draw(barraVida);
}

void Hud::updateHud(int vidas) {
    shapeVida.height = sVida.getTextureSize().y;
    shapeVida.width = sVida.getTextureSize().x * vidas; //15 vidas

    sVida.setTextRect(shapeVida.top, shapeVida.left, shapeVida.width, shapeVida.height);
    //El metodo getSfTexture() devuelve una sf::Texture que no estaria bien pero es para no tener que 
    //leer del disco todo el rato. Solo utilizamos este metodo aqui

    //sVida.setTexture(sVida.getSfTexture());
    std::string str;
    str = toString(vidas) + "/15";
    tVida.setString(str);
}

