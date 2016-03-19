#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "PhysicsState.hpp"
#include "Render.hpp"
#include "Animation.hpp"
#include "Hud.hpp"
#include "Heal.hpp"
#include "hFireBasic.hpp"
#include "hFireAdvanced.hpp"

class Player : public Render,public PhysicsState{
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
        //Animaciones de andar
        Animation               *walkingAnimationDown;
        Animation               *walkingAnimationLeft;
        Animation               *walkingAnimationRight;
        Animation               *walkingAnimationUp;
        //Animaciones spellcast
        Animation               *healingAnimationDown;
        Animation               *healingAnimationLeft;
        Animation               *healingAnimationRight;
        Animation               *healingAnimationUp;
        
	Hud                     *hud;
        Heal                    *hHeal;
        
        int                     contFuego=0;
        hFireAdvanced           *hFuegoAvanzado;
        hFireBasic              *hFuegoBasico;
        sf::Clock               clockCDFire;    //Variable de clase para el cd
        bool                    primercastFuego;    //Variable de clase para el primer casteo
        int                     getVida();
        int                     restaVida(int a);
        void                    heal();
private:
        sf::Texture             texturaPlayer;
        float                   velocity=200.f;
        int                     vida=15;
        sf::Clock               invulnerable;
};

#endif	/* PLAYER_H */

