/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hud.hpp
 * Author: tonir
 *
 * Created on 11 de marzo de 2016, 13:12
 */

#ifndef HUD_HPP
#define HUD_HPP
#include <SFML/Graphics.hpp>
class Hud{
public:
    Hud();
    Hud(const Hud& orig);
    virtual ~Hud();
    void renderHud(sf::RenderWindow *window);
    sf::FloatRect   viewBounds;
    sf::Vector2f    position;
    void            updateHud(int vidas);
    
private:
    sf::Sprite      barraVida;
    sf::IntRect     shapeVida;
    sf::Texture     tBarraVida;
    sf::Texture     tUnidadVida;
    sf::Sprite      sVida;
    sf::Text        tVida;
    sf::Font        fVida;
};

#endif /* HUD_HPP */