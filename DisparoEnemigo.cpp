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

    
    disparo.setRadius(10);
    disparo.setOutlineColor(sf::Color::Red);
    
    
}

DisparoEnemigo::DisparoEnemigo(const DisparoEnemigo& orig) {
}

DisparoEnemigo::~DisparoEnemigo() {
}

void DisparoEnemigo::Disparar(float x, float y) {

  //  sf::Vector2f vector(x, y);
    
    disparo->setPosition(x,y);

    float angleShot = Motor2D::Instance()->getAngleShot(posicion);
    angleshot2 = angleShot; //so it goes in a straight line
    
}

void DisparoEnemigo::RenderDisparo() {

    Motor2D::Instance()->draw(disparo);
    
}


