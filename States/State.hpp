/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.hpp
 * Author: joselu
 *
 * Created on 26 de marzo de 2016, 19:49
 */

#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Entities/Enemigo.hpp"
#include <SFML/Window.hpp>

namespace States{
	enum ID{
            InGame,
            Menu,
            Carga,
            Transition
	};
}

class State {
public:
    virtual void HandleEvents(sf::Event &event) = 0;
    virtual void Update(sf::Time timeElapsed) = 0;
    virtual void Render(float interpolation, sf::Time elapsedTime) = 0;

   // virtual void Clean() = 0;
    virtual void Inicializar() = 0;


    Motor2D *motor;

    States::ID id;

};

#endif /* STATE_HPP */

