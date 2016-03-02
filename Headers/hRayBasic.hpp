/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayBasic.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 23:05
 */

#ifndef HRAYBASIC_HPP
#define HRAYBASIC_HPP

#include "../Headers/Hechizo.hpp"


class hRayBasic:public Hechizo {
public:
    hRayBasic();
    hRayBasic(const hRayBasic& orig);
    virtual ~hRayBasic();
private:
    void cast();
};

#endif /* HRAYBASIC_HPP */

