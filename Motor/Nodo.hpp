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

    Nodo(Nodo *nodoPadre, Nodo *nodoFinal, sf::Vector2f pos, float costo);

    virtual ~Nodo();
    Nodo devuelveNodo();
    
    Nodo *NodoPadre;
    Nodo *NodoFinal;
    float costoTotal;
    float costoG;
    bool Cerrado = false;
    int casillaX;
    int casillaY;
    sf::Vector2f posicion;
    bool escolision=false;
    bool nulo=true;
    

    float Calcularcosto();

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f pos);
    bool esIgual(Nodo *nodo);
    sf::Vector2i GetCasilla() const{
        return sf::Vector2i(casillaX,casillaY);
    }
   friend bool operator== ( const Nodo &n1, const Nodo &n2);
   friend bool operator!= ( const Nodo &n1, const Nodo &n2);




 //metodo para borrar
//  for (std::vector< int >::iterator it = v.begin() ; it != v.end(); ++it)
//   {
//     delete (*it);
//   } 

private:



};

#endif /* NODO_HPP */

