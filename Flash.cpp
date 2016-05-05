/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Flash.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 23:20
 */

#include "../Headers/Flash.hpp"
#include "States/InGame.hpp"
#include "Otros/tmxHelper.hpp"

void Flash::CreateBody() {

}


Flash::Flash(int animation): Collisionable((Entity*)this) {
    dibujar = false;
    switch (animation) {
        case 1: //Animacion que aparece en la posicion que deja el jugador

            flashingAnimation = new Animation();

            flashingAnimation->setSpriteSheet("resources/Textures/flash1.png");

            flashingAnimation->addFrame(sf::IntRect(0, 0, 200, 112));
            flashingAnimation->addFrame(sf::IntRect(200, 0, 200, 112));

            flashingAnimation->addFrame(sf::IntRect(0, 112, 200, 112));
            flashingAnimation->addFrame(sf::IntRect(200, 112, 200, 112));

            flashingAnimation->addFrame(sf::IntRect(0, 112 * 2, 200, 112));
            flashingAnimation->addFrame(sf::IntRect(200, 112 * 2, 200, 112));

            flashingAnimation->addFrame(sf::IntRect(0, 112 * 3, 200, 112));
            flashingAnimation->addFrame(sf::IntRect(200, 112 * 3, 200, 112));

            flashingAnimation->addFrame(sf::IntRect(0, 112 * 3, 200, 112));
            flashingAnimation->addFrame(sf::IntRect(200, 112 * 3, 200, 112));

            flashingAnimation->addFrame(sf::IntRect(0, 112 * 5, 200, 112));
            flashingAnimation->addFrame(sf::IntRect(200, 112 * 5, 200, 112));

            flashingAnimation->addFrame(sf::IntRect(0, 112 * 6, 200, 112));
            flashingAnimation->addFrame(sf::IntRect(200, 112 * 6, 200, 112));

            flashingAnimation->addFrame(sf::IntRect(0, 112 * 7, 200, 112));
            flashingAnimation->addFrame(sf::IntRect(200, 112 * 7, 200, 112));

            InicializarAnimatedSprite(sf::seconds(0.05f), true, false);
            SetOriginAnimatedSprite(200 / 2, 112 / 2);
            setCD(5.f);
            break;
        case 2: //Animacion que aparece a la posicion en que se ha movido el jugador
            flashingAnimation2 = new Animation();

            flashingAnimation2->setSpriteSheet("resources/Textures/flash2.png");
            flashingAnimation2->addFrame(sf::IntRect(0, 0, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200, 0, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 2, 0, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 3, 0, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 4, 0, 200, 112));

            flashingAnimation2->addFrame(sf::IntRect(0, 112, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200, 112, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 2, 112, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 3, 112, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 4, 112, 200, 112));

            flashingAnimation2->addFrame(sf::IntRect(0, 112 * 2, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200, 112 * 2, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 2, 112 * 2, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 3, 112 * 2, 200, 112));
            flashingAnimation2->addFrame(sf::IntRect(200 * 4, 112 * 2, 200, 112));

            InicializarAnimatedSprite(sf::seconds(0.05f), true, false);
            SetOriginAnimatedSprite(200 / 2, 112 / 2);
            SetScale(0.7f,0.7f);
            setCD(5.f);
            break;
    }
}

Flash::~Flash() {
}

std::string Flash::getClassName() {

}


sf::Vector2f Flash::cast(sf::Vector2f posicion,Hud *hud) {


    if (clockCd.getTiempo() > getCD() || primerCast == true) {
        primerCast = false;
        dibujar = true;
        SetPosition(posicion);
        clockCd.restart();
        hud->resetFlash();
        tiempoCast.restart();
        sf::Vector2f vectorFinal;
        sf::Vector2f mousePosition=Motor2D::Instance()->getMousePosition();
        float angleShot = Motor2D::Instance()->getAngleShot(posicion);
        angleshot2 = angleShot;

        if (mousePosition.x > posicion.x) {
            if (abs(mousePosition.x) - abs(posicion.x) < 100 && abs(mousePosition.x) - abs(posicion.x) > 0) {
                vectorFinal.x = mousePosition.x;
            } else {
                vectorFinal.x = 100 * (cos(angleshot2) * 1.0f) + posicion.x;
            }
        } else {
            if (abs(mousePosition.x) - abs(posicion.x) > 100 && abs(mousePosition.y) - abs(posicion.y) > 100) {
                vectorFinal.x = mousePosition.x;
            } else {
                vectorFinal.x = 100 * (cos(angleshot2) * 1.0f) + posicion.x;
            }
        }
        if (mousePosition.y > posicion.y) {
            if (abs(mousePosition.y) - abs(posicion.y) < 100) {
                vectorFinal.y = mousePosition.y;
            } else {
                vectorFinal.y = 100 * (sin(angleshot2) * 1.0f) + posicion.y;
            }
        } else {
            if (abs(posicion.y) - abs(mousePosition.y) < 100) {
                vectorFinal.y = mousePosition.y;
            } else {
                vectorFinal.y = 100 * (sin(angleshot2) * 1.0f) + posicion.y;
            }
        }
        return vectorFinal;

    }

    return posicion;

}

void Flash::cast2(Reloj *clockCD2) {
    if (clockCD2->getTiempo() > getCD() || primerCast == true) {
        
        primerCast = false;
        dibujar = true;
        tiempoCast.restart();
    }

}

void Flash::Draw() {
    DrawAnimationWithOut(GetPosition());
}

void Flash::DrawWithInterpolation( float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew) {
    DrawAnimation( posPrev, posNew, interpolation);
}