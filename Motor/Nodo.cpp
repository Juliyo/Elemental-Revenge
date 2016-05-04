/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.cpp
 * Author: Usuario
 * 
 * Created on 29 de abril de 2016, 13:14
 */

#include "Nodo.hpp"
#include "../States/InGame.hpp"
Nodo::Nodo() {
}

Nodo::Nodo(const Nodo& orig) {
}

Nodo::~Nodo() {
    NodoPadre = NULL;
    NodoFinal = NULL;

}

void Nodo::setPosition(sf::Vector2f pos) {
    posicion = pos;
}

sf::Vector2f Nodo::getPosition() {
    return posicion;
}

bool Nodo::esIgual(Nodo nodo) {
    return (posicion == nodo.posicion);
}

Nodo Nodo::devuelveNodo() {
    return *this;
}

Nodo::Nodo(Nodo* nodoPadre, Nodo* nodoFinal, sf::Vector2f pos, float costo) {

    /* NodoPadre=new Nodo();
     NodoFinal=new Nodo();*/

    NodoPadre = nodoPadre;
    NodoFinal = nodoFinal;
    posicion = pos;
    costoG = costo;
    //calculo de la posicion del nodo en la matriz del mapa 
    casillaX = posicion.x / 24;
    casillaY = posicion.y / 24;
    if (nodoFinal != NULL) {
        costoTotal = costoG + Calcularcosto();
    }

    //TODO sacar si en este nodo hay colision en el mapa, es decir es un arbol, una pared,etc
    //        if (colision){
    //            escolision=true;
    //        }
    InGame *world = InGame::Instance();
    int **colisiones = world->level->map->colisiones;
        int height = world->level->map->_height;
    int width = world->level->map->_width;
    if (casillaY >= 0 && casillaX >=0 && casillaY < height && casillaX < width && colisiones[casillaY][casillaX] != 0) {
        escolision = true;
        std::cout << "Hay colison en la casilla " << casillaX << "," << casillaY << std::endl;
    }
}

float Nodo::Calcularcosto() {
    return abs(casillaX - NodoFinal->casillaX) + abs(casillaY - NodoFinal->casillaY);
}

