/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InGame.cpp
 * Author: joselu
 * 
 * Created on 26 de marzo de 2016, 19:49
 */

#include "InGame.hpp"
#include "Game.hpp"

InGame::InGame() {
    player = new Player();
    player -> Inicializar(200.f, 250.f);
}

InGame::InGame(const InGame& orig) {
}

InGame::~InGame() {
}




void InGame::Update(sf::Time elapsedTime){
    
    if (!firstTime) {
        sf::Vector2f movement(0.f, 0.f);
        if (isMovingUp)
            movement.y -= player -> getVelocidad();
        if (isMovingDown)
            movement.y += player -> getVelocidad();
        if (isMovingLeft)
            movement.x -= player -> getVelocidad();
        if (isMovingRight)
            movement.x += player -> getVelocidad();

        player -> Update(movement, elapsedTime);

        if (player->hRayoBasico->tiempoCast.getElapsedTime().asSeconds() > player->hRayoBasico->getCast() && aux == true) {
            isShooting = false;
            player->hRayoBasico->primerCast = false;
        }

        if ((isShooting && player->hRayoBasico->tiempoCd.getElapsedTime().asSeconds() > player->hRayoBasico->getCD()) || (isShooting && player->hRayoBasico->primerCast == true)) {//Entra si dispara y el tiempo de enfriamiento ha pasado
            player->hRayoBasico->primerCast = false;
            if (aux == false) {//si es la primera vez que pulsa el boton
                player->hRayoBasico->tiempoCast.restart();

                aux = true; //no entra mas aqui para no hacer restart del cast
            }
            player->hRayoBasico->cast(sf::Vector2f(player->getPosition()), &mWindow); //siempre que entra aqui pintas

        } else {//entras si no disparas o si no ha pasado el tiempo de enfriamiento
            if (aux == true) {//entras si acabas de soltar el raton
                player->hRayoBasico->tiempoCd.restart();
                // std::cout<<"Inicio den CD"<<std::endl;
                aux = false; //no entra mas aqui para no hacer restart dl cd
            }
            player->hRayoBasico->draw = false;
        }
        //avanzado

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && player->hRayoAvanzado->tiempoCast.getElapsedTime().asSeconds() > player->hRayoBasico->getCast()) {
            player->hRayoAvanzado->draw = false;
            player->hRayoAvanzado->StopAnimation();
        }

    }

    firstTime = false;
    
    
}

void InGame::render(float interpolation, sf::Time elapsedTime){
   
}