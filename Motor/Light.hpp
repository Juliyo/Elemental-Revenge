/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Light.hpp
 * Author: tonir
 *
 * Created on 9 de abril de 2016, 11:43
 */

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <SFML/Graphics.hpp>
#include "Sprite.hpp"
class Light {
public:
    Light();
    Light(sf::Vector2f nposition, sf::Vector2f nscale,int r, int g, int b, std::string ruta);
    Light(const Light& orig);
    virtual ~Light();
    void setPosition(sf::Vector2f pos);
    void setScale(sf::Vector2f scl);
    void setColor(int r, int g, int b);
    void setTexture(std::string ruta);
    void setTextureRect(int top, int left, int width, int heigth);
    void setOrigin(float x, float y);
    
private:
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Color color;
    
    sf::Texture lightTexture;
    Sprite light;
};

#endif /* LIGHT_HPP */

