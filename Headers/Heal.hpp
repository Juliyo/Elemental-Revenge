/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Heal.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 23:15
 */

#ifndef HEAL_HPP
#define HEAL_HPP

#include "../Headers/Hechizo.hpp"


class Heal: public Hechizo {
public:
    Heal();
    Heal(const Heal& orig);
    virtual ~Heal();
private:

};

#endif /* HEAL_HPP */

