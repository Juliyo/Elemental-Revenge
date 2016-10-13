/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Util.hpp
 * Author: julio
 *
 * Created on 14 de marzo de 2016, 19:26
 */

#ifndef UTIL_HPP
#define UTIL_HPP
#include "SFML/Graphics.hpp"
class Util {
public:
    static float Length(sf::Vector2f vector);
    static sf::Vector2f Normalize(sf::Vector2f vector);
private:

};

#endif /* UTIL_HPP */

