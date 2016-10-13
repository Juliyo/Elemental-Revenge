/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dummy.hpp
 * Author: tonir
 *
 * Created on 29 de abril de 2016, 13:31
 */

#ifndef DUMMY_HPP
#define DUMMY_HPP
#include "../Entities/Entity.hpp"
#include "../Motor/Collisionable.hpp"

class Dummy : public Entity,  public Collisionable {
public:
    Dummy();
    virtual ~Dummy();
    std::string getClassName() override;


    bool touch = false;
    void collide();
    bool getCollision(sf::Vector2f &p);
private:

};

#endif /* DUMMY_HPP */

