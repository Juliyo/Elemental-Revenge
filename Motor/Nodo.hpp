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
#include "SFML/System.hpp"
#include <vector>
class Nodo {
public:
    Nodo();
    Nodo(const Nodo& orig);

    Nodo(Nodo *nodoPadre, Nodo *nodoFinal, sf::Vector2f pos, float costo) {
        
        NodoPadre=new Nodo();
        NodoFinal=new Nodo();
                
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
        //if (colision) escolision=true;
    }

    virtual ~Nodo();
    Nodo devuelveNodo(){
        return *this;
    }
    
    Nodo *NodoPadre;
    Nodo *NodoFinal;
    float costoTotal;
    float costoG;
    bool Cerrado = false;
    int casillaX;
    int casillaY;
    sf::Vector2f posicion;
    bool escolision=false;
    std::vector<Nodo*>  *nodosAbiertos;

    float Calcularcosto() {
        return abs(casillaX - NodoFinal->casillaX) + abs(casillaY - NodoFinal->casillaY);
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
 void calcularListaAbiertos(){
       nodosAbiertos = new std::vector<Nodo*>();
       nodosAbiertos->reserve(8);
    
//se le pasa solo el costoG ya que es el costo que vas acumulando de los movimientos y en cada nodo
       //se calcularia su costoTotal con el CostoG y la distancia hasta el nodo final
        nodosAbiertos->push_back(new Nodo(this,NodoFinal,sf::Vector2f(posicion.x-24,posicion.y-24),this->costoG+10));//(i-1,j-1) arri-izq
        nodosAbiertos->push_back(new Nodo(this,NodoFinal,sf::Vector2f(posicion.x,posicion.y-24),this->costoG+10));//(i,j-1) arriba
        nodosAbiertos->push_back(new Nodo(this,NodoFinal,sf::Vector2f(posicion.x+24,posicion.y-24),this->costoG+10));//(i+1,j-1) arriba-der
        nodosAbiertos->push_back(new Nodo(this,NodoFinal,sf::Vector2f(posicion.x-24,posicion.y),this->costoG+10));//(i-1,j) izquierda
        nodosAbiertos->push_back(new Nodo(this,NodoFinal,sf::Vector2f(posicion.x+24,posicion.y),this->costoG+10));//(i+1,j) derecha
        nodosAbiertos->push_back(new Nodo(this,NodoFinal,sf::Vector2f(posicion.x-24,posicion.y+24),this->costoG+10));//(i-1,j+1) abajo izquierda
        nodosAbiertos->push_back(new Nodo(this,NodoFinal,sf::Vector2f(posicion.x,posicion.y+24),this->costoG+10));//(i,j+1) abajo
        nodosAbiertos->push_back(new Nodo(this,NodoFinal,sf::Vector2f(posicion.x+24,posicion.y+24),this->costoG+10));//(i+1,j+1) abajo derecha
        

 }
private:



};

#endif /* NODO_HPP */

