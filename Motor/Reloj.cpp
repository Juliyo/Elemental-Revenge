/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Reloj.cpp
 * Author: Usuario
 * 
 * Created on 5 de abril de 2016, 14:19
 */

#include "Reloj.hpp"
#include "SFML/System/Clock.hpp"

Reloj::Reloj() {
}

Reloj::Reloj(const Reloj& orig) {
}

Reloj::~Reloj() {
}

Reloj::~Reloj() {
}


float Reloj::getTiempo() {
    return reloj->getElapsedTime().asSeconds();
}
void Reloj::reset() {
    reloj->restart();
}
