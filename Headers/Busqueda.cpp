/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Busqueda.cpp
 * Author: kike
 * 
 * Created on 25 de abril de 2016, 13:10
 */

#include "Busqueda.hpp"

Busqueda::Busqueda() {
}

Busqueda::Busqueda(const Busqueda& orig) {
}

Busqueda::~Busqueda() {
}

void Busqueda::adicionarNodoAListaAbierta(Nodo nodo) {
    int indice = 0;

    std::vector<Nodo>::iterator it;
    it = listaAbierta->begin();
    float costo = nodo.costoTotal;
    while (listaAbierta->size() > indice && costo < listaAbierta->at(indice).costoTotal) {
        it++;
        indice++;
    }

    listaAbierta->insert(it, nodo);
}
