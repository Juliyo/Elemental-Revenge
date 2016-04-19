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
#include "../Motor/ProgressBar.hpp"

class Hud {
public:
    Hud(Reloj *cds, float *coolDowns);
    Hud(const Hud& orig);
    virtual ~Hud();
    void renderHud(sf::Time elapsedTime);
    sf::FloatRect viewBounds;
    sf::Vector2f position;
    void updateHud(float vidas);
    void cambiaHechizo(int activar);
    void resetRayo2();
    void resetRayo1();
    
    void resetAgua1();
    void resetAgua2();
    
    void resetFuego1();
    void resetFuego2();
private:
    Motor2D *m;
    Sprite barraVida;
    sf::IntRect shapeVida;
    Sprite sVida;
    Reloj *mCds;
    float *mCoolDowns;

    int activo = 1;
    
    //Rayo
    Sprite      *rayoBueno;
    Sprite       *rBlanco;
    Sprite       *rGlare;
    Sprite       *rRayo;
    Sprite       *rSombra;
    
    //Agua
    Sprite      *aguaBueno;
    Sprite       *aBlanco;
    Sprite       *aGlare;
    Sprite       *aRayo;
    Sprite       *aSombra;
    
    //Fuego
    Sprite      *fuegoBueno;
    Sprite       *fBlanco;
    Sprite       *fGlare;
    Sprite       *fRayo;
    Sprite       *fSombra;
    
    void cargarRayo();
    void cargarAgua();
    void cargarFuego();

    
    ProgressBar *cRayo1;
    ProgressBar *cRayo2;
    ProgressBar *cAgua1;
    ProgressBar *cAgua2;
    ProgressBar *cFuego1;
    ProgressBar *cFuego2;
    
};

#endif /* HUD_HPP */