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
    fuegoAnimationDown = new Animation();
    fuegoAnimationLeft = new Animation();
    fuegoAnimationRight = new Animation();
    fuegoAnimationUp = new Animation();
    fuego2AnimationDown = new Animation();
    fuego2AnimationLeft = new Animation();
    fuego2AnimationRight = new Animation();
    fuego2AnimationUp = new Animation();
    
    hud = new Hud();
    hHeal = new Heal();
    hFuegoAvanzado= new hFireAdvanced();
    hFuegoBasico = new hFireBasic[50];

    if (!texturaPlayer.loadFromFile("resources/Textures/player.png")) {
        std::cout << "Error cargando la textura: " << "resources/Textures/player.png" << std::endl;
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
    
   
    fuegoAnimationUp->setSpriteSheet(texturaPlayer);
    //fuegoAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(0, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(64, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(128, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(192, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(256, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
  
  
    
    
    fuegoAnimationDown->setSpriteSheet(texturaPlayer);
    //fuegoAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(0, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(64, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(128, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(192, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(256, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
 
    
    
    fuegoAnimationRight->setSpriteSheet(texturaPlayer);
    //fuegoAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(0, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(64, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(128, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(192, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(256, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
  
    
    
    fuegoAnimationLeft->setSpriteSheet(texturaPlayer);
    //fuegoAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(0, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(64, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(128, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(192, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(256, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));

    fuego2AnimationDown->setSpriteSheet(texturaPlayer);
    fuego2AnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(0, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(64, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(128, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(192, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(256, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(320, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));


    fuego2AnimationLeft->setSpriteSheet(texturaPlayer);
    fuego2AnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(0, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(64, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(128, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(192, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(256, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(320, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));

    fuego2AnimationRight->setSpriteSheet(texturaPlayer);
    fuego2AnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(0, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(64, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(128, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(192, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(256, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(320, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));


    fuego2AnimationUp->setSpriteSheet(texturaPlayer);
    fuego2AnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(0, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(64, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(128, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(192, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(256, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(320, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    
    currentAnimation = &walkingAnimationDown;
    InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    SetPosition(posX, posY);
    SetSpeed(speedX, speedY);
    SetMaxSpeed(maxSpeedX, maxSpeedY);
    SetOriginAnimation(32,32);
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

int Player::getVida() {
    return vida;
}

int Player::restaVida(int a) {

    if (invulnerable.getElapsedTime().asSeconds() > 0.5f && (vida-a) >= 0) {
        //std::cout <<"Resto vidas";
        vida -= a;
        hud->updateHud(vida);
        invulnerable.restart();
    }


    return vida;
}

void Player::heal() {
    if (hHeal->cast()) {
        //std::cout <<"Sumo vidas";
        vida += 2;
        if (vida > 15) {
            vida = 15;

        }
        hud->updateHud(vida);
    }
}

