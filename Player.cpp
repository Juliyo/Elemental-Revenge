/* 
 * File:   Player.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 7:43 AM
 */

#include "Player.hpp"
#include "Util.hpp"

Player::Player() {
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

void Player::Inicializar(float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    castingAnimationUp= new Animation();
    castingAnimationDown= new Animation();
    castingAnimationRight= new Animation();
    castingAnimationLeft= new Animation();
    hud = new Hud();
    hAguaAvanzado = new hWaterAdvanced();
    hAguaBasico = new hWaterBasic();
            
    if(!texturaPlayer.loadFromFile("resources/Textures/player.png")){
       std::cout<<"Error cargando la textura: "<<"resources/Textures/player.png"<<std::endl;
       exit(0);
    }
    texturaPlayer.setSmooth(true);
    
    walkingAnimationDown->setSpriteSheet(texturaPlayer);
    walkingAnimationDown->addFrame(sf::IntRect(512, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(0, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(64, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(128, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(192, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(256, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(320, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(384, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(448, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(512, 640, 64, 64));
   
    
    walkingAnimationLeft->setSpriteSheet(texturaPlayer);
    walkingAnimationLeft->addFrame(sf::IntRect(512, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(0, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(64, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(128, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(192, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(256, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(320, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(384, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(448, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(512, 576, 64, 64));
    
    walkingAnimationRight->setSpriteSheet(texturaPlayer);
    walkingAnimationRight->addFrame(sf::IntRect(512, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(0, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(64, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(128, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(192, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(256, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(320, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(384, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(448, 704, 64, 64));
    
    
    walkingAnimationUp->setSpriteSheet(texturaPlayer);
    walkingAnimationUp->addFrame(sf::IntRect(512, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(0, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(64, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(128, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(192, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(256, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(320, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(384, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(448, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(512, 512, 64, 64));
    
    //casteo
    castingAnimationUp->setSpriteSheet(texturaPlayer);
    castingAnimationUp->addFrame(sf::IntRect(448, 256, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(0, 256, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(64, 256, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(128, 256, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(192, 256, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(256, 256, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(320, 256, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(384, 256, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(448, 256, 64, 64));
  
    
    
    castingAnimationDown->setSpriteSheet(texturaPlayer);
    castingAnimationDown->addFrame(sf::IntRect(448, 384, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(0, 384, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(64, 384, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(128, 384, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(192, 384, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(256, 384, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(320, 384, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(384, 384, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(448, 384, 64, 64));
    
    
    castingAnimationRight->setSpriteSheet(texturaPlayer);
    castingAnimationRight->addFrame(sf::IntRect(448, 448, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(0, 448, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(64, 448, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(128, 448, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(192, 448, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(256, 448, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(320, 448, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(384, 448, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(448, 448, 64, 64));
    
    
    castingAnimationLeft->setSpriteSheet(texturaPlayer);
    castingAnimationLeft->addFrame(sf::IntRect(448, 320, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(0, 320, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(64, 320, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(128, 320, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(192, 320, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(256, 320, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(320, 320, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(384, 320, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(448, 320, 64, 64));
    
    
    currentAnimation = &walkingAnimationDown;
    InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    SetPosition(posX, posY);
    SetSpeed(speedX, speedY);
    SetMaxSpeed(maxSpeedX, maxSpeedY);
    SetOriginAnimatedSprite(32,38);
}

void Player::Update(sf::Vector2f velocity, sf::Time elapsedTime) {
    /**Hay que normalizar la velocidad**/
    sf::Vector2f nVelocity = Util::Normalize(velocity);
    SetSpeed(nVelocity * Player::getVelocidad());
    PhysicsState::Update(elapsedTime);
}

void Player::Draw(sf::RenderWindow& window) {
    GetSprite().setPosition(GetPosition());
    window.draw(GetSprite());
}

void Player::DrawWithInterpolation(sf::RenderWindow& window, float interpolation) {
    Render::DrawAnimation(window, GetPreviousPosition(), GetPosition(), interpolation);
}

float Player::getVelocidad() {
    return velocity;
}
sf::Vector2f Player::getPosition() {
    return GetSpriteAnimated().getPosition();
}

void Player::UpdatePlayerAnimation(int x,int y) {
    //sf::Vector2f distancia(mouseSprite.getPosition().y - player -> GetRenderPosition().y, mouseSprite.getPosition().x - player -> GetRenderPosition().x);
   
    // 1 -> Arriba
    // 2 -> Abajo
    // 3 -> Derecha
    // 4 -> Izquierda


    if (abs(y) > abs(x) && y <= 0) {
        cuadrante = 1;
        currentAnimation = &walkingAnimationUp;
    } else if (abs(y) > abs(x) && y > 0) {
        currentAnimation = &walkingAnimationDown;
        cuadrante = 2;
    } else if (abs(x) > abs(y) && x > 0) {
        currentAnimation = &walkingAnimationRight;
        cuadrante = 3;
    } else {
        currentAnimation = &walkingAnimationLeft;
        cuadrante = 4;
    }
}