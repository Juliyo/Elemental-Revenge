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
    healingAnimationDown = new Animation();
    healingAnimationLeft = new Animation();
    healingAnimationRight = new Animation();
    healingAnimationUp = new Animation();
    
    hud = new Hud();
    hHeal = new Heal();

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
    
    healingAnimationDown->setSpriteSheet(texturaPlayer);
    healingAnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(0, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(64, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(128, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(192, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(256, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(320, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));


    healingAnimationLeft->setSpriteSheet(texturaPlayer);
    healingAnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(0, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(64, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(128, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(192, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(256, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(320, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));

    healingAnimationRight->setSpriteSheet(texturaPlayer);
    healingAnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(0, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(64, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(128, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(192, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(256, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(320, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));


    healingAnimationUp->setSpriteSheet(texturaPlayer);
    healingAnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(0, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(64, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(128, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(192, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(256, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(320, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));

    currentAnimation = &walkingAnimationDown;
    InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    SetPosition(posX, posY);
    SetSpeed(speedX, speedY);
    SetMaxSpeed(maxSpeedX, maxSpeedY);

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

    if (invulnerable.getElapsedTime().asSeconds() > 3) {
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

