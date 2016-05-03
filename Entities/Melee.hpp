/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Melee.hpp
 * Author: Julio
 *
 * Created on 26 de abril de 2016, 11:19
 */

#ifndef MELEE_HPP
#define MELEE_HPP

#include "Enemigo.hpp"
#include "../Motor/Collisionable.hpp"
#include "../Headers/hFireBasic.hpp"
#include "Animation.hpp"


namespace Tipo {

    enum ID {
        Rata = 0,
        Ninja = 1,
    };
}

class Melee : public Enemigo, public Collisionable {
public:
    Melee();
    virtual ~Melee();

    void Inicializar(float posX, float posY, Tipo::ID tipo,float speedX = 0.f, float speedY = 0.f, float maxSpeedX = 1000.f, float maxSpeedY = 1000.f);
    void Update(const sf::Time elapsedTime, float x1, float x2, float multiplicador);

    
    bool HandleMapCollisions(const sf::Time& elapsedTime);

    void Draw();
    void DrawWithInterpolation(float interpolation);

    void FindPlayer(sf::Time elapsedTime);
    
    void UpdateEnemyAnimation(int x, int y);
    void PlayAnimation(Animation *animation);
    void UpdateAnimation(sf::Time elapsedTime);
    void StopAnimation();

    bool empujado;
    bool empujado2;
    Reloj tiempoempujado;
    int cuadrante = 2;
    Animation **currentAnimation;
    Animation *walkingAnimationDown;
    Animation *walkingAnimationLeft;
    Animation *walkingAnimationRight;
    Animation *walkingAnimationUp;
    
    
        //Animaciones fuego1
    Animation *fuegoAnimationDown;
    Animation *fuegoAnimationLeft;
    Animation *fuegoAnimationRight;
    Animation *fuegoAnimationUp;
    
    void updateFuego(bool fuegoBasicCast, sf::Time elapsedTime);
    void renderFuego(sf::Time elapsedTime, float interpolation);

    int contFuego = 0;
    Reloj clockCDFire; //Variable de clase para el cd
    float CDFire = 0.35f;
    Reloj castFire; //Variable de clase para el casteo
    Reloj castFire2; //Variable de clase para el casteo
    bool primercastFuego; //Variable de clase para el primer casteo

    
    hFireBasic *hFuegoBasico;

    
private:
    Tipo::ID m_tipo;
    sf::Texture texturaEnemigo;
};

#endif /* MELEE_HPP */

