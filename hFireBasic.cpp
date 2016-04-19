/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hFireBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 12:45
 */

#include "../Headers/hFireBasic.hpp"

hFireBasic::hFireBasic() {



    animationInicio = new Animation();
    animationInicio->setSpriteSheet("resources/Textures/FuegoSpriteSheet.png");
    animationInicio->addFrame(sf::IntRect(0, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 0, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 148, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 148, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 148, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 148, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 148, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 296, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 296, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 296, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 296, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 296, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 444, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 444, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 444, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 444, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 444, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 592, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 592, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 592, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 592, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 592, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 740, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 740, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 740, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 740, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 740, 152, 148));
    InicializarAnimatedSprite(sf::seconds(0.02f), true, false);
    SetOriginAnimation(0, 147 / 2);
    SetScaleAnimation(0.2, 0.2);
    //hSprite.setPosition(0, 0);


    /*SetTexture(hTexture);
    SetTextureRect(sf::IntRect(0, 0, 100, 81));
    SetScale(0.2,0.2);*/
    // SetPosition(0,0);

}

hFireBasic::hFireBasic(const hFireBasic& orig) {

}

hFireBasic::~hFireBasic() {
}

void hFireBasic::cast(sf::Vector2f posicion) {


    SetPosition(posicion);

    float angleShot = Motor2D::Instance()->getAngleShot(posicion);
    angleshot2 = angleShot; //so it goes in a straight line
    SetRotationAnimation(angleShot * 180 / 3.14);


}

void hFireBasic::DrawWithInterpolation(float interpolation) {
    Draw(GetPreviousPosition(), GetPosition(), interpolation);
}

void hFireBasic::Update2(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    Update(elapsedTime);
}
