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
#include "Hud.hpp"
#include "hRayAdvanced.hpp"
#include "hRayBasic.hpp"
#include "hFireBasic.hpp"
#include "hFireAdvanced.hpp"
#include "hWaterBasic.hpp"
#include "hWaterAdvanced.hpp"
#include "Heal.hpp"
#include "Flash.hpp"
#include "Enemigo.hpp"
#include "../Motor/Motor2D.hpp"

class Player : public Render, public PhysicsState{
public:
	Player();
	Player(const Player& orig);
	virtual ~Player();
	static Player* Instance();
	void Inicializar(float posX, float posY, float speedX=0.f, float speedY=0.f, float maxSpeedX=1000.f, float maxSpeedY=1000.f);
	void Update(sf::Vector2f velocity, sf::Time elapsedTime);
	void Draw();
	void DrawWithInterpolation(float interpolation);
        float getVelocidad();
        PhysicsState* getPhysics();
        void UpdatePlayerAnimation(int x, int y);
        sf::Vector2f getPosition();
        Animation** getAnimation(){ return currentAnimation; };
        void updateRayo(bool isShooting);
        void updateFuego(bool fuegoBasicCast,bool fuegoAdvancedCast, sf::Time elapsedTime);
        void updateAgua(bool aguaBasicCast,bool aguaAdvancedCast, sf::Time elapsedTime,sf::Vector2f movement);
        void updateFlash();
        void renderRayo(sf::Time elapsedTime, float interpolation);
        void renderFuego(sf::Time elapsedTime, float interpolation);
        void renderAgua(sf::Time elapsedTime, float interpolation);
        void renderHeal(sf::Time elapsedTime, float interpolation);
        void renderFlash(sf::Time elapsedTime, float interpolation);
        
        void Colocar(sf::Vector2f NuevaPosicion);
        
        hRayBasic     *hRayoBasico;
        hRayAdvanced  *hRayoAvanzado;
        
        
        //Fuego
        hFireBasic              *hFuegoBasico;
        hFireAdvanced           *hFuegoAvanzado;
        int                     contFuego=0;
        Reloj               clockCDFire;    //Variable de clase para el cd
        float                   CDFire=0.35f;
        Reloj               castFire;    //Variable de clase para el casteo
        Reloj               castFire2;    //Variable de clase para el casteo
        bool                    primercastFuego;    //Variable de clase para el primer casteo
  
        
        ///Aguaa
        hWaterBasic             *hAguaBasico;
        hWaterAdvanced          *hAguaAvanzado;
        
        
        
        ///
        
        Animation               **currentAnimation;
        Animation               *walkingAnimationDown;
        Animation               *walkingAnimationLeft;
        Animation               *walkingAnimationRight;
        Animation               *walkingAnimationUp;
        //Fuego
        Animation               *castingAnimationUpFuego;
        Animation               *castingAnimationDownFuego;
        Animation               *castingAnimationRightFuego;
        Animation               *castingAnimationLeftFuego;
        //Rayo
        Animation               *castingAnimationUpRayo;
        Animation               *castingAnimationDownRayo;
        Animation               *castingAnimationRightRayo;
        Animation               *castingAnimationLeftRayo;
        //Agua
        Animation               *castingAnimationUpAgua;
        Animation               *castingAnimationDownAgua;
        Animation               *castingAnimationRightAgua;
        Animation               *castingAnimationLeftAgua;
                
                //Animaciones fuego1
        Animation               *fuegoAnimationDown;
        Animation               *fuegoAnimationLeft;
        Animation               *fuegoAnimationRight;
        Animation               *fuegoAnimationUp;
        //Animaciones fuego2
        Animation               *fuego2AnimationDown;
        Animation               *fuego2AnimationLeft;
        Animation               *fuego2AnimationRight;
        Animation               *fuego2AnimationUp;
        //Animaciones heal
        Animation               *healingAnimationDown;
        Animation               *healingAnimationLeft;
        Animation               *healingAnimationRight;
        Animation               *healingAnimationUp;
        
	Hud                     *hud;
        int                     cuadrante;
        
        //heal
        Heal                    *hHeal;
        int                     getVida();
        int                     restaVida(int a);
        void                    heal();
        //flash
        Flash                   *flash;
        Flash                   *flash2;
        bool                    isFlashing=false;
private:
        static Player           *mInstance;
        sf::Texture             texturaPlayer;
        float                   velocity=200.f;
        int                     vida=15;
        PhysicsState            physicsState;
        Reloj                   invulnerable;
        bool                    aux;
        bool                    cantMove=false;
};

#endif	/* PLAYER_H */

