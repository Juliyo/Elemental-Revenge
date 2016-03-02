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


class Render {
public:
	Render();
	Render(const Render& orig);
	virtual ~Render();
	
	void SetTexture(sf::Texture &tex);
        void SetTextureRect(sf::IntRect rect);
        void SetOrigin(float x, float y);
	void Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation);
	sf::Sprite &GetSprite() { return sprite; }
	sf::Vector2f GetRenderPosition() const { return renderPos; }

private:
	sf::Sprite		sprite;
	sf::Vector2f            renderPos;
};

#endif	/* RENDER_H */

