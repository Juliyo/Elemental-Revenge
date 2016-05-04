/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisparoEnemigo.cpp
 * Author: joselu
 * 
 * Created on 3 de mayo de 2016, 10:04
 */

#include "DisparoEnemigo.hpp"

DisparoEnemigo::DisparoEnemigo() {
    
    motor = Motor2D::Instance();
    
    

    SetTexture("resources/Textures/DisparoDragon.png");
    SetOrigin(47,24);
    SetScale(0.1,0.1);
    SetPosition(-10000,-10000);
    
    
    disparo.setRadius(10);
    disparo.setOutlineColor(sf::Color::Red);
    
    
}

DisparoEnemigo::DisparoEnemigo(const DisparoEnemigo& orig) {
}

DisparoEnemigo::~DisparoEnemigo() {
}

void DisparoEnemigo::Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer) {

    
    PhysicsState::SetPosition(vector);

    float angleShot = atan2(vectorPlayer.y-vector.y, vectorPlayer.x-vector.x);
    angleshot2 = angleShot; //so it goes in a straight line
    SetRotation(angleshot2);
    
}

void DisparoEnemigo::RenderDisparo(float interpolation) {

    Draw(GetPreviousPosition(), GetPosition(), interpolation);
}


void DisparoEnemigo::Update2(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    PhysicsState::Update(elapsedTime);
}
