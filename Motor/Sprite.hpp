/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sprite.hpp
 * Author: Usuario
 *
 * Created on 5 de abril de 2016, 14:40
 */

#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>

class Sprite: public sf::Drawable {
public:
    Sprite(std::string ruta);
    Sprite(std::string ruta,bool smooth);
    Sprite();
    virtual ~Sprite();
    void setTexture(std::string ruta);
    void setTexture(std::string ruta, bool smooth);
    void setTexture(sf::Texture& textura);
    void setScale(float x,float y);
    void setRotation(float angulo);
    void setTextRect(int fil, int col, int ancho, int alto);
    void setOrigin(float x, float y);
    void setColor(sf::Color transparent);
    sf::FloatRect getGlobalBounds();
    sf::FloatRect getLocalBounds();
    void setSmooth(bool a);
    void setRepeated(bool a);
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f pos);
    sf::Vector2u getTextureSize();
    sf::Texture* getTexture();
    sf::Vector2f getPosition();

    sf::Texture* getSfTexture();
    sf::IntRect getTextureRect();

    void rotate(float ang);

    
private:
    sf::Sprite m_sprite;
    sf::Texture *m_texture;
    sf::VertexArray m_vertices;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(m_sprite, states);
    }
};

#endif /* SPRITE_HPP */

