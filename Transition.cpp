/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transition.cpp
 * Author: joselu
 * 
 * Created on 26 de marzo de 2016, 19:50
 */

#include "Transition.hpp"

Transition::Transition() {
    //Estado de Ingame
    EstadoActivo = true;
}

Transition::Transition(const Transition& orig) {
}

Transition::~Transition() {
}


void Transition::Update(sf::Time elapsedTime){
    
}
