/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hWaterBasic.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 23:06
 */

#ifndef HWATERBASIC_HPP
#define HWATERBASIC_HPP

#include "Hechizo.hpp"
#include "Enemigo.hpp"

class hWaterBasic:public Hechizo {
public:
    hWaterBasic();
    hWaterBasic(const hWaterBasic& orig);
    virtual ~hWaterBasic();
    void cast(sf::Vector2f , sf::RenderWindow *mWindow, Enemigo *enemigo);
    
    void setDibujar(bool NuevoDibujar);
    
};

#endif /* HWATERBASIC_HPP */

