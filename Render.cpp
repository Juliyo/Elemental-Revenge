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

void Render::PlayAnimation(Animation *animation) {
    animatedSprite.play(*animation);
}

void Render::UpdateAnimation(sf::Time elapsedTime) {
    animatedSprite.update(elapsedTime);
}

void Render::StopAnimation() {
    //if(&animatedSprite!=NULL){
    animatedSprite.stop();
    //}

}
void Render::SetFrameTime(sf::Time time) {
    //if(&animatedSprite!=NULL){
    animatedSprite.setFrameTime(time);
    //}

}

void Render::Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation) {
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));

    sprite.setPosition(renderPos.x, renderPos.y);
    window.draw(sprite);
}

void Render::DrawAnimation(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation) {
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));
    animatedSprite.setPosition(renderPos.x, renderPos.y);
    window.draw(animatedSprite);
}
void Render::Draw90(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation)
{
	renderPos = sf::Vector2f(
		posPrev.x + ((posNew.x - posPrev.x) * interpolation),
		posPrev.y + ((posNew.y - posPrev.y) * interpolation));

	sprite.setPosition(renderPos.x, renderPos.y);
        sprite.rotate(25);
        
	window.draw(sprite);
}