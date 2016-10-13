/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateStack.hpp
 * Author: julio
 *
 * Created on 21 de abril de 2016, 0:34
 */

#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include "State.hpp"
#include "StateFactory.hpp"
#include <map>

class StateStack {
public:
    static StateStack* Instance();
    
    void   CreateStates();
    State* GetState(States::ID id) const;
    State* GetCurrentState() const;
    void   SetCurrentState(States::ID id);
    
    
    States::ID currentState;
    
    StateStack();
    StateStack(const StateStack& orig);
    virtual ~StateStack();
    
private:
    static StateStack* instance;
    std::map<States::ID, State*> *mapStates;
};

#endif /* STATESTACK_HPP */

