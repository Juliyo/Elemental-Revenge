/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.hpp
 * Author: Usuario
 *
 * Created on 29 de abril de 2016, 13:14
 */

#ifndef NODO_HPP
#define NODO_HPP
#include <iostream>

class Nodo {
public:
    Nodo();
    Nodo(const Nodo& orig);

    Nodo(Nodo nodoPadre, Nodo nodoFinal, sf::Vector2f pos, float costo) {
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
    }

    virtual ~Nodo();

    Nodo NodoPadre;
    Nodo NodoFinal;
    float costoTotal;
    float costoG;
    bool Cerrado = false;
    int casillaX;
    int casillaY;
    sf::Vector2f posicion;

    float Calcularcosto() {
        return abs(casillaX - NodoFinal.casillaX) + abs(casillaY - NodoFinal.casillaY);
    }

    sf::Vector2f getPosition() {
        return posicion;
    }

    void setPosition(sf::Vector2f pos) {
        posicion = pos;
    }
 bool esIgual(Nodo nodo){
 return (posicion == nodo.posicion);
}
private:



};

#endif /* NODO_HPP */

