/* 
 * File:   Player.h
 * Author: linuxero
 *
 * Created on March 5, 2014, 7:43 AM
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Animation.hpp"
#include "Hud.hpp"
#include "hRayAdvanced.hpp"
#include "hRayBasic.hpp"
#include "Entity.hpp"
#include "../Motor/Collisionable.hpp"

class Player : public Entity, public Collisionable {
public:
    Player();
    virtual ~Player();

    void Inicializar(float posX, float posY, float speedX = 0.f, float speedY = 0.f, float maxSpeedX = 1000.f, float maxSpeedY = 1000.f);
    void Update(const sf::Time elapsedTime);

    void Draw();
    void DrawWithInterpolation(float interpolation);
    
    
    PhysicsState* getPhysics();
    void UpdatePlayerAnimation(int x, int y);
    sf::Vector2f getPosition();

    Animation** getAnimation() {
        return currentAnimation;
    };
    
    float GetVelocity() const {
        return velocity;
    }

    void SetVelocity(float velocity) {
        this->velocity = velocity;
    }

    int GetVida() const {
        return vida;
    }

    void SetVida(int vida) {
        this->vida = vida;
    }

    hRayBasic *hRayoBasico;
    hRayAdvanced *hRayoAvanzado;

    Animation **currentAnimation;
    Animation *walkingAnimationDown;
    Animation *walkingAnimationLeft;
    Animation *walkingAnimationRight;
    Animation *walkingAnimationUp;
    Animation *castingAnimationUp;
    Animation *castingAnimationDown;
    Animation *castingAnimationRight;
    Animation *castingAnimationLeft;
    Hud *hud;
    int cuadrante;
    
    //Eventos del player
    bool isMovingUp;
    bool isMovingDown;
    bool isMovingRight;
    bool isMovingLeft;
    
    
private:
    
    sf::Texture texturaPlayer;
    
    float velocity = 200.f;
    int vida = 15;

    
};

#endif /* PLAYER_H */

