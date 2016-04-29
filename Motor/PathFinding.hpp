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
class PathFinding {
public:
    PathFinding();
    PathFinding(const PathFinding& orig);
    virtual ~PathFinding();
    
    void encontrarCamino(sf::Vector2f posjugador,sf::Vector2f posenemigo ){
        
    }
private:
    std::vector<Nodo*>  nodosAbiertos;
    std::vector<Nodo*>  nodosCerrados;
    
};

#endif /* PATHFINDING_HPP */

