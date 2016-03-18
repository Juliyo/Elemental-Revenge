
////
/* 
 * File:   Render.cpp
 * Author: zimuuuuuuuuuuuuuuuuuuu
 * 
 * Created on March 5, 2014, 8:08 AM
 */

#include "../Headers/Render.hpp"


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

void Render::PlayAnimation(Animation *animation) {
    animatedSprite.play(*animation);
}
void Render::StopAnimation(){

        animatedSprite.stop();
        
}
//Renderizar sprites sin animar con interpolación
void Render::Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation)
{
	renderPos = sf::Vector2f(
		posPrev.x + ((posNew.x - posPrev.x) * interpolation),
		posPrev.y + ((posNew.y - posPrev.y) * interpolation));

	sprite.setPosition(renderPos.x, renderPos.y);
	window.draw(sprite);
}
//Renderizar sprites animados con interpolación
void Render::DrawAnimation(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation)
{
	renderPos = sf::Vector2f(
		posPrev.x + ((posNew.x - posPrev.x) * interpolation),
		posPrev.y + ((posNew.y - posPrev.y) * interpolation));
	animatedSprite.setPosition(renderPos.x, renderPos.y);
	window.draw(animatedSprite);
}
//Renderizar sprites animados sin interpolación
void Render::DrawAnimationWithOut(sf::RenderWindow &window, const sf::Vector2f &pos)
{
	renderPos = sf::Vector2f(pos);

	animatedSprite.setPosition(renderPos.x, renderPos.y);
	window.draw(animatedSprite);
}
//Renderizar sprites sin animar con interpolación en rotación
void Render::Draw(sf::RenderWindow& window, const sf::Vector2f& posPrev, const sf::Vector2f& posNew, float* anglePrev, float* angleNew, float interpolation) {
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));
    float shortest_angle=((((int)(*angleNew - *anglePrev) % 360) + 540) % 360) - 180;   //Calculamos el angulo más corto en el caso de que
                                                                                        //pasemos de 0 a 360ª
     renderAngle = *anglePrev + (shortest_angle) * interpolation;
    
    sprite.setPosition(renderPos.x, renderPos.y);
    sprite.setRotation(renderAngle);
    window.draw(sprite);
}
//Renderizar sprites animados con interpolación en rotación
void Render::DrawAnimation(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation,float *anglePrev, float *angleNew)
{
    renderPos = sf::Vector2f(
            posPrev.x + ((posNew.x - posPrev.x) * interpolation),
            posPrev.y + ((posNew.y - posPrev.y) * interpolation));
    
    float shortest_angle=((((int)(*angleNew - *anglePrev) % 360) + 540) % 360) - 180;   //Calculamos el angulo más corto en el caso de que
                                                                                        //pasemos de 0 a 360ª
     renderAngle = *anglePrev + (shortest_angle) * interpolation;
    
    animatedSprite.setPosition(renderPos.x, renderPos.y);
    animatedSprite.setRotation(renderAngle);
    window.draw(animatedSprite);
}
void Render::UpdateAnimation(sf::Time elapsedTime) {
    animatedSprite.update(elapsedTime);
}


void Render::SetFrame(sf::Time time) {
    animatedSprite.setFrameTime(time);

}