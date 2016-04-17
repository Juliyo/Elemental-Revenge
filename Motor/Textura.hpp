/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Textura.hpp
 * Author: Julio
 *
 * Created on 13 de abril de 2016, 14:14
 */

#ifndef TEXTURA_HPP
#define TEXTURA_HPP
#include <iostream>
#include "Motor2D.hpp"
class Textura {
public:
    Textura( std::string ruta );
    Textura(const Textura& orig);
    virtual ~Textura();
    int getId();
private:
    int id;
    const std::string m_ruta;
};

#endif /* TEXTURA_HPP */

