/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MapFactory.hpp
 * Author: tonir
 *
 * Created on 22 de abril de 2016, 10:10
 */

#ifndef MAPFACTORY_HPP
#define MAPFACTORY_HPP
#include "../Motor/Mapa.hpp"
class MapFactory {
public:
    static std::string CreateLevel(Niveles::ID id);
    
private:

};

#endif /* MAPFACTORY_HPP */

