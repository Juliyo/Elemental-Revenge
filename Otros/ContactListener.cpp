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
ContactListener::ContactListener() {
}

ContactListener::ContactListener(const ContactListener& orig) {
}

ContactListener::~ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {

    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData){
        static_cast<Entity*> (bodyUserData)->Collide();
    }
       
}

void ContactListener::EndContact(b2Contact* contact) {
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData){
        static_cast<Entity*> (bodyUserData)->EndCollide();
    }
}
