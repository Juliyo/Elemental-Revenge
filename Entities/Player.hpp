/* 
 * File:   Player.h
 * Author: ElementalR
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Animation.hpp"
#include "Hud.hpp"
#include "hRayAdvanced.hpp"
#include "hRayBasic.hpp"
#include "hFireBasic.hpp"
#include "hFireAdvanced.hpp"
#include "hWaterBasic.hpp"
#include "hWaterAdvanced.hpp"
#include "Heal.hpp"
#include "Flash.hpp"
#include "Entity.hpp"
#include "../Motor/Collisionable.hpp"

class Player : public Entity, public Collisionable {
public:
    Player();
    virtual ~Player();
    std::string getClassName() override;
    void CreateBody() override;



    void Inicializar(float posX, float posY, float speedX = 0.f, float speedY = 0.f, float maxSpeedX = 1000.f, float maxSpeedY = 1000.f);
    void Update(const sf::Time elapsedTime);

    void Draw();
    void DrawWithInterpolation(float interpolation);

    void HandleMapCollisions(const sf::Time& elapsedTime);

    PhysicsState* getPhysics();
    void UpdatePlayerAnimation();
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


    bool updateRayo(bool isShooting, bool RayoAvanzadoCast, float cdRayoBasicoPausa,float cdRayoAvanzadoCast);
    void updateFuego(bool fuegoBasicCast, bool fuegoAdvancedCast, sf::Time elapsedTime, float cdFuegoAvanzadoPausa, float cdFuegoBasicoPausa);
    void updateAgua(bool aguaBasicCast, bool aguaAdvancedCast, sf::Time elapsedTime, float cdAguaAvanzadoPausa, float cdAguaBasicoPausa);
    void updateFlash(float cdFlashPausa);
    void renderRayo(sf::Time elapsedTime, float interpolation);
    void renderFuego(sf::Time elapsedTime, float interpolation);
    void renderAgua(sf::Time elapsedTime, float interpolation);
    void renderHeal(sf::Time elapsedTime, float interpolation);
    void renderFlash(sf::Time elapsedTime, float interpolation);

    void Colocar(sf::Vector2f NuevaPosicion);

    void SetVida(int vida) {
        this->vida = vida;
    }

    hRayBasic *hRayoBasico;
    hRayAdvanced *hRayoAvanzado;

    //Fuego
    hFireBasic *hFuegoBasico;
    std::vector<sf::CircleShape*> *shapesFuego; 
    hFireAdvanced *hFuegoAvanzado;
    
    
    int contFuego = 0;
    Reloj clockCDFire; //Variable de clase para el cd
    float CDFire = 0.35f;
    Reloj castFire; //Variable de clase para el casteo
    Reloj castFire2; //Variable de clase para el casteo
    bool primercastFuego; //Variable de clase para el primer casteo

    ///Aguaa
    hWaterBasic *hAguaBasico;
    hWaterAdvanced *hAguaAvanzado;
    Animation **currentAnimation;
    Animation *walkingAnimationDown;
    Animation *walkingAnimationLeft;
    Animation *walkingAnimationRight;
    Animation *walkingAnimationUp;

    //Fuego
    Animation *castingAnimationUpFuego;
    Animation *castingAnimationDownFuego;
    Animation *castingAnimationRightFuego;
    Animation *castingAnimationLeftFuego;
    //Rayo
    Animation *castingAnimationUpRayo;
    Animation *castingAnimationDownRayo;
    Animation *castingAnimationRightRayo;
    Animation *castingAnimationLeftRayo;
    //Agua
    Animation *castingAnimationUpAgua;
    Animation *castingAnimationDownAgua;
    Animation *castingAnimationRightAgua;
    Animation *castingAnimationLeftAgua;

    //Animaciones fuego1
    Animation *fuegoAnimationDown;
    Animation *fuegoAnimationLeft;
    Animation *fuegoAnimationRight;
    Animation *fuegoAnimationUp;
    //Animaciones fuego2
    Animation *fuego2AnimationDown;
    Animation *fuego2AnimationLeft;
    Animation *fuego2AnimationRight;
    Animation *fuego2AnimationUp;
    //Animaciones heal
    Animation *healingAnimationDown;
    Animation *healingAnimationLeft;
    Animation *healingAnimationRight;
    Animation *healingAnimationUp;
    
    Animation *animationMuerte;
    Animation *Muerto;

    Reloj relojMuriendo;
    
    Hud *hud;
    int cuadrante;

    //Eventos del player
    bool isMovingUp;
    bool isMovingDown;
    bool isMovingRight;
    bool isMovingLeft;
    bool cantMove = false;

    //heal
    Heal *hHeal;
    int getVida();
    int restaVida(int a);
    void heal();
    //flash
    Flash *flash;
    Flash *flash2;
    bool isFlashing = false;
    bool aux;
    
    Reloj invulnerable;
    Reloj damaged;

private:

    sf::Texture texturaPlayer;
    float velocity = 250.f;
    int vida = 15;
    
    
    
};

#endif /* PLAYER_H */