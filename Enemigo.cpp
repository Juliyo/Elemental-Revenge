/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.cpp
 * Author: joselu
 * 
 * Created on 8 de marzo de 2016, 9:30
 */

#include "Enemigo.hpp"

Enemigo::Enemigo() {
}

Enemigo::Enemigo(const Enemigo& orig) {
}

Enemigo::~Enemigo() {
}

void Enemigo::Inicializar(float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY){
        texturaEnemigo.loadFromFile("resources/Textures/ninja.png");
	renderState.SetTexture(texturaEnemigo);
        sf::IntRect rect(0, 0, 96, 96);
        renderState.SetTextureRect(rect);
        renderState.GetSprite().setScale(0.5,0.5);
	physicsState.SetPosition(posX, posY);
	physicsState.SetSpeed(speedX, speedY);
	physicsState.SetMaxSpeed(maxSpeedX, maxSpeedY);
}


void Enemigo::Update(sf::Vector2f velocity, sf::Time elapsedTime){
	physicsState.SetSpeed(velocity);
	physicsState.Update(elapsedTime);
}

void Enemigo::Draw(sf::RenderWindow& window){
	renderState.GetSprite().setPosition(physicsState.GetPosition());
	window.draw(renderState.GetSprite());
}

void Enemigo::DrawWithInterpolation(sf::RenderWindow& window, float interpolation){

	renderState.Draw(window, physicsState.GetPreviousPosition(), physicsState.GetPosition(), interpolation);
}
float Enemigo::getVelocidad(){
    return velocity;
}
sf::Vector2f Enemigo::getPosition(){
    return renderState.GetSprite().getPosition();
}

sf::Sprite Enemigo::getSprite(){
    return renderState.GetSprite();
}

