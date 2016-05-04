/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContactListener.hpp
 * Author: tonir
 *
 * Created on 29 de abril de 2016, 14:42
 */

#ifndef CONTACTLISTENER_HPP
#define CONTACTLISTENER_HPP
#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener, public b2ContactFilter {
public:
    ContactListener();
    ContactListener(const ContactListener& orig);
    virtual ~ContactListener();
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;

private:

};

#endif /* CONTACTLISTENER_HPP */

