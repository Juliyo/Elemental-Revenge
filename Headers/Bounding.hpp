/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bounding.hpp
 * Author: joselu
 *
 * Created on 9 de abril de 2016, 12:39
 */

#ifndef BOUNDING_HPP
#define BOUNDING_HPP

class Bounding {
public:
    Bounding();
    Bounding(const Bounding& orig);
    virtual ~Bounding();
    
    int top;
    int right;
    int left;
    int bot;
    
private:
    
};

#endif /* BOUNDING_HPP */

