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
#include "../States/InGame.hpp"
#include <algorithm>

PathFinding::PathFinding() {
}

PathFinding::PathFinding(const PathFinding& orig) {
}

PathFinding::~PathFinding() {
}


void PathFinding::adicionarNodoAListaAbierta(Nodo *nodo) {
    int indice = 0;
    float costo = nodo->costoTotal;
    while ((listaAbierta.size() > indice) && (costo < listaAbierta.at(indice)->costoTotal)) {
        indice++;
    }
    auto it = listaAbierta.begin();
    //auto it2 = listaAbiertaV.begin();
    listaAbierta.insert(it + indice, nodo);
    //listaAbiertaV.insert(it2 + indice, nodo->GetCasilla());
}

std::vector<Nodo*>* PathFinding::encontrarNodosAdyacentes(Nodo *nodoActual, Nodo *nodoFinal) {
    //printf("Encontrar Nodos Adyaccentes Inicio Metodo \n");
    std::vector<Nodo*> *nodosAdyacentes = new std::vector<Nodo*>();
    int X = nodoActual->GetCasilla().x;
    int Y = nodoActual->GetCasilla().y;

    bool arribaIzquierda = true;
    bool arribaDerecha = true;
    bool abajoIzquierda = true;
    bool abajoDerecha = true;

    InGame *world = InGame::Instance();
    int **colisiones = world->level->map->colisiones;
    int height = world->level->map->_height;
    int width = world->level->map->_width;
    int tileAncho = 24;
    int tileAlto = 24;

    bool condicion = Y >= 0 && X >= 0 && Y < height && X < width;
    //Izquierda
    if (condicion) {
        if (colisiones[Y][X - 1] != 1) {
            nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X - 1), tileAlto * Y), toTieso + nodoActual->costoG));
        } else {
            arribaIzquierda = false;
            abajoDerecha = false;
        }

        //Derecha
        if (colisiones[Y][X + 1] != 1) {
            nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X + 1), tileAlto * Y), toTieso + nodoActual->costoG));
        } else {
            arribaDerecha = false;
            abajoDerecha = false;
        }

        //Arriba
        if (colisiones[Y - 1][X] != 1) {
            nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho*X, tileAlto * (Y - 1)), toTieso + nodoActual->costoG));
        } else {
            arribaIzquierda = false;
            arribaDerecha = false;
        }

        //Abajo
        if (colisiones[Y + 1][X] != 1) {
            nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho*X, tileAlto * (Y + 1)), toTieso + nodoActual->costoG));
        } else {
            arribaDerecha = false;
            abajoDerecha = false;
        }

        //Diagonal
        if (arribaIzquierda && colisiones[Y - 1][X - 1] != 1) {
            nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X - 1), tileAlto * (Y - 1)), toTorsio + nodoActual->costoG));
        }
        if (arribaDerecha && colisiones[Y - 1][X + 1] != 1) {
            nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X + 1), tileAlto * (Y - 1)), toTorsio + nodoActual->costoG));
        }
        if (abajoIzquierda && colisiones[Y + 1][X - 1] != 1) {
            nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X - 1), tileAlto * (Y + 1)), toTorsio + nodoActual->costoG));
        }
        if (abajoDerecha && colisiones[Y + 1][X + 1] != 1) {
            nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X + 1), tileAlto * (Y + 1)), toTorsio + nodoActual->costoG));
        }
    }


    //printf("Encontrar Nodos Adyaccentes Final metodo \n");
    //    for(int j=0;j<nodosAdyacentes->size();j++){
    //        std::cout<<"Nodo "<<j<<" "<<nodosAdyacentes->at(j)->GetCasilla().x<<","<<nodosAdyacentes->at(j)->GetCasilla().y<<"    Meta    "<<nodoFinal->GetCasilla().x<<","<<nodoFinal->GetCasilla().y<<std::endl;
    //    }
    colisiones = nullptr;
    return nodosAdyacentes;
}

