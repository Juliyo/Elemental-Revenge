/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.hpp
 * Author: kike
 *
 * Created on 25 de abril de 2016, 13:09
 */

#ifndef NODO_HPP
#define NODO_HPP
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Nodo {
public:
    Nodo(Nodo *Npadre,Nodo *Nfinal,sf::Vector2i Nposicion,float costo);
    float calcularCosto();
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    Nodo *nodoPadre;
    Nodo *nodoFinal;
    sf::Vector2i posicion;
    float costoTotal;
    float costoG;
private:

};

#endif /* NODO_HPP */

