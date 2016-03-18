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

Flash::Flash() {
}

Flash::Flash(const Flash& orig) {
}

Flash::~Flash() {
}

sf::Vector2f Flash::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {



    if (clockCd.getElapsedTime().asSeconds() > 5 || primerCast == true) {
        primerCast = false;

        clockCd.restart();
        sf::Vector2f vectorFinal;
        sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
        // sf::Vector2f playerposition = player->getPosition();

        float angleShot = atan2(mousePosition.y - posicion.y, mousePosition.x - posicion.x);
        angleshot2 = angleShot;

        if (mousePosition.x > posicion.x) {
            if (abs(mousePosition.x) - abs(posicion.x) < 100 && abs(mousePosition.x) - abs(posicion.x) > 0) {
                vectorFinal.x = mousePosition.x;
            }
            else {
                vectorFinal.x = 100 * (cos(angleshot2) * 1.0f) + posicion.x;
            }
        } else {
            if (abs(mousePosition.x) - abs(posicion.x) > 100 && abs(mousePosition.y) - abs(posicion.y) > 100) {
                vectorFinal.x = mousePosition.x;
            }
            else {
                vectorFinal.x = 100 * (cos(angleshot2) * 1.0f) + posicion.x;
            }
        }
        if (mousePosition.y > posicion.y) {
            if (abs(mousePosition.y) - abs(posicion.y) < 100) {
                vectorFinal.y = mousePosition.y;
            }
            else {
                vectorFinal.y = 100 * (sin(angleshot2) * 1.0f) + posicion.y;
            }
        }
        else {
            if (abs(posicion.y) - abs(mousePosition.y) < 100) {
                vectorFinal.y = mousePosition.y;
            }
            else {
                vectorFinal.y = 100 * (sin(angleshot2) * 1.0f) + posicion.y;
            }
        }
        return vectorFinal;

    }

    return posicion;

}
