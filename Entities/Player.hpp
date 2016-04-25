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
    Player(BoundingBox *rectPlayer);
   // Player(const Player& orig);
    virtual ~Player();

    void Inicializar(float posX, float posY, float speedX = 0.f, float speedY = 0.f, float maxSpeedX = 1000.f, float maxSpeedY = 1000.f);
    void Update(const sf::Time elapsedTime);

    void Draw();
    void DrawWithInterpolation(float interpolation);
    float getVelocidad();
    PhysicsState* getPhysics();
    void UpdatePlayerAnimation(int x, int y);
    sf::Vector2f getPosition();

    Animation** getAnimation() {
        return currentAnimation;
    };

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
    
    void OnColision(std::vector<Colision::Type>);


    
    bool isMovingUp;
    bool isMovingDown;
    bool isMovingRight;
    bool isMovingLeft;

    std::vector<sf::RectangleShape> shapes;
    sf::RectangleShape playerShape;
    std::vector<tmx::MapObject*> objetosCercanos;
private:
    
    void HandleMapCollisions(const sf::Time& elapsedTime);
    sf::Texture texturaPlayer;
    
    float velocity = 150.f;
    int vida = 15;

    
};

#endif /* PLAYER_H */

