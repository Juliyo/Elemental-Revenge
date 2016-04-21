/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateFactory.hpp
 * Author: julio
 *
 * Created on 21 de abril de 2016, 0:31
 */

#ifndef STATEFACTORY_HPP
#define STATEFACTORY_HPP
#include "State.hpp"

class StateFactory {
public:
    static State* CreateState(States::ID id);
private:

};

#endif /* STATEFACTORY_HPP */

