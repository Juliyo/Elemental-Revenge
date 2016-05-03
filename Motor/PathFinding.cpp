/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PathFinding.cpp
 * Author: Usuario
 * 
 * Created on 29 de abril de 2016, 14:27
 */

#include "PathFinding.hpp"

PathFinding::PathFinding() {
}

PathFinding::PathFinding(const PathFinding& orig) {
}

PathFinding::~PathFinding() {
}



void PathFinding::calcularListaAbiertos() {

    // nodosAbiertos->reserve(8);

    //se le pasa solo el costoG ya que es el costo que vas acumulando de los movimientos y en cada nodo
    //se calcularia su costoTotal con el CostoG y la distancia hasta el nodo final
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x - 24, NodoActual->posicion.y - 24), NodoActual->costoG + 10)); //(i-1,j-1) arri-izq
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x, NodoActual->posicion.y - 24), NodoActual->costoG + 10)); //(i,j-1) arriba
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x + 24, NodoActual->posicion.y - 24), NodoActual->costoG + 10)); //(i+1,j-1) arriba-der
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x - 24, NodoActual->posicion.y), NodoActual->costoG + 10)); //(i-1,j) izquierda
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x + 24, NodoActual->posicion.y), NodoActual->costoG + 10)); //(i+1,j) derecha
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x - 24, NodoActual->posicion.y + 24), NodoActual->costoG + 10)); //(i-1,j+1) abajo izquierda
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x, NodoActual->posicion.y + 24), NodoActual->costoG + 10)); //(i,j+1) abajo
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x + 24, NodoActual->posicion.y + 24), NodoActual->costoG + 10)); //(i+1,j+1) abajo derecha


}

