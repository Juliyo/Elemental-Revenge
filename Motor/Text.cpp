/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Text.cpp
 * Author: tonir
 * 
 * Created on 8 de abril de 2016, 17:36
 */

#include "Text.hpp"
#include <string>

Text::Text() {
}

Text::Text(const Text& orig) {
}

Text::~Text() {
}

std::string Text::getText() {
    m_text.getString();
}

void Text::setFont(std::string ruta) {
    m_font.loadFromFile(ruta);
    m_text.setFont(m_font);
}

void Text::setFont(sf::Font fuente) {
    m_font = fuente;
    m_text.setFont(m_font);
}
void Text::setColor(int r, int g, int b, int a) {
    sf::Color color(r, g, b, a);
    m_text.setColor(color);
}

void Text::setString(std::string texto) {

    m_text.setString(texto);
}

void Text::setStyle(int a) {
    switch (a) {
        case 0:
            m_text.setStyle(sf::Text::Regular);
            break;
        case 1:
            m_text.setStyle(sf::Text::Bold);
            break;
        case 2:
            m_text.setStyle(sf::Text::Italic);
            break;
        case 3:
            m_text.setStyle(sf::Text::Underlined);
            break;
    }

}

void Text::setColor(sf::Color color) {
    m_text.setColor(color);
}

void Text::setScale(float x, float y) {
    m_text.setScale(x, y);
}

void Text::setPosition(int x, int y) {
    m_text.setPosition(x, y);
}

sf::FloatRect Text::getGlobalBounds() {
    return m_text.getGlobalBounds();
}

sf::Vector2f Text::getPosition() {
    return m_text.getPosition();
}

void Text::setOrigin(float x, float y) {
    m_text.setOrigin(x, y);
}
