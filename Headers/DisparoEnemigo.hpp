/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisparoEnemigo.hpp
 * Author: joselu
 *
 * Created on 3 de mayo de 2016, 10:04
 */

#ifndef DISPAROENEMIGO_HPP
#define DISPAROENEMIGO_HPP

#include "SFML/Graphics/CircleShape.hpp"

#include "Render.hpp"
#include "PhysicsState.hpp"
#include "../Motor/Motor2D.hpp"
#include "Hechizo.hpp"
#include "../Motor/Collisionable.hpp"

class DisparoEnemigo : public Hechizo, public Collisionable {
public:
    DisparoEnemigo();
    virtual ~DisparoEnemigo();
    
    Motor2D *motor;

    float angleshot2=0.0f;
    
    void Update2(sf::Vector2f velocity, sf::Time elapsedTime);
    void CreateBody() override;
    std::string getClassName() override;
    
    void Clear();
    void Disparar(sf::Vector2f vector,sf::Vector2f vectorPlayer);
    void RenderDisparo(float interpolation);
    
    Animation **currentAnimation;
    Animation *animationInicio;
    Animation *animationFin;
    
    void Colision(){
        if(GetEstado() == Estado::Vivo){
            //SetPosition(sf::Vector2f(0,0));
            //body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(0,0)),0);
            explosionTiempo->restart();
            currentAnimation = &animationFin;
            Render::SetOriginAnimatedSprite(86, 79);
            Render::SetFrameTime(sf::seconds(0.05));
            Render::SetLooped(false);
            Render::SetScaleAnimation(0.4, 0.4);
            SetEstado(Estado::ID::Muriendo);
        }
    }

    void ComprobarSiMuerto() {
        if (explosionTiempo->getTiempo() > 0.25f) {
            SetEstado(Estado::ID::Muerto);
        }
    }
    
private:
    Reloj *explosionTiempo;
};

#endif /* DISPAROENEMIGO_HPP */

