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
    PrimeraAnimacion  = new Animation();
    setCD(4);
    setCast(3);
    if(!hTexture.loadFromFile("resources/Textures/RayoSpriteSheet.png")){
       
       //comentario error
       exit(0);
   }
  // hSprite.setTexture(hTexture);
    //SetPosition()
     PrimeraAnimacion->setSpriteSheet(hTexture);
     animationDurante->setSpriteSheet(hTexture);
     
     
     
    animationDurante->addFrame(sf::IntRect(0,445,89,445));
     
     PrimeraAnimacion->addFrame(sf::IntRect(0,0,89,445));
     PrimeraAnimacion->addFrame(sf::IntRect(0,445,89,445));
     PrimeraAnimacion->addFrame(sf::IntRect(0,890,89,445));
     
     PrimeraAnimacion->addFrame(sf::IntRect(89,0,89,445));
     PrimeraAnimacion->addFrame(sf::IntRect(89,445,89,445));
     PrimeraAnimacion->addFrame(sf::IntRect(89,890,89,445));
     
     PrimeraAnimacion->addFrame(sf::IntRect(89*2,0,89,445));
     PrimeraAnimacion->addFrame(sf::IntRect(89*2,445,89,445));
     PrimeraAnimacion->addFrame(sf::IntRect(89*2,890,89,445));
     
     //PrimeraAnimacion->addFrame(sf::IntRect(0,0,89,445));
    
     
     

     animationDurante->addFrame(sf::IntRect(89*3,0,89,445));
     animationDurante->addFrame(sf::IntRect(89*3,445,89,445));
     animationDurante->addFrame(sf::IntRect(89*3,890,89,445));
     
     animationDurante->addFrame(sf::IntRect(89*4,0,89,445));
     animationDurante->addFrame(sf::IntRect(89*4,445,89,445));
     animationDurante->addFrame(sf::IntRect(89*4,890,89,445));
     
     animationDurante->addFrame(sf::IntRect(89*5,0,89,445));
     animationDurante->addFrame(sf::IntRect(89*5,445,89,445));
     animationDurante->addFrame(sf::IntRect(89*5,890,89,445));
     
     animationDurante->addFrame(sf::IntRect(89*6,0,89,445));
     animationDurante->addFrame(sf::IntRect(89*6,445,89,445));
     animationDurante->addFrame(sf::IntRect(89*6,890,89,445));
     
     animationDurante->addFrame(sf::IntRect(89*7,0,89,445));
     animationDurante->addFrame(sf::IntRect(89*7,445,89,445));
     animationDurante->addFrame(sf::IntRect(89*7,890,89,445));
     
     animationDurante->addFrame(sf::IntRect(89*8,0,89,445));
     animationDurante->addFrame(sf::IntRect(89*8,445,89,445));
     animationDurante->addFrame(sf::IntRect(89*8,890,89,445));
     
     animationDurante->addFrame(sf::IntRect(89*9,0,89,445));
     animationDurante->addFrame(sf::IntRect(89*9,445,89,445));
     animationDurante->addFrame(sf::IntRect(89*9,890,89,445));
     
     
     
     
     
    currentAnimation = &PrimeraAnimacion;
    InicializarAnimatedSprite(sf::seconds(0.5f/8),true,false);
    SetOriginAnimatedSprite(40,-30);
    
    
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
    
    
    angleShot = (angleShot * 180 / 3.14)+270;
    SetAngle(angleshot2, angleShot);
    
    
    angleshot2 = angleShot; //so it goes in a straight line
    
    //GetSprite().setRotation((angleShot * 180 / 3.14)+90);
    
}
void hRayBasic::DrawWithInterpolation(sf::RenderWindow& window, float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew){
	DrawAnimation(window,posPrev, posNew , interpolation, &anglePrev, &angleNew);
}

void hRayBasic::updateBounding(){

    //GetSpriteAnimated()->getGlobalBounds();
       bot=GetSpriteAnimated().getGlobalBounds().top+ GetSpriteAnimated().getGlobalBounds().height-110;
       top=GetSpriteAnimated().getGlobalBounds().top+100;
       right=GetSpriteAnimated().getGlobalBounds().left+ GetSpriteAnimated().getGlobalBounds().width;
       left=GetSpriteAnimated().getGlobalBounds().left;
       
}
bool hRayBasic::colision(Enemigo *e){
    if(right<e->left || left>e->right || top>e->bot || bot<e->top){
        return false;
    }
    return true;
}