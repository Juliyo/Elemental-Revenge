/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Caster.hpp
 * Author: RuCri
 *
 * Created on 8 de mayo de 2016, 13:13
 */

#ifndef CASTER_HPP
#define CASTER_HPP

#include "Enemigo.hpp"

#include "../Headers/DisparoEnemigo.hpp"
#include "../Motor/Collisionable.hpp"

namespace Tipo {

    enum Caster {
        Mago = 0,
        Bandido = 1,
    };
}

class Caster : public Enemigo, public Collisionable {
public:
    Caster();
    virtual ~Caster();
    void Inicializar(float posX, float posY, Tipo::Caster tipo, float speedX = 0.f, float speedY = 0.f, float maxSpeedX = 1000.f, float maxSpeedY = 1000.f);
    void Update(const sf::Time elapsedTime, float x1, float x2, float multiplicador);
    void CreateBody() override;
    std::string getClassName() override;


    void RestarVida(int a);
    void CambiarVectorVelocidad();


    void updateDisparoEnemigo(bool disparado, sf::Time elapsedTime, float x4, float y4);

    bool HandleMapCollisions(const sf::Time& elapsedTime);

    void Draw();
    void DrawWithInterpolation(float interpolation);


    void UpdateEnemyAnimation(int x, int y);
    void PlayAnimation(Animation *animation);
    void UpdateAnimation(sf::Time elapsedTime);
    void StopAnimation();

    bool empujado;
    bool empujado2;
    Reloj tiempoempujado;
    int cuadrante = 2;

    int numDisparo = 0;

    Reloj castDisparo; //Variable de clase para el casteo
    Reloj clockCdDisparo;
    float CdDisparo;

    bool primercastDisparo; //Variable de clase para el primer casteo


    //DisparoEnemigo *disparo;
    std::vector<DisparoEnemigo*> *disparos;

    Animation **currentAnimation;
    Animation *walkingAnimationDown;
    Animation *walkingAnimationLeft;
    Animation *walkingAnimationRight;
    Animation *walkingAnimationUp;

    Animation *animationMuerte;
    std::vector<sf::RectangleShape> shapesDebug;
    sf::Color color;
private:
    Tipo::Caster m_tipo;
    sf::Texture texturaEnemigo;
    Reloj inicio;

};

#endif /* CASTER_HPP */



