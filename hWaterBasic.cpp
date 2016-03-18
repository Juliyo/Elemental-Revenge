/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hWaterBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 23:06
 */

#include "../Headers/hWaterBasic.hpp"
#ifdef _WIN32
#include <Windows.h>
#include <iostream>
#include "../Headers/AnimatedSprite.hpp"
#include "../Headers/Animation.hpp"
#endif

hWaterBasic::hWaterBasic() {
    animation = new Animation();

    if (!hTexture.loadFromFile("resources/Textures/sprite-agua.png")) {
        std::cout << "Error cargando la textura: resources/Textures/sprite-agua.png" << std::endl;
        exit(0);
    }
    animation->setSpriteSheet(hTexture);
    animation->addFrame(sf::IntRect(735, 0, 147, 147));
    animation->addFrame(sf::IntRect(735, 147, 147, 147));
    animation->addFrame(sf::IntRect(735, 294, 147, 147));
    animation->addFrame(sf::IntRect(735, 441, 147, 147));
    animation->addFrame(sf::IntRect(735, 588, 147, 147));
    animation->addFrame(sf::IntRect(588, 0, 147, 147));
    animation->addFrame(sf::IntRect(588, 147, 147, 147));
    animation->addFrame(sf::IntRect(588, 294, 147, 147));
    animation->addFrame(sf::IntRect(588, 441, 147, 147));
    animation->addFrame(sf::IntRect(588, 588, 147, 147));
    animation->addFrame(sf::IntRect(441, 0, 147, 147));
    animation->addFrame(sf::IntRect(441, 147, 147, 147));
    animation->addFrame(sf::IntRect(441, 294, 147, 147));
    animation->addFrame(sf::IntRect(441, 441, 147, 147));
    animation->addFrame(sf::IntRect(441, 588, 147, 147));
    animation->addFrame(sf::IntRect(294, 0, 147, 147));
    animation->addFrame(sf::IntRect(294, 147, 147, 147));
    animation->addFrame(sf::IntRect(294, 294, 147, 147));
    animation->addFrame(sf::IntRect(294, 441, 147, 147));
    animation->addFrame(sf::IntRect(294, 588, 147, 147));
    animation->addFrame(sf::IntRect(147, 0, 147, 147));
    animation->addFrame(sf::IntRect(147, 147, 147, 147));
    animation->addFrame(sf::IntRect(147, 294, 147, 147));
    animation->addFrame(sf::IntRect(147, 441, 147, 147));
    animation->addFrame(sf::IntRect(147, 588, 147, 147));
    animation->addFrame(sf::IntRect(0, 0, 147, 147));
    animation->addFrame(sf::IntRect(0, 147, 147, 147));
    animation->addFrame(sf::IntRect(0, 294, 147, 147));
    animation->addFrame(sf::IntRect(0, 441, 147, 147));
    animation->addFrame(sf::IntRect(0, 588, 147, 147));
    InicializarAnimatedSprite(sf::seconds(0.5f / 29), true, false);
    SetOriginAnimatedSprite(0, 147 / 2);
    SetScale(0.5f, 0.5f);
    setCD(1.0f);
}

hWaterBasic::hWaterBasic(const hWaterBasic& orig) {
}

hWaterBasic::~hWaterBasic() {


}

void hWaterBasic::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {

    if (clockCd.getElapsedTime().asSeconds() > getCD() || primerCast == true) {
        clockCd.restart();
        primerCast = false;
        sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));

        float angleShot = atan2(mousePosition.y - posicion.y, mousePosition.x - posicion.x);
        angleshot2 = angleShot;
        //Ponemos el sprite en la posicion del jugador y separado un distancia del jugador
        SetPosition(posicion.x + 10 * cos(angleshot2) * 1.0f, posicion.y + 20 * sin(angleshot2) * 1.0f);
        tiempoCast.restart();
        dibujar = true;
        SetAngle(angleShot * 180 / 3.14);
    }


}

void hWaterBasic::DrawWithInterpolation(sf::RenderWindow& window, float interpolation) {
    DrawAnimation(window, GetPreviousPosition(), GetPosition(), interpolation);
}

void hWaterBasic::Update(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    PhysicsState::Update(elapsedTime);
}

void hWaterBasic::setDibujar(bool NuevoDibujar) {
    dibujar = NuevoDibujar;
}