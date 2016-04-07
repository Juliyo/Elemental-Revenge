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

sf::Texture Sprite::getSfTexture(){
    return m_texture;
}

void Sprite::setTexture(std::string ruta, bool smooth) {
    if (m_texture.loadFromFile(ruta)) {
        m_sprite.setTexture(m_texture);
    }
    if(smooth){
        m_texture.setSmooth(true);
    }
}

void Sprite::setTexture(sf::Texture textura) {
    m_texture = textura;
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

sf::Vector2u Sprite::getTextureSize() {
    return m_texture.getSize();
}

sf::Texture Sprite::getTexture() {
    return m_texture;
}

sf::Vector2f Sprite::getPosition() {
    return m_sprite.getPosition();
}
