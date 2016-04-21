/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateFactory.cpp
 * Author: julio
 * 
 * Created on 21 de abril de 2016, 0:31
 */

#include "StateFactory.hpp"
#include "InGame.hpp"
#include "Menu.hpp"

State* StateFactory::CreateState(States::ID id){
    
    if(id == States::ID::InGame){
        return new InGame();
    }else if(id == States::ID::Menu){
        return new Menu();
    }
        
    
   
}