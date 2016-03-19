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

#include "../Headers/Hechizo.hpp"



class hFireAdvanced : public Hechizo {
public:
    hFireAdvanced();
    hFireAdvanced(const hFireAdvanced& orig);
    virtual ~hFireAdvanced();
    
    void cast(sf::Vector2f , sf::RenderWindow *mWindow);
    void DrawWithInterpolation(sf::RenderWindow& window, float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew);
    bool lanzado=false;

private:

};

#endif /* HFIREADVANCED_HPP */

