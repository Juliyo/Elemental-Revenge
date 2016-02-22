/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Flash.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 23:20
 */

#ifndef FLASH_HPP
#define FLASH_HPP

#include "../Headers/Hechizo.hpp"


class Flash:public Hechizo {
public:
    Flash();
    Flash(const Flash& orig);
    virtual ~Flash();
private:

};

#endif /* FLASH_HPP */

