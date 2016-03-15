/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Heal.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 23:15
 */
#include "../Headers/Heal.hpp"
#include "AnimatedSprite.hpp"
#include <iostream>

Heal::Heal() {
    animacion = new Animation();

    if (!hTexture.loadFromFile("resources/Textures/heal.png")) {
        std::cout << "No se ha podido cargar heal.png" << std::endl;
        exit(0);
    }

    animacion->setSpriteSheet(hTexture);
    animacion->addFrame(sf::IntRect(0,0,256,256));
    animacion->addFrame(sf::IntRect(256,0,256,256));
    animacion->addFrame(sf::IntRect(512,0,256,256));
    animacion->addFrame(sf::IntRect(768,0,256,256));
    animacion->addFrame(sf::IntRect(1024,0,256,256));
    
    animacion->addFrame(sf::IntRect(0,256,256,256));
    animacion->addFrame(sf::IntRect(256,256,256,256));
    animacion->addFrame(sf::IntRect(512,256,256,256));
    animacion->addFrame(sf::IntRect(768,256,256,256));
    animacion->addFrame(sf::IntRect(1024,256,256,256));
    
    animacion->addFrame(sf::IntRect(0,512,256,256));
    animacion->addFrame(sf::IntRect(256,512,256,256));
    animacion->addFrame(sf::IntRect(512,512,256,256));
    animacion->addFrame(sf::IntRect(768,512,256,256));
    animacion->addFrame(sf::IntRect(1024,512,256,256));
    
    animacion->addFrame(sf::IntRect(0,768,256,256));
    animacion->addFrame(sf::IntRect(256,768,256,256));
    animacion->addFrame(sf::IntRect(512,768,256,256));
    animacion->addFrame(sf::IntRect(768,768,256,256));
    animacion->addFrame(sf::IntRect(1024,768,256,256));
   
    InicializarAnimatedSprite(sf::seconds(0.025f),true,false);
    SetOriginAnimatedSprite(70,100);
    SetScale(0.5f,0.5f);
    
    setCD(5.f);
}

Heal::Heal(const Heal& orig) {
}

Heal::~Heal() {
}

bool Heal::cast() {
    if (primerCast == true || clockCd.getElapsedTime().asSeconds() > getCD()) {
        primerCast = false;
        clockCd.restart();
        tiempoCast.restart();
        dibujar = true;
        return true;
    }
    return false;
}

void Heal::DrawWithInterpolation(sf::RenderWindow& window, float interpolation, sf::Vector2f pos1,sf::Vector2f pos2) {
    DrawAnimation(window, pos1, pos2, interpolation);
}