/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Boss.hpp
 * Author: Julio
 *
 * Created on 26 de abril de 2016, 11:19
 */

#ifndef BOSS_HPP
#define BOSS_HPP

#include "Enemigo.hpp"

#include "../Headers/AtaqueBossA.hpp"
#include "../Headers/AtaqueBossB.hpp"
#include "../Headers/AtaqueBossC.hpp"

#include "../Motor/Collisionable.hpp"

#include "../Motor/Motor2D.hpp"


class Boss : public Enemigo, public Collisionable {
public:
    Boss();
    virtual ~Boss();

    void Inicializar(float posX, float posY, float speedX = 0.f, float speedY = 0.f, float maxSpeedX = 1000.f, float maxSpeedY = 1000.f);
    void Update(const sf::Time elapsedTime, float x1, float x2, float multiplicador);

    
    void updateAtaqueBossA(bool disparado, sf::Time elapsedTime,float x4,float y4);
    void updateAtaqueBossB(bool disparado, sf::Time elapsedTime,float x4,float y4);
    void updateAtaqueBossC(bool disparado, sf::Time elapsedTime,float x4,float y4);
    
    bool HandleMapCollisions(const sf::Time& elapsedTime);

    void Draw();
    void DrawWithInterpolation(float interpolation);

    void FindPlayer(sf::Time elapsedTime);
    
    void UpdateEnemyAnimation(int x, int y);
    void PlayAnimation(Animation *animation);
    void UpdateAnimation(sf::Time elapsedTime);
    void StopAnimation();
    
    void renderAtaqueA(sf::Time elapsedTime, float interpolation);
    void renderAtaqueB(sf::Time elapsedTime, float interpolation);
    void renderAtaqueC(sf::Time elapsedTime, float interpolation);
    
    bool empujado;
    bool empujado2;
    Reloj tiempoempujado;
    int cuadrante = 2;
    
    int numDisparo=0;
        Motor2D *motor;

    Reloj castDisparo; //Variable de clase para el casteoum
    Reloj castDisparoRayo; //Variable de clase para el casteo
    Reloj castDisparoEspiral; //Variable de clase para el casteo

    Reloj clockCdDisparo; 
    Reloj clockCdDisparoRayo; 
    Reloj clockCdDisparoEspiral; 
    float CdDisparo = 2.5f;
    float CdDisparoRayo = 2.9f;
    float CdDisparoEspiral = 10.0f;
    
    int rotacion[50];
    int rotacion2[50];
    int rotacion3[50];

    bool primercastDisparo; //Variable de clase para el primer casteo
    bool primercastDisparoRayo; //Variable de clase para el primer casteo
    bool primercastDisparoEspiral; //Variable de clase para el primer casteo
    int setOriginEspiral=0;
    int setOriginEspiral2=0;
    int setOriginEspiral3=0;
    
    int numBolasEspiral=0;
    int numBolasEspiral2=0;
    int numBolasEspiral3=0;
    
    
    std::vector<AtaqueBossA*> *disparo;
    //AtaqueBossA *disparo;
    AtaqueBossB *rayo;
    std::vector<AtaqueBossC*> *espiral;
    
    Animation **currentAnimation;
    Animation *walkingAnimationDown;
    Animation *walkingAnimationLeft;
    Animation *walkingAnimationRight;
    Animation *walkingAnimationUp;
private:

    sf::Texture texturaEnemigo;
};

#endif /* MELEE_HPP */

