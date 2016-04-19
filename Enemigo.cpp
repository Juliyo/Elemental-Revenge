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
        
        /*Reservamos memoria para los punteros de Animation*/
    
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    
    walkingAnimationDown->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationDown->addFrame(sf::IntRect(512, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(0, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(64, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(128, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(192, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(256, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(320, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(384, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(448, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(512, 640, 64, 64));
   
    
    walkingAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationLeft->addFrame(sf::IntRect(512, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(0, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(64, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(128, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(192, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(256, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(320, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(384, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(448, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(512, 576, 64, 64));
    
    walkingAnimationRight->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationRight->addFrame(sf::IntRect(512, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(0, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(64, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(128, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(192, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(256, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(320, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(384, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(448, 704, 64, 64));
    
    
    walkingAnimationUp->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationUp->addFrame(sf::IntRect(512, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(0, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(64, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(128, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(192, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(256, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(320, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(384, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(448, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(512, 512, 64, 64));
    
    
    currentAnimation = &walkingAnimationDown;
    renderState.InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
	physicsState.SetPosition(posX, posY);
	physicsState.SetSpeed(speedX, speedY);
	physicsState.SetMaxSpeed(maxSpeedX, maxSpeedY);
    renderState.SetOriginAnimatedSprite(32,38);

        empujado=false;
        empujado2=false;
}


void Enemigo::Update(sf::Vector2f velocity, sf::Time elapsedTime,Map *mapa){
    sf::Vector2f nVelocity = Util::Normalize(velocity);
	physicsState.SetSpeed(nVelocity * Enemigo::getVelocidad());
	physicsState.Update(elapsedTime,mapa);
}

void Enemigo::Draw(){
    
	renderState.GetSprite().setPosition(physicsState.GetPosition().x, physicsState.GetPosition().y);
        Motor2D::Instance()->draw(&renderState.GetSprite());
	//window.draw(renderState.GetSprite());
}


void Enemigo::DrawWithInterpolation( float interpolation) {
    
    renderState.DrawAnimation(physicsState.GetPreviousPosition(), physicsState.GetPosition(), interpolation);
}
float Enemigo::getVelocidad(){
    return velocity;
}
sf::Vector2f Enemigo::getPosition(){
    return physicsState.GetPosition();
}

Sprite Enemigo::getSprite(){
    return renderState.GetSprite();
}

void Enemigo::UpdateEnemyAnimation(int x,int y) {
    //sf::Vector2f distancia(mouseSprite.getPosition().y - player -> GetRenderPosition().y, mouseSprite.getPosition().x - player -> GetRenderPosition().x);
   
    // 1 -> Arriba
    // 2 -> Abajo
    // 3 -> Derecha
    // 4 -> Izquierda
    
    if (abs(y) > abs(x) && y <= 0) {
        cuadrante = 1;
        currentAnimation = &walkingAnimationUp;
    } else if (abs(y) > abs(x) && y > 0) {
        currentAnimation = &walkingAnimationDown;
        cuadrante = 2;
    } else if (abs(x) > abs(y) && x > 0) {
        currentAnimation = &walkingAnimationRight;
        cuadrante = 3;
    } else {
        currentAnimation = &walkingAnimationLeft;
        cuadrante = 4;
    }
    
}

void Enemigo::PlayAnimation(Animation* animation) {
renderState.PlayAnimation(animation);
}

void Enemigo::UpdateAnimation(sf::Time elapsedTime) {
    renderState.UpdateAnimation(elapsedTime);
}

void Enemigo::StopAnimation() {
renderState.StopAnimation();
}
