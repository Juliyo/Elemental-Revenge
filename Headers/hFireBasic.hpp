/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hFireBasic.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 12:45
 */

#ifndef HFIREBASIC_HPP
#define HFIREBASIC_HPP

#include "../Headers/Hechizo.hpp"


class hFireBasic: public Hechizo {
public:
    hFireBasic();
    hFireBasic(const hFireBasic& orig);
    virtual ~hFireBasic();
    void cast(sf::Vector2f , sf::RenderWindow *mWindow);
    void DrawWithInterpolation(sf::RenderWindow& window, float interpolation);
  void Update2(sf::Vector2f velocity, sf::Time elapsedTime);
    //Animation **currentAnimation;
    Animation *animationInicio;
private:
};

#endif /* HFIREBASIC_HPP */