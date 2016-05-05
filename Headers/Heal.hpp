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

#include "Hechizo.hpp"
#include "Animation.hpp"
#include "Hud.hpp"
class Heal: public Hechizo, public Collisionable {
public:
    Heal();
    virtual ~Heal();
    std::string getClassName() override;
    void CreateBody() override;

    bool cast(Hud *hud);
    void DrawWithInterpolation( float interpolation, sf::Vector2f pos1,sf::Vector2f pos2);
    
    Animation   *animacion;
};
#endif /* HEAL_HPP */
