/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.cpp
 * Author: kike
 * 
 * Created on 25 de abril de 2016, 13:09
 */

#include "Nodo.hpp"

Nodo::Nodo(Nodo *Npadre,Nodo *Nfinal,sf::Vector2i Nposicion,float costo) {
    nodoPadre=Npadre;
    nodoFinal=Nfinal;
    posicion=Nposicion;
    costoG=costo;
    if(nodoFinal!=NULL){
        costoTotal=costoG+calcularCosto();
    } 
}

Nodo::Nodo(const Nodo& orig) {
}

Nodo::~Nodo() {
}

float Nodo::calcularCosto() {
    return abs(posicion.x-nodoFinal->posicion.x)+abs(posicion.y-nodoFinal->posicion.y);
}