/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PathFinding.hpp
 * Author: Usuario
 *
 * Created on 29 de abril de 2016, 14:27
 */

#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include "Nodo.hpp"
#include <iostream>
#include "SFML/System.hpp"
#include <vector>

class PathFinding {
public:
    PathFinding();
    PathFinding(const PathFinding& orig);
    virtual ~PathFinding();

    void encontrarCamino(sf::Vector2f posjugador, sf::Vector2f posenemigo) {
        
        

        
        NodoFinal = new Nodo(NULL, NULL, posjugador, 0.f);
        NodoInicio = new Nodo(NULL, NodoFinal, posenemigo, 0.f);
        NodoActual=new Nodo();
        NodoSiguiente=new Nodo();
        //nodosCerrados = new std::vector<Nodo*>();

        
        NodoActual = NodoInicio;
        float peso;

        //lo primero es vaciar el camino por si ya se habia llamado al metodo
        nodosCerrados.clear();
        NodoActual->calcularListaAbiertos();
        while (NodoActual->posicion != NodoFinal->posicion) {
            for (int i = 0; i < 8; i++) {
                if (NodoActual->nodosAbiertos->at(i)->escolision == false) {
                    
                    if (i == 1) {
                        peso = NodoActual->nodosAbiertos->at(i)->costoTotal;
                        NodoSiguiente = NodoActual->nodosAbiertos->at(i);
                       // NodoSiguiente = NodoActual->nodosAbiertos->at(i)->devuelveNodo();
                    }
                    if (peso > NodoActual->nodosAbiertos->at(i)->costoTotal) {
                        peso = NodoActual->nodosAbiertos->at(i)->costoTotal;
                        //NodoSiguiente = NodoActual->nodosAbiertos->at(i)->devuelveNodo();
                        NodoSiguiente = NodoActual->nodosAbiertos->at(i);
                    }
                }//fin if

            }//fin for
            //sale del for, ya ha recorrido la lista de vecinos del nodo, y se ha quedado con el 
            //mejor nodo en NodoSiguiente, por lo tanto añadimos este a la lista y lo hacemos nuestro nodo Actual.
            //repetir proceso hasta que NodoSiguiente==NodoFinal
            nodosCerrados.push_back(NodoSiguiente);
            //aqui podriamos hacer un delete de todo lo del nodo actual para vaciar memoria ya que con este algoritmo
            //nunca vamos a volver hacia atras y los nodos por los que pasamos ya no los vamos a utilizar mas.
            NodoActual = NodoSiguiente;
            
        }//fin while
//salimos del while y ya tendriamos el camino completo que tenemos que seguir nodo a nodo hasta llegar a la posicion del jugador.
    }
std::vector<Nodo*> getCamino(){
    return nodosCerrados;
}

private:
    std::vector<Nodo*> nodosCerrados;
    Nodo *NodoInicio;
    Nodo *NodoFinal;
    Nodo *NodoActual;
    Nodo *NodoSiguiente;

};

#endif /* PATHFINDING_HPP */

