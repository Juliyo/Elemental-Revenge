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



void Render::SetTexture(sf::Texture &tex)
{
	sprite = sf::Sprite(tex);
        
}

void Render::SetTextureRect(sf::IntRect rect){
    sprite.setTextureRect(rect);
}

void Render::PlayAnimation(Animation animation, sf::Time elapsedTime){
        animatedSprite.play(animation);
        animatedSprite.update(elapsedTime);
}
void Render::StopAnimation(){
    //if(&animatedSprite!=NULL){
        animatedSprite.stop();
    //}
        
}
void Render::Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation)
{
	renderPos = sf::Vector2f(
		posPrev.x + ((posNew.x - posPrev.x) * interpolation),
		posPrev.y + ((posNew.y - posPrev.y) * interpolation));

	sprite.setPosition(renderPos.x, renderPos.y);
	window.draw(sprite);
}

void Render::DrawAnimation(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation)
{
	renderPos = sf::Vector2f(
		posPrev.x + ((posNew.x - posPrev.x) * interpolation),
		posPrev.y + ((posNew.y - posPrev.y) * interpolation));
	animatedSprite.setPosition(renderPos.x, renderPos.y);
	window.draw(animatedSprite);
}

void Render::Draw(sf::RenderWindow& window, const sf::Vector2f& posPrev, const sf::Vector2f& posNew, float* anglePrev, float* angleNew, float interpolation) {
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));
    float shortest_angle=((((int)(*angleNew - *anglePrev) % 360) + 540) % 360) - 180;
     renderAngle = *anglePrev + (shortest_angle) * interpolation;
    
    
    std::cout<<"renderAngle: "<<renderAngle<<std::endl;
    std::cout<<"angleNew: "<<*angleNew<<std::endl;
    std::cout<<"anglePrev: "<<*anglePrev<<std::endl;
    sprite.setPosition(renderPos.x, renderPos.y);
    sprite.setRotation(renderAngle);
    window.draw(sprite);
}
void Render::DrawAnimation(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation,float *anglePrev, float *angleNew)
{
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));
    float shortest_angle=((((int)(*angleNew - *anglePrev) % 360) + 540) % 360) - 180;
     renderAngle = *anglePrev + (shortest_angle) * interpolation;
     
         std::cout<<"renderAngle: "<<renderAngle<<std::endl;
    std::cout<<"angleNew: "<<*angleNew<<std::endl;
    std::cout<<"anglePrev: "<<*anglePrev<<std::endl;
    animatedSprite.setPosition(renderPos.x+20, renderPos.y+25);
    animatedSprite.setRotation(renderAngle);
    window.draw(animatedSprite);
}