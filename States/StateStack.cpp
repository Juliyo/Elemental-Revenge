/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateStack.cpp
 * Author: julio
 * 
 * Created on 21 de abril de 2016, 0:34
 */

#include "StateStack.hpp"

StateStack* StateStack::instance = 0;

StateStack* StateStack::Instance() {
	if(instance == 0){
            instance = new StateStack();
        }
        
	return instance;
}

StateStack::StateStack() {
    mapStates = new std::map<States::ID, State*>();
    currentState = States::ID::InGame;
    
    CreateStates();
    //Solo inicializamos el estado menu
    GetCurrentState()->Inicializar();
}

StateStack::StateStack(const StateStack& orig) {
}

StateStack::~StateStack() {
}

void StateStack::CreateStates() {
    mapStates->insert(std::make_pair(States::ID::Menu , StateFactory::CreateState(States::ID::Menu)));
    mapStates->insert(std::make_pair(States::ID::InGame , StateFactory::CreateState(States::ID::InGame)));
    mapStates->insert(std::make_pair(States::ID::Carga , StateFactory::CreateState(States::ID::Carga)));
    mapStates->insert(std::make_pair(States::ID::Transition , StateFactory::CreateState(States::ID::Transition)));
}

State* StateStack::GetCurrentState() const {
    std::map<States::ID, State*>::iterator it = mapStates->find(currentState);
    return it->second;
}

State* StateStack::GetState(States::ID id) const {
    std::map<States::ID, State*>::iterator it = mapStates->find(id);
    return it->second;
}

void StateStack::SetCurrentState(States::ID id) {
    if(id != currentState)
    {
        States::ID aux = currentState;

        currentState = id;
        if(id==States::ID::InGame){
            //Deberiamos limpiar el mapa
        }
        
    }
}

