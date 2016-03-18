/* 
 * File:   Render.h
 * Author: linuxero
 *
 * Created on March 5, 2014, 8:08 AM
 */

#ifndef RENDER_HPP
#define	RENDER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AnimatedSprite.hpp"

class Render {
public:
	Render();
	Render(const Render& orig);
	virtual ~Render();
	
	void SetTexture(sf::Texture &tex);
        void SetTextureRect(sf::IntRect rect);
	void PlayAnimation(Animation *animation);
        void UpdateAnimation(sf::Time elapsedTime);
        void StopAnimation();
        void SetFrame(sf::Time time);
        void InicializarAnimatedSprite(sf::Time seconds,bool a,bool b){ animatedSprite=AnimatedSprite(seconds,a,b); };
	void Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation);
        void DrawAnimation(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation); 
        void Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float *anglePrev, float *angleNew, float interpolation);
        void DrawAnimation(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation, float *anglePrev, float *angleNew);
        void DrawAnimationWithOut(sf::RenderWindow &window, const sf::Vector2f &pos);
        
        void SetOrigin(float x,float y){sprite.setOrigin(x,y);};
        void SetOriginAnimatedSprite(float x,float y){ animatedSprite.setOrigin(x,y); };
        void SetRotation(float angle){ animatedSprite.setRotation(angle); };
        void SetScale(float x, float y){ animatedSprite.setScale(x,y); };
	sf::Sprite &GetSprite() { return sprite; }
        AnimatedSprite &GetSpriteAnimated() { return animatedSprite; }
	sf::Vector2f GetRenderPosition() const { return renderPos; }
        sf::FloatRect GetGlobalBounds();

private:
        AnimatedSprite		animatedSprite;
	sf::Sprite		sprite;
	sf::Vector2f            renderPos;
        float                   renderAngle;
	
};

#endif	/* RENDER_H */

