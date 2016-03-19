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

Flash::Flash(int animation) {
    dibujar = false;
    switch (animation) {
        case 1: //Animacion que aparece en la posicion que deja el jugador
            if (!hTexture.loadFromFile("resources/Textures/flash1.png")) {
                std::cout << "No se ha podido cargar flash1.png" << std::endl;
                exit(0);
            }
            flashingAnimation = new Animation();

            flashingAnimation->setSpriteSheet(hTexture);

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
            if (!hTexture2.loadFromFile("resources/Textures/flash2.png")) {
                std::cout << "No se ha podido cargar flash2.png" << std::endl;
                exit(0);
            }
            flashingAnimation2->setSpriteSheet(hTexture2);
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

Flash::Flash(const Flash& orig) {
}

Flash::~Flash() {
}

sf::Vector2f Flash::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {


    if (clockCd.getElapsedTime().asSeconds() > getCD() || primerCast == true) {
        primerCast = false;
        dibujar = true;
        SetPosition(posicion);
        clockCd.restart();
        tiempoCast.restart();
        sf::Vector2f vectorFinal;
        sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));

        float angleShot = atan2(mousePosition.y - posicion.y, mousePosition.x - posicion.x);
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

void Flash::cast2(sf::Clock *clockCD2) {
    if (clockCD2->getElapsedTime().asSeconds() > getCD() || primerCast == true) {
        
        primerCast = false;
        dibujar = true;
        tiempoCast.restart();
    }

}

void Flash::Draw(sf::RenderWindow& window) {
    DrawWithout(window, GetPosition());
}

void Flash::DrawWithInterpolation(sf::RenderWindow& window, float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew) {
    DrawAnimation(window, posPrev, posNew, interpolation);
}