/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.hpp
 * Author: joselu
 *
 * Created on 8 de marzo de 2016, 9:39
 */

#ifndef ENEMIGO_HPP
#define ENEMIGO_HPP

#include "PhysicsState.hpp"
#include "Render.hpp"

class Enemigo {
public:
	Enemigo();
	Enemigo(const Enemigo& orig);
	virtual ~Enemigo();
	
	void Inicializar(float posX, float posY, float speedX=0.f, float speedY=0.f, float maxSpeedX=1000.f, float maxSpeedY=1000.f);
	void Update(sf::Vector2f velocity, sf::Time elapsedTime);
	void Draw(sf::RenderWindow& window);
	void DrawWithInterpolation(sf::RenderWindow& window, float interpolation);
        float getVelocidad();
        sf::Vector2f getPosition();
        sf::Sprite getSprite();
        bool empujado;
        bool empujado2;
        sf::Clock tiempoempujado;
        float top,bot,left,right;
        void updateBounding();
        bool chamuscao;
        bool chamuscaoB;

         
	
private:
	Render			renderState;
	PhysicsState            physicsState;
        sf::Texture             texturaEnemigo;
        float                   velocity=200.f;
        
};


#endif /* ENEMIGO_HPP */

