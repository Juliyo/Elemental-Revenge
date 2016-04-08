/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Reloj.hpp
 * Author: Usuario
 *
 * Created on 5 de abril de 2016, 14:19
 */

#ifndef RELOJ_HPP
#define RELOJ_HPP
#include <SFML/Graphics.hpp>
class Reloj {
public:
    Reloj();
    Reloj(const Reloj& orig);
    virtual ~Reloj();
    float getTiempo();
    void restart();
private:
    sf::Clock *reloj;
};

#endif /* RELOJ_HPP */

