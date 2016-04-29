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
class PathFinding {
public:
    PathFinding();
    PathFinding(const PathFinding& orig);
    virtual ~PathFinding();
    
    void encontrarCamino(sf::Vector2f posjugador,sf::Vector2f posenemigo ){
        NodoFinal=new Nodo(NULL,NULL,posjugador,0); 
        NodoInicio= new Nodo(NULL,NodoFinal,posenemigo,0);
        NodoActual=NodoInicio;
        
        
    }
    void calcularAbiertos(Nodo *nodo){
        float posx=nodo->posicion.x;
        float posy=nodo->posicion.x;
            Nodo nodonuevo=new Nodo(nodo,NodoFinal,sf::Vector2f(posx-24,posy-24),nodo->Calcularcosto()+10);
    }
private:
    std::vector<Nodo*>  nodosAbiertos;
    std::vector<Nodo*>  nodosCerrados;
    Nodo *NodoInicio;
    Nodo *NodoFinal;
    Nodo *NodoActual;
    
};

#endif /* PATHFINDING_HPP */

