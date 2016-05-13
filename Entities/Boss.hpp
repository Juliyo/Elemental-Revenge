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
#include "Hud.hpp"
#include "../Headers/AtaqueBossA.hpp"
#include "../Headers/AtaqueBossB.hpp"
#include "../Headers/AtaqueBossC.hpp"
#include "../Headers/AtaqueBossD.hpp"

#include "../Motor/Collisionable.hpp"

#include "../Motor/Motor2D.hpp"


class Boss : public Enemigo, public Collisionable {
public:
    Boss();
    virtual ~Boss();

    void Inicializar(float posX, float posY, float speedX = 0.f, float speedY = 0.f, float maxSpeedX = 1000.f, float maxSpeedY = 1000.f);
    void Update(const sf::Time elapsedTime);

    void CreateBody() override;
    std::string getClassName() override;
    
    void Spawn();
    
    void updateAtaqueBossA(bool disparado, sf::Time elapsedTime,float x4,float y4);
    void updateAtaqueBossB(bool disparado, sf::Time elapsedTime,float x4,float y4);
    void updateAtaqueBossC(bool disparado, sf::Time elapsedTime,float x4,float y4);
    void updateAtaqueBossD(bool disparado, sf::Time elapsedTime);
   

    void Draw();
    void DrawWithInterpolation(float interpolation);
    
    void UpdateEnemyAnimation(int x, int y);
    void PlayAnimation(Animation *animation);
    void UpdateAnimation(sf::Time elapsedTime);
    void StopAnimation();
    
    void renderAtaqueA(sf::Time elapsedTime, float interpolation);
    void renderAtaqueB(sf::Time elapsedTime, float interpolation);
    void renderAtaqueC(sf::Time elapsedTime, float interpolation);
    void renderAtaqueD(sf::Time elapsedTime, float interpolation);
    
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
    float CdDisparo = 1.5f;
    float CdDisparoRayo = 2.35f;
    float CdDisparoEspiral = 10.0f;
    
    int rotacion[30];
    int rotacion2[30];
    int rotacion3[30];

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
    std::vector<AtaqueBossD*> *circuloFuego;
    Reloj ataqueD;
    float cdAtaqueD = 8.f;
    
    Animation **currentAnimation;
    Animation *walkingAnimationRight;
    Animation *walkingAnimationLeft;
    Animation *animationMuerte;
    
    
    void RestarVida(int a);
    void CambiarVectorVelocidad();
    
    //Variables colisiones
    Reloj *damaged;
    
    
    Hud *hud;
private:
    
};

#endif /* MELEE_HPP */

