/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.hpp
 * Author: Julio
 *
 * Created on 26 de abril de 2016, 11:16
 */

#ifndef ENEMIGO_HPP
#define ENEMIGO_HPP

#include "Entity.hpp"



class Enemigo : public Entity{
public:    
    Enemigo();
    virtual ~Enemigo();
    
    sf::Vector2f getPosition(){
        return GetPosition();
    };
    sf::Vector2f getSpeed(){
        return GetSpeed();
    };
    Sprite getSprite(){
        return GetSprite();
    };
    
    std::vector<sf::Vector2i>  *camino;
    std::vector<sf::Vector2i>  *posiblecamino;
    int nodoactual=0;
    bool bueno=true;
    bool encola=false;
    float distancia=900;
    
    float GetDamage() const {
        return damage;
    }

    void SetDamage(float damage) {
        this->damage = damage;
    }
    
    float damageTaken;
    int numContactos;
    Reloj invulnerable;
    
protected:
    
    float GetVida() const {
        return vida;
    }

    void SetVida(float vida) {
        this->vida = vida;
    }
    float GetVelocity() const {
        return velocity;
    }

    void SetVelocity(float velocity) {
        this->velocity = velocity;
    }
        
    private:
        float vida;
        float damage;
        float velocity;
};

#endif /* ENEMIGO_HPP */