std::vector<sf::Vector2i>* PathFinding::buscaCamino(sf::Vector2f posenemigo, sf::Vector2f posjugador) {
    listaAbierta.clear();
    listaCerrada.clear();
    listaActuales.clear();
    std::vector<sf::Vector2i> *mejorCamino = new std::vector<sf::Vector2i>();
    Nodo *nodoFinal = new Nodo(NULL, NULL, posjugador, 0);
    Nodo *nodoInicial = new Nodo(NULL, nodoFinal, posenemigo, 0);

    adicionarNodoAListaAbierta(nodoInicial);

    while (listaAbierta.size() > 0) {
        
        Nodo *nodoActual = listaAbierta.at(listaAbierta.size() - 1);
        listaActuales.push_back(nodoActual);
        if (listaCerrada.size() > 400) {
            nodoFinal = listaAbierta.at(listaAbierta.size() - 1);
        }

        if (nodoActual->esIgual(nodoFinal)) {
            
            // std::cout<<"Tamano de listaabierta: "<<listaAbierta.size()<<std::endl;
            while (nodoActual != NULL) {
                auto it = mejorCamino->begin();
                mejorCamino->insert(it, nodoActual->GetCasilla());
                nodoActual = nodoActual->NodoPadre;
            }
            
            break;
        }
        listaAbierta.pop_back();
        std::vector<Nodo*> *nodosAdyacentes = encontrarNodosAdyacentes(nodoActual, nodoFinal);
        for (int i = 0; i < nodosAdyacentes->size(); i++) {
            //std::cout<<"tam nodos adyaccentes "<<nodosAdyacentes->size()<<"Num de iteracion= "<<i<<std::endl;
            if (std::find(listaCerrada.begin(), listaCerrada.end(), nodosAdyacentes->at(i)->GetCasilla()) == listaCerrada.end()) {

                //if (std::find(listaAbierta.begin(), listaAbierta.end(),nodosAdyacentes->at(i))) { //si esta en la lista entra en el if
                if (BuscarNodoEnListaAbierta(nodosAdyacentes->at(i))) {
                    if (nodosAdyacentes->at(i)->costoG >= nodoActual->costoG) {
                        delete nodosAdyacentes->at(i);
                        continue;
                    }
                }

                adicionarNodoAListaAbierta(nodosAdyacentes->at(i));

            }else{
                delete nodosAdyacentes->at(i);
            }

        }
        
        
        listaCerrada.push_back(nodoActual->GetCasilla());
        //delete nodosAdyacentes;
        //delete nodoActual;

    }

    while (!listaAbierta.empty()) {
        delete listaAbierta.back(), listaAbierta.pop_back();
    }

    while (!listaActuales.empty()) {
        delete listaActuales.back(), listaActuales.pop_back();
    }
    while (!listaCerrada.empty()) {
         listaCerrada.pop_back();
    }
    
    listaCerrada.clear();
    //delete nodoInicial;
    
    //delete nodoFinal;

    return mejorCamino;

}


//para los casters

std::vector<sf::Vector2i>* PathFinding::buscaCamino2(sf::Vector2f posenemigo, sf::Vector2f posjugador) {
    listaAbierta.clear();
    listaCerrada.clear();
    //listaAbiertaV.clear();

    Nodo *nodoFinal = new Nodo(NULL, NULL, posjugador, 0);
    Nodo *nodoInicial = new Nodo(NULL, nodoFinal, posenemigo, 0);

    adicionarNodoAListaAbierta(nodoInicial);

    while (listaAbierta.size() > 0) {

        Nodo *nodoActual = listaAbierta.at(listaAbierta.size() - 1);
        
        if (nodoActual->esIgual(nodoFinal)) {
            std::vector<sf::Vector2i> *mejorCamino = new std::vector<sf::Vector2i>();
            // std::cout<<"Tamano de listaabierta: "<<listaAbierta.size()<<std::endl;
            while (nodoActual != NULL) {
                auto it = mejorCamino->begin();
                mejorCamino->insert(it, nodoActual->GetCasilla());
                // std::cout<<"Camino Final: "<<nodoActual->GetCasilla().x<<","<<nodoActual->GetCasilla().y<<std::endl;
                nodoActual = nodoActual->NodoPadre;

            }

            return mejorCamino;
        }
        //auto it = listaAbierta.end();
        listaAbierta.pop_back();
        //listaAbiertaV.pop_back();
        std::vector<Nodo*> *nodosAdyacentes = encontrarNodosAdyacentes(nodoActual, nodoFinal);
        //esto es un for each

        //listaAbiertaV.clear();
        listaAbierta.clear();
        for (int i = 0; i < nodosAdyacentes->size(); i++) {
            //std::cout<<"tam nodos adyaccentes "<<nodosAdyacentes->size()<<"Num de iteracion= "<<i<<std::endl;
            if (std::find(listaCerrada.begin(), listaCerrada.end(), nodosAdyacentes->at(i)->GetCasilla()) == listaCerrada.end()) {
                adicionarNodoAListaAbierta(nodosAdyacentes->at(i));
            }else{
                delete nodosAdyacentes->at(i);
            }

        }
        delete nodosAdyacentes;
        listaCerrada.push_back(nodoActual->GetCasilla());
    }
    while (!listaAbierta.empty()) {
        delete listaAbierta.back(), listaAbierta.pop_back();
    }

    listaCerrada.clear();
    delete nodoInicial;

    delete nodoFinal;
    
    
    return NULL;

}