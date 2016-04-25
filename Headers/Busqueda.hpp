/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Busqueda.hpp
 * Author: kike
 *
 * Created on 25 de abril de 2016, 13:10
 */

#ifndef BUSQUEDA_HPP
#define BUSQUEDA_HPP
#include <iostream>
#include <vector>
#include "Nodo.hpp"

class Busqueda {
public:
    Busqueda();
    Busqueda(const Busqueda& orig);
    virtual ~Busqueda();
    void adicionarNodoAListaAbierta(Nodo nodo);
    
public std::vector<sf::Vector2i> encontrarCamino(sf::Vector2i posTileIni,sf::Vector2i posTileFinal){
    
}
    
public std::vector<Nodo> encontrarAdyacentes(Nodo nodoActual, Nodo nodoFinal){
    
    std::vector<Nodo> nodosAdyacentes = new std::vector<Nodo>;
    
    int X = nodoActual.posicion.x;
    int Y = nodoActual.posicion.y;
    
    bool topLeft =true;
    bool topRight = true;
    bool botLeft=true;
    bool botRight=true;
    
    
    
    
    //IZQUIERDA
    
}

    int costoDer=10;
    int costoDiag=15;
    
    std::vector<Nodo> *listaAbierta=new std::vector<Nodo>;
    std::vector<sf::Vector2i> *listaCerrada=new std::vector<sf::Vector2i>;
    
private:

};

#endif /* BUSQUEDA_HPP */

