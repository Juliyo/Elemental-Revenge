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
#include "../Motor/Motor2D.hpp"
#include "../Motor/Text.hpp"

class Hud{
public:
    Hud(Reloj *cds, float *coolDowns);
    Hud(const Hud& orig);
    virtual ~Hud();
    void renderHud();
    sf::FloatRect   viewBounds;
    sf::Vector2f    position;
    void            updateHud(float vidas);
    void            cambiaHechizo(int activar);
    void            Update();
private:
    Sprite      barraVida;
    sf::IntRect     shapeVida;
    
    Sprite      sVida;
    Sprite      agua;
    Sprite      fuego;
    Sprite      rayo;
    Sprite      *arrLeftMouse[3];
    Sprite      *arrRightMouse[3];
    
    sf::Texture aguaGris;
    sf::Texture fuegoGris;
    sf::Texture rayoGris;
    
    sf::Texture aguaT;
    sf::Texture fuegoT;
    sf::Texture rayoT;
    
    sf::Texture mouseLeftG;
    sf::Texture mouseRightG;
    
    sf::CircleShape maskCircle1, maskCircle2, maskCircle3;
    sf::RenderTexture   rTexture;
    sf::Image           img;
    
    Text        tVida;
    Reloj       *mCds;
    float       *mCoolDowns;
    
    int         activo=1;
    
    Text       *cdRayo1;
    Text       *cdRayo2;
    
    bool        *draws;
    
    Sprite rayoBueno;
    Sprite rBlanco, rFondo, rGlare, rRayo, rSombra;
};

#endif /* HUD_HPP */