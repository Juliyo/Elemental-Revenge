/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Util.cpp
 * Author: julio
 * 
 * Created on 14 de marzo de 2016, 19:26
 */

#include "Util.hpp"

// Returns the length of the vector
float Util::Length(sf::Vector2f vector){
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}
 
// Normalizes the vector
sf::Vector2f Util::Normalize(sf::Vector2f vector ){
    sf::Vector2f nVector;
    float length = Length(vector);
 
    if(length != 0){
        nVector.x = vector.x/length;
        nVector.y = vector.y/length;
    }
 
    return nVector;
}
