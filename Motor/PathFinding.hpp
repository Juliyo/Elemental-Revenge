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

    //void encontrarCamino(sf::Vector2f posjugador, sf::Vector2f posenemigo);

    //std::vector<Nodo*> getCamino();

    //void calcularListaAbiertos();

    void adicionarNodoAListaAbierta(Nodo *nodo);

    std::vector<sf::Vector2i>* buscaCamino(sf::Vector2f posenemigo, sf::Vector2f posjugador);

    std::vector<Nodo*>* encontrarNodosAdyacentes(Nodo *nodoActual, Nodo *nodoFinal);
private:
    //std::vector<Nodo> nodosCerrados;
    std::vector<Nodo*> listaAbierta;
    std::vector<sf::Vector2i> listaCerrada;

    template <typename T>
    const bool Contains(std::vector<T>& Vec, const T& Element) {
        if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end())
            return true;

        return false;
    }
    bool BuscarNodoEnListaAbierta(Nodo *nodo){
        for(int i = 0; i < listaAbierta.size();i++){
            if(listaAbierta.at(i)->esIgual(nodo)){
                return true;
                break;
            }
        }
        return false;
    }
    bool buscarCasilla(sf::Vector2i casilla){
       bool encontrado=false;
       for(int i=0;i<listaCerrada.size();i++){
           if(listaCerrada.at(i).x==casilla.x && listaCerrada.at(i).y==casilla.y ){
               encontrado==true;
           }
       }
       return encontrado;
   }
    //Nodo *NodoInicio;
    //Nodo *NodoFinal;
    //Nodo *NodoActual;
    // Nodo *NodoAnterior;
    // Nodo *NodoSiguiente;
    // int siguiente;
    int toTieso = 15;
    int toTorsio = 10;

    //std::vector<Nodo*> nodosAbiertos;

};

#endif /* PATHFINDING_HPP */

