/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 23:05
 */

#include "../Headers/hRayBasic.hpp"
#include "../Headers/Player.hpp"
#include "Motor/Motor2D.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>



hRayBasic::hRayBasic() {
    
    
  

    
    draw = false;
    animation = new Animation();
    animationDurante = new Animation();
    PrimeraAnimacion = new Animation();
    setCD(4);
    setCast(3);
    if (!hTexture.loadFromFile("resources/Textures/RayoSpriteSheet.png")) {

        //comentario error
        exit(0);
    }
    // hSprite.setTexture(hTexture);
    //SetPosition()
    PrimeraAnimacion->setSpriteSheet("resources/Textures/RayoSpriteSheet.png");
    animationDurante->setSpriteSheet("resources/Textures/RayoSpriteSheet.png");

    animationDurante->addFrame(sf::IntRect(0, 445, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(0, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(0, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(0, 890, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(89, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89, 890, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 890, 89, 445));

    //PrimeraAnimacion->addFrame(sf::IntRect(0,0,89,445));

    animationDurante->addFrame(sf::IntRect(89 * 3, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 3, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 3, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 4, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 4, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 4, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 5, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 5, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 5, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 6, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 6, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 6, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 7, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 7, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 7, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 8, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 8, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 8, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 9, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 9, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 9, 890, 89, 445));

    currentAnimation = &PrimeraAnimacion;
    InicializarAnimatedSprite(sf::seconds(0.5f / 8), true, false);
    SetOriginAnimatedSprite(40, -30);
}

hRayBasic::hRayBasic(const hRayBasic& orig) {
}

hRayBasic::~hRayBasic() {

}

void hRayBasic::cast(sf::Vector2f posicion) {

      /*if(!buffer.loadFromFile("resources/Sounds/Pistola.wav")){
        exit(0);
    }

    sound.setBuffer(buffer);
    sound.play();
*/
    draw = true;
    float angleShot = Motor2D::Instance()->getAngleShot(posicion);

    angleShot = (angleShot * 180 / 3.14) + 270;
    SetAngle(angleshot2, angleShot);


    angleshot2 = angleShot; //so it goes in a straight line
}

void hRayBasic::DrawWithInterpolation(float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew) {
    DrawAnimation(posPrev, posNew, interpolation, &anglePrev, &angleNew);
}