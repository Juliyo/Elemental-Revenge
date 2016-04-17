/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Textura.cpp
 * Author: Julio
 * 
 * Created on 13 de abril de 2016, 14:14
 */

#include "Textura.hpp"

Textura::Textura(std::string ruta) {
    Motor2D *motor = Motor2D::Instance();
    motor->Textures.insert(std::pair<int, sf::Texture*>(motor->key, new sf::Texture()));
    motor->Textures.at(motor->key)->loadFromFile(ruta);
    m_ruta = ruta;
    motor->key++;
}

Textura::Textura(const Textura& orig) {
}

Textura::~Textura() {
}

int Textura::getId() {
    return id;
}

