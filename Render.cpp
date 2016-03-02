/* 
 * File:   Render.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 8:08 AM
 */

#include "Render.hpp"

Render::Render() : sprite(), renderPos() {
}

Render::Render(const Render& orig) {
}

Render::~Render() {
}

void Render::SetTexture(sf::Texture &tex) {
    sprite = sf::Sprite(tex);

}

void Render::SetTextureRect(sf::IntRect rect) {
    sprite.setTextureRect(rect);
}

void Render::SetOrigin(float x, float y) {
    sprite.setOrigin(x, y);
}

void Render::Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation) {
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));

    sprite.setPosition(renderPos.x, renderPos.y);
    window.draw(sprite);
}

void Render::Draw(sf::RenderWindow& window, const sf::Vector2f& posPrev, const sf::Vector2f& posNew, float* anglePrev, float* angleNew, float interpolation) {
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));

    renderAngle = anglePrev + (angleNew - anglePrev) * interpolation;
    
    sprite.setPosition(renderPos.x, renderPos.y);
    sprite.setRotation(renderAngle);
    window.draw(sprite);
}