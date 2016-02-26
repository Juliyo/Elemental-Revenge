/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorldState.hpp
 * Author: Julio
 *
 * Created on 26 de febrero de 2016, 12:30
 */

#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

class WorldState {
public:
    WorldState();
    WorldState(const WorldState& orig);
    virtual ~WorldState();
    float jugadorX,jugadorY=0;
private:
    
};

#endif /* WORLDSTATE_HPP */

