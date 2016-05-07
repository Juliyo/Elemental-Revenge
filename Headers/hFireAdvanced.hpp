/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hFireAdvanced.hpp
 * Author: joselu
 *
 * Created on 14 de marzo de 2016, 13:06
 */

#ifndef HFIREADVANCED_HPP
#define HFIREADVANCED_HPP
#include "Hechizo.hpp"

class hFireAdvanced : public Hechizo, public Collisionable {
public:
    hFireAdvanced();
    virtual ~hFireAdvanced();
    std::string getClassName() override;
    void CreateBody() override;

    void cast(sf::Vector2f);
    void DrawWithInterpolation( float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew);
    bool lanzado=false;
    sf::Vector2f actualSize;

private:

};

#endif /* HFIREADVANCED_HPP */

