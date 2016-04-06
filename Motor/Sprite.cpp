/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sprite.cpp
 * Author: Usuario
 * 
 * Created on 5 de abril de 2016, 14:40
 */

#include "Sprite.hpp"

Sprite::Sprite(std::string ruta) {
    setTexture(ruta);
}
Sprite::Sprite() {
}


Sprite::Sprite(const Sprite& orig) {
}

Sprite::Sprite(std::string ruta, bool smooth) {
    setTexture(ruta);
    m_texture.setSmooth(smooth);
}

Sprite::~Sprite() {
}

void Sprite::setTexture(std::string ruta) {
    if (m_texture.loadFromFile(ruta)) {
        m_sprite.setTexture(m_texture);
    }
}

void Sprite::setScale(float x, float y) {
    m_sprite.setScale(x, y);
}

void Sprite::setRotation(float angulo) {
    m_sprite.rotate(angulo);
}

void Sprite::setTextRect(int fil, int col, int ancho, int alto) {
    m_sprite.setTextureRect(sf::IntRect(fil, col, ancho, alto));
}

void Sprite::setOrigin(float x, float y) {
    m_sprite.setOrigin(x, y);
}

sf::FloatRect Sprite::getGlobalBounds() {
    return m_sprite.getGlobalBounds();
}

void Sprite::setSmooth(bool a) {
    m_texture.setSmooth(a);
}

void Sprite::setRepeated(bool a) {
    m_texture.setRepeated(a);
}

void Sprite::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}
