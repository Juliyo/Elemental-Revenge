/* 
 * File:   Player.h
 * Author: linuxero
 *
 * Created on March 5, 2014, 7:43 AM
 */

#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "PhysicsState.hpp"
#include "Render.hpp"
#include "Animation.hpp"

class Player : public Render, PhysicsState{
public:
	Player();
	Player(const Player& orig);
	virtual ~Player();
	
	void Inicializar(float posX, float posY, float speedX=0.f, float speedY=0.f, float maxSpeedX=1000.f, float maxSpeedY=1000.f);
	void Update(sf::Vector2f velocity, sf::Time elapsedTime);
	void Draw(sf::RenderWindow& window);
	void DrawWithInterpolation(sf::RenderWindow& window, float interpolation);
        float getVelocidad();
        sf::Vector2f getPosition();
        Animation** getAnimation(){ return currentAnimation; };
        
        Animation               **currentAnimation;
        Animation               *walkingAnimationDown;
        Animation               *walkingAnimationLeft;
        Animation               *walkingAnimationRight;
        Animation               *walkingAnimationUp;
	
private:
        sf::Texture             texturaPlayer;
        float                   velocity=200.f;
        
};

#endif	/* PLAYER_H */

