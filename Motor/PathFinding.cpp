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


/*
 * NUESTRO INTENTO DE PATHFINDING
void PathFinding::calcularListaAbiertos() {

    // nodosAbiertos->reserve(8);

    //se le pasa solo el costoG ya que es el costo que vas acumulando de los movimientos y en cada nodo
    //se calcularia su costoTotal con el CostoG y la distancia hasta el nodo final
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x - 24, NodoActual->posicion.y - 24), NodoActual->costoG + 15)); //(i-1,j-1) arri-izq
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x, NodoActual->posicion.y - 24), NodoActual->costoG + 10)); //(i,j-1) arriba
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x + 24, NodoActual->posicion.y - 24), NodoActual->costoG + 15)); //(i+1,j-1) arriba-der
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x - 24, NodoActual->posicion.y), NodoActual->costoG + 10)); //(i-1,j) izquierda
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x + 24, NodoActual->posicion.y), NodoActual->costoG + 10)); //(i+1,j) derecha
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x - 24, NodoActual->posicion.y + 24), NodoActual->costoG + 15)); //(i-1,j+1) abajo izquierda
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x, NodoActual->posicion.y + 24), NodoActual->costoG + 10)); //(i,j+1) abajo
    nodosAbiertos.push_back(new Nodo(NodoActual, NodoFinal, sf::Vector2f(NodoActual->posicion.x + 24, NodoActual->posicion.y + 24), NodoActual->costoG + 15)); //(i+1,j+1) abajo derecha


}

std::vector<Nodo*> PathFinding::getCamino() {
    return nodosCerrados;
}

void PathFinding::encontrarCamino(sf::Vector2f posjugador, sf::Vector2f posenemigo) {




    NodoFinal = new Nodo(NULL, NULL, posjugador, 0.f);
    NodoInicio = new Nodo(NULL, NodoFinal, posenemigo, 0.f);
    NodoActual = new Nodo();
    NodoAnterior = new Nodo();
    NodoSiguiente = new Nodo();
    //nodosCerrados = new std::vector<Nodo*>();
    //nodosAbiertos = new std::vector<Nodo*>();


    NodoActual = NodoInicio;
    NodoAnterior = NodoInicio;
    float peso = -1;

    //lo primero es vaciar el camino por si ya se habia llamado al metodo
    nodosCerrados.clear();

    //ese || antes era una && pero se ha rayao y asi si que va
    while ((NodoActual->casillaX != NodoFinal->casillaX) || (NodoActual->casillaY != NodoFinal->casillaY)) {
        std::cout << "Nodo Actual " << NodoActual->casillaX << "," << NodoActual->casillaY << "    Meta " << NodoFinal->casillaX << "," << NodoFinal->casillaY << std::endl;
        //nodosAbiertos = new std::vector<Nodo*>();
        nodosAbiertos.clear();
        calcularListaAbiertos();
        peso = -1;
        for (int i = 0; i < 8; i++) {
            if (nodosAbiertos.at(i)->escolision == false) {

                if (peso == -1) {
                    peso = nodosAbiertos.at(i)->costoTotal;
                    NodoSiguiente = nodosAbiertos.at(i);
                    siguiente = i;
                    // NodoSiguiente = NodoActual->nodosAbiertos->at(i)->devuelveNodo();
                } else {
                    if (peso > nodosAbiertos.at(i)->costoTotal && ((nodosAbiertos.at(i)->casillaX != NodoAnterior->casillaX) && (nodosAbiertos.at(i)->casillaY != NodoAnterior->casillaY))) {
                        peso = nodosAbiertos.at(i)->costoTotal;
                        //NodoSiguiente = NodoActual->nodosAbiertos->at(i)->devuelveNodo();
                        NodoSiguiente = nodosAbiertos.at(i);
                        siguiente = i;
                    }
                }

            }//fin if

        }//fin for


        for (int j = 0; j < 8; j++) {
            if (j != siguiente) {
                delete nodosAbiertos.at(j);
            }
        }

        //sale del for, ya ha recorrido la lista de vecinos del nodo, y se ha quedado con el 
        //mejor nodo en NodoSiguiente, por lo tanto añadimos este a la lista y lo hacemos nuestro nodo Actual.
        //repetir proceso hasta que NodoSiguiente==NodoFinal
        nodosCerrados.push_back(NodoSiguiente);
        //aqui podriamos hacer un delete de todo lo del nodo actual para vaciar memoria ya que con este algoritmo
        //nunca vamos a volver hacia atras y los nodos por los que pasamos ya no los vamos a utilizar mas.
        NodoAnterior = NodoActual;
        NodoActual = NodoSiguiente;

    }//fin while
    //salimos del while y ya tendriamos el camino completo que tenemos que seguir nodo a nodo hasta llegar a la posicion del jugador.


}
*/

///nuevooo

