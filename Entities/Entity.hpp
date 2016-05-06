/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Entity.hpp
 * Author: julio
 *
 * Created on 22 de abril de 2016, 16:06
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Headers/PhysicsState.hpp"
#include "../Headers/Render.hpp"
#include <string.h>

/*enum _entityCategory {
    BOUNDARY = 0x0001,
    PLAYER = 0x0002,
    ENEMIGO = 0x0004,
    HECHIZO = 0x0008
};*/
namespace Estado {
    enum ID {
        Vivo,
        Muerto,
        Muriendo
    };
}

class Entity : public PhysicsState, public Render {
public:
    Entity();
    Entity(const Entity& orig);
    virtual ~Entity();
    //virtual void Update(const sf::Time elapsedTime) = 0;
    virtual std::string getClassName() = 0;
    
    Estado::ID GetEstado(){
        return estado;
    }
    void SetEstado(Estado::ID est){
        estado = est;
    }
    
    
private:
    //Todas las entitys empiezan en este estado
    Estado::ID estado;
};

#endif /* ENTITY_HPP */

