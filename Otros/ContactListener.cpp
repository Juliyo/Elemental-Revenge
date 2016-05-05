/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContactListener.cpp
 * Author: tonir
 * 
 * Created on 29 de abril de 2016, 14:42
 */

#include "ContactListener.hpp"
#include "../Otros/Dummy.hpp"
#include "../Entities/Player.hpp"
ContactListener::ContactListener() {
}

ContactListener::ContactListener(const ContactListener& orig) {
}

ContactListener::~ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {

    
       
}

void ContactListener::EndContact(b2Contact* contact) {
    
}

bool ContactListener::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) {
    std::cout<<static_cast<Entity*> (fixtureA->GetBody()->GetUserData())->getClassName()<<std::endl;
    std::string claseA = "";
    std::string claseB = "";
    if(fixtureA->GetBody()->GetUserData()){
        claseA = static_cast<Entity*> (fixtureA->GetBody()->GetUserData())->getClassName();
    }
    if(fixtureB->GetBody()->GetUserData()){
        claseB = static_cast<Entity*> (fixtureB->GetBody()->GetUserData())->getClassName();
    }

    if(claseA == "Player"){
        if(claseB == ""){
            return true;
        }else if(claseB == "Melee"){
            Player *p = static_cast<Player*> (fixtureA->GetBody()->GetUserData());
            p->restaVida(1);
            return true;
        }else if(claseB == "hFireBasic"){
            return false;
        }
    }
    if(claseA == "hFireBasic"){
        if(claseB == "Player"){
            return false;
        }
    }
    if(claseA == "Melee"){
        if(claseB == "Player"){
           //Player *p = static_cast<Player*> (fixtureA->GetBody()->GetUserData());
           //p->restaVida(1);
           return true;
        }
    }

    
    return true;
}