void PathFinding::adicionarNodoAListaAbierta(Nodo *nodo) {
    int indice = 0;
    float costo = nodo->costoTotal;
    while ((listaAbierta.size() > indice) && (costo < listaAbierta.at(indice)->costoTotal)) {
        indice++;
    }
    auto it = listaAbierta.begin();
    listaAbierta.insert(it + indice, nodo);
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

bool condicion = Y >= 0 && X >=0 && Y < height && X < width;
    //Izquierda
    if (condicion && colisiones[Y][X - 1] != 1) {
        nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X - 1), tileAlto * Y), toTieso + nodoActual->costoG));
    } else {
        arribaIzquierda = false;
        abajoDerecha = false;
    }
    
    //Derecha
    if (condicion && colisiones[Y][X + 1] != 1) {
        nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X + 1), tileAlto * Y), toTieso + nodoActual->costoG));
    } else {
        arribaDerecha = false;
        abajoDerecha = false;
    }

    //Arriba
    if (condicion && colisiones[Y - 1][X] != 1) {
        nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho*X, tileAlto * (Y - 1)), toTieso + nodoActual->costoG));
    } else {
        arribaIzquierda = false;
        arribaDerecha = false;
    }

    //Abajo
    if (condicion && colisiones[Y + 1][X] != 1) {
        nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho*X, tileAlto * (Y + 1)), toTieso + nodoActual->costoG));
    } else {
        arribaDerecha = false;
        abajoDerecha = false;
    }

    //Diagonal
    if (condicion && arribaIzquierda && colisiones[Y - 1][X - 1] != 1) {
        nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X - 1), tileAlto * (Y - 1)), toTorsio + nodoActual->costoG));
    }
    if (condicion && arribaDerecha && colisiones[Y + 1][X + 1] != 1) {
        nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X + 1), tileAlto * (Y - 1)), toTorsio + nodoActual->costoG));
    }
    if (condicion && abajoIzquierda && colisiones[Y + 1][X - 1] != 1) {
        nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X - 1), tileAlto * (Y + 1)), toTorsio + nodoActual->costoG));
    }
    if (condicion && abajoDerecha && colisiones[Y - 1][X + 1] != 1) {
        nodosAdyacentes->push_back(new Nodo(nodoActual, nodoFinal, sf::Vector2f(tileAncho * (X + 1), tileAlto * (Y + 1)), toTorsio + nodoActual->costoG));
    }
    
    //printf("Encontrar Nodos Adyaccentes Final metodo \n");
//    for(int j=0;j<nodosAdyacentes->size();j++){
//        std::cout<<"Nodo "<<j<<" "<<nodosAdyacentes->at(j)->GetCasilla().x<<","<<nodosAdyacentes->at(j)->GetCasilla().y<<"    Meta    "<<nodoFinal->GetCasilla().x<<","<<nodoFinal->GetCasilla().y<<std::endl;
//    }
    return nodosAdyacentes;
}


std::vector<sf::Vector2i>* PathFinding::buscaCamino(sf::Vector2f posenemigo, sf::Vector2f posjugador) {
    listaAbierta.clear();
    listaCerrada.clear();


    Nodo *nodoFinal = new Nodo(NULL, NULL, posjugador, 0);
    Nodo *nodoInicial = new Nodo(NULL, nodoFinal, posenemigo, 0);

    adicionarNodoAListaAbierta(nodoInicial);

    while (listaAbierta.size() > 0) {
        Nodo *nodoActual = listaAbierta.at(listaAbierta.size() - 1);
        if (nodoActual->esIgual(nodoFinal)) {
            std::vector<sf::Vector2i> *mejorCamino = new std::vector<sf::Vector2i>();
            while (nodoActual != NULL) {
                auto it = mejorCamino->begin();
                mejorCamino->insert(it, nodoActual->GetCasilla());
                nodoActual = nodoActual->NodoPadre;
            }
            return mejorCamino;
        }
        //auto it = listaAbierta.end();
        listaAbierta.pop_back();

        std::vector<Nodo*> *nodosAdyacentes = encontrarNodosAdyacentes(nodoActual, nodoFinal);
        //esto es un for each
        
        for (int i = 0; i<nodosAdyacentes->size();i++) {
            //std::cout<<"tam nodos adyaccentes "<<nodosAdyacentes->size()<<"Num de iteracion= "<<i<<std::endl;
            //si este if no va hay que crearnos uno nosotros para comparar eso
            if (!buscarCasilla(nodosAdyacentes->at(i)->GetCasilla())) {
                if (BuscarNodoEnListaAbierta(nodosAdyacentes->at(i))) {
                    if (nodosAdyacentes->at(i)->costoG >= nodosAdyacentes->at(i)->costoTotal) {
                        continue;
                    }

                }
                adicionarNodoAListaAbierta(nodosAdyacentes->at(i));
            }

        }
        listaCerrada.push_back(nodoActual->GetCasilla());
        //printf("Dentro del While \n");
    }
    return NULL;

}
