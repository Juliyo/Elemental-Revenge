/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transition.hpp
 * Author: joselu
 *
 * Created on 26 de marzo de 2016, 19:50
 */

#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include "State.hpp"

class Transition:public State {
public:
    Transition();
    Transition(const Transition& orig);
    virtual ~Transition();
    
    void Update(sf::Time elapsedTime);
private:

};

#endif /* TRANSITION_HPP */

