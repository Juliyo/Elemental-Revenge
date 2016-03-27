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
#include "Player.hpp"
#include "Enemigo.hpp"
#include <SFML/Window.hpp>

class State {
public:
    State();
    State(const State& orig);
    virtual ~State();
    
    bool             EstadoActivo=false;

};

#endif /* STATE_HPP */

