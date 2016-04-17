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
    hRayoBasico = new hRayBasic();
    hRayoAvanzado = new hRayAdvanced();
            
    if(!texturaPlayer.loadFromFile("resources/Textures/player.png")){
       std::cout<<"Error cargando la textura: "<<"resources/Textures/player.png"<<std::endl;
       exit(0);
    }
    texturaPlayer.setSmooth(true);
    
    walkingAnimationDown->setSpriteSheet("resources/Textures/player.png");
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
   
    
    walkingAnimationLeft->setSpriteSheet("resources/Textures/player.png");
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
    
    walkingAnimationRight->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationRight->addFrame(sf::IntRect(512, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(0, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(64, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(128, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(192, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(256, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(320, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(384, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(448, 704, 64, 64));
    
    
    walkingAnimationUp->setSpriteSheet("resources/Textures/player.png");
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
    castingAnimationUp->setSpriteSheet("resources/Textures/player.png");
    castingAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(0, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(64, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(128, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(192, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(256, 768, 64, 64));
    castingAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
  
  
    
    
    castingAnimationDown->setSpriteSheet("resources/Textures/player.png");
    castingAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(0, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(64, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(128, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(192, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(256, 896, 64, 64));
    castingAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
 
    
    
    castingAnimationRight->setSpriteSheet("resources/Textures/player.png");
    castingAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(0, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(64, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(128, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(192, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(256, 960, 64, 64));
    castingAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
  
    
    
    castingAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    castingAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(0, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(64, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(128, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(192, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(256, 832, 64, 64));
    castingAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));
 
    
    
    currentAnimation = &walkingAnimationDown;
    InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    SetPosition(posX, posY);
    SetSpeed(speedX, speedY);
    SetMaxSpeed(maxSpeedX, maxSpeedY);
    SetOriginAnimatedSprite(32,38);

}

void Player::Update(sf::Vector2f velocity, sf::Time elapsedTime, Map *mapa) {
    /**Hay que normalizar la velocidad**/
    sf::Vector2f nVelocity = Util::Normalize(velocity);
    SetSpeed(nVelocity * Player::getVelocidad());
    PhysicsState::Update(elapsedTime, mapa);
}

void Player::Draw() {
    GetSprite().setPosition(GetPosition().x,GetPosition().y);
    Motor2D::Instance()->draw(GetSprite());
}

void Player::DrawWithInterpolation( float interpolation) {
    Render::DrawAnimation(GetPreviousPosition(), GetPosition(), interpolation);
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
PhysicsState* Player::getPhysics() {
    return &physicsState;
}