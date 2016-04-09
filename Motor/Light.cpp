/* 
 * File:   Light.cpp
 * Author: tonir
 * 
 * Created on 9 de abril de 2016, 11:43
 */

#include "Light.hpp"
Light::Light(){
}

Light::Light(const Light& orig) {
}

Light::~Light() {
}

Light::Light(sf::Vector2f nposition, sf::Vector2f nscale, int r, int g, int b,std::string ruta) {
    setPosition(nposition);
    setScale(nscale);
    setColor(r,g,b);
    setTexture(ruta);
}

void Light::setColor(int r, int g, int b) {
    color.r = r;
    color.g = g;
    color.b = b;
}

void Light::setPosition(sf::Vector2f pos) {
    position.x = pos.x;
    position.y = pos.y;
}

void Light::setScale(sf::Vector2f scl) {
    scale.x = scl.x;
    scale.y = scl.y;
}

void Light::setTexture(std::string ruta) {
    light.setTexture(ruta);
    light.setSmooth(true);
    
    setTextureRect(0,0,lightTexture.getSize().x,lightTexture.getSize().y);
    setOrigin(lightTexture.getSize().x/2,lightTexture.getSize().y/2);
}

void Light::setTextureRect(int top, int left, int width, int heigth) {
    light.setTextRect(top, left, width, heigth);
}

void Light::setOrigin(float x, float y) {
    light.setOrigin(x, y);
}

