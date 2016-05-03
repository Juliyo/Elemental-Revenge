/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dummy.cpp
 * Author: tonir
 * 
 * Created on 29 de abril de 2016, 13:31
 */

#include "Dummy.hpp"
#include "tmxHelper.hpp"

Dummy::Dummy(): Collisionable((Entity*)this) {
    this->CreateDynamicBody();
    SetPosition(0,0);
    body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(0,0)),0);
    body->SetUserData(this);
    
}


Dummy::~Dummy() {
}

void Dummy::EndCollide() {

}

void Dummy::Collide() {

}

void Dummy::collide() {
    //touch = true;
}

bool Dummy::getCollision(sf::Vector2f &p){
    bool a = body->GetFixtureList()->TestPoint(tmx::SfToBoxVec(p));
    return a;
}

