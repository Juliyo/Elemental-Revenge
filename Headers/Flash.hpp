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
#include "../Headers/Animation.hpp"

class Flash : public Hechizo {
public:
    Flash(int animation);
    Flash(const Flash& orig);
    virtual ~Flash();
    void Draw(sf::RenderWindow& window);
    void DrawWithInterpolation(sf::RenderWindow& window, float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew);
    sf::Vector2f cast(sf::Vector2f, sf::RenderWindow *mWindow);
    void cast2(sf::Clock *clockCD2);
    Animation *flashingAnimation;
    Animation *flashingAnimation2;
    
private:
    sf::Texture hTexture2;
};

#endif /* FLASH_HPP */
