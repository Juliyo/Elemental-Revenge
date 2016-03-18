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
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>
hRayBasic::hRayBasic() {
    draw = false;
    animation = new Animation();
    animationDurante = new Animation();
    
    if(!hTexture.loadFromFile("resources/Textures/rayo.png")){
       
       //comentario error
       exit(0);
   }
  // hSprite.setTexture(hTexture);
    //SetPosition()
     animationDurante->setSpriteSheet(hTexture);
     animationDurante->addFrame(sf::IntRect(0,0,64,233));
     animationDurante->addFrame(sf::IntRect(64,0,64,233));
     animationDurante->addFrame(sf::IntRect(128,0,64,233));
     animationDurante->addFrame(sf::IntRect(192,0,64,233));
     animationDurante->addFrame(sf::IntRect(256,0,64,233));
     animationDurante->addFrame(sf::IntRect(320,0,64,233));
     animationDurante->addFrame(sf::IntRect(384,0,64,233));
     animationDurante->addFrame(sf::IntRect(448,0,64,233));
     
    currentAnimation = &animationDurante;
    InicializarAnimatedSprite(sf::seconds(0.5f/8),true,false);
    SetOriginAnimatedSprite(41,233);
    
    
}

hRayBasic::hRayBasic(const hRayBasic& orig) {
}

hRayBasic::~hRayBasic() {
    
}

void hRayBasic::cast(sf::Vector2f posicion, sf::RenderWindow *mWindow) {
    

    draw=true;
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    //hSprite.setPosition(posicion);
    float angleShot = atan2(mousePosition.y - posicion.y, mousePosition.x - posicion.x);
    
    
    angleShot = (angleShot * 180 / 3.14)+90;
    SetAngle(angleshot2, angleShot);
    
    
    angleshot2 = angleShot; //so it goes in a straight line
    
    //GetSprite().setRotation((angleShot * 180 / 3.14)+90);
    
}
void hRayBasic::DrawWithInterpolation(sf::RenderWindow& window, float interpolation, PhysicsState *physicsState){
	DrawAnimation(window, physicsState->GetPreviousPosition(), physicsState->GetPosition() , interpolation, &anglePrev, &angleNew);
}