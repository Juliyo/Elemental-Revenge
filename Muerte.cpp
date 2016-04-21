/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Muerte.cpp
 * Author: kike
 * 
 * Created on 13 de abril de 2016, 18:20
 */
#include <iostream>
#include <string>
#include "Muerte.hpp"


Muerte::Muerte() {
    
    motor = Motor2D::Instance();
    
    spriteRelleno = new Sprite();
    spritePersonaje = new Sprite();
    spriteFondo = new Sprite();
    spriteFondoOpciones = new Sprite();
    mouseSprite = new Sprite();
    textoMuerte = new Text();
    
    //Estado de Ingame
//    EstadoActivo = false;

    try {
        texturaRelleno.loadFromFile("resources/Textures/texturaMuerte.png");
        texturaFondo.loadFromFile("resources/Textures/fondo.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
        texturaPersonaje.loadFromFile("resources/Textures/fondoPersonaje.png");
        fontMuerte.loadFromFile("resources/Fonts/OptimusPrinceps.ttf");
    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    textoMuerte->setFont(fontMuerte);
    textoMuerte->setColor(sf::Color::Red);
    textoMuerte->setString("HAS MUERTO");
    textoMuerte->setOrigin(textoMuerte->getGlobalBounds().width/2, textoMuerte->getGlobalBounds().height/2);
    textoMuerte->setPosition(15+(500), 500);
    textoMuerte->setScale(2,2);
    
    mouseSprite->setTexture(mouseTexture);
    mouseSprite->setScale(0.2, 0.2);
    mouseSprite->setPosition(20, 20);
    mouseSprite->setOrigin(64, 64);

    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    spriteFondo->setTexture(texturaFondo);
    spriteFondo->setTextRect(0, 0, 1280, 720);
    //spriteFondo->setOrigin(spriteFondo->getTextureRect().width / 2, spriteFondo->getTextureRect().height / 2);
    //spriteFondo->setPosition(350, 700 / 2);
    spriteFondo->setScale(1,2);
    transparent.a = 180;
    spriteFondo->setColor(transparent);
    
    spriteRelleno->setTexture(texturaRelleno);
    spriteRelleno->setScale(1.2,0.45);
    //spriteRelleno->setOrigin(spriteRelleno->getTextureRect().width / 2, spriteRelleno->getTextureRect().height / 2);
    spriteRelleno->setPosition(0, 440);
    spriteRelleno->setColor(transparent);
}


Muerte::Muerte(const Muerte& orig) {
}

Muerte::~Muerte() {
}

void Muerte::render(float interpolation, sf::Time elapsedTime) {
    
    if(relojMuerte.getElapsedTime().asSeconds()<0.5){
        escala++;
        float aux= 1.4+0.07*escala;
        textoMuerte->setScale(aux,aux);
    }
    
    updateView();
    motor->draw(spriteFondo);
    motor->draw(spriteRelleno);
    motor->draw(*textoMuerte);
    
}
void Muerte::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left) {
        if (isPressed) {
            buttonPressed = isPressed;
        }
    }
}

void Muerte::updateView() {
     sf::FloatRect viewBounds(motor->getCenterFromView(1) - motor->getSizeFromView(1) / 2.f, motor->getSizeFromView(1));

    sf::Vector2f position = motor->getMousePosition();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);

    mouseSprite->setPosition(position.x, position.y);

}

void Muerte::SetEscala() {
    escala = 1;
}
