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
#include <iostream>
#include <vector>

class Hud {
public:
    Hud(Reloj *cds, float *coolDowns);
    Hud(const Hud& orig);
    virtual ~Hud();
    void renderHud();
    sf::FloatRect viewBounds;
    sf::Vector2f position;
    void updateHud(float vidas);
    void cambiaHechizo(int activar);
    void Update();
    void resetRayo2();
    void resetRayo1();
    
    void resetAgua1();
    void resetAgua2();
    
    void resetFuego1();
    void resetFuego2();
private:
    Sprite barraVida;
    sf::IntRect shapeVida;

    Sprite sVida;
    Sprite agua;
    Sprite fuego;
    Sprite rayo;
    Sprite *arrLeftMouse[3];
    Sprite *arrRightMouse[3];

    sf::Texture aguaGris;
    sf::Texture fuegoGris;
    sf::Texture rayoGris;

    sf::Texture aguaT;
    sf::Texture fuegoT;
    sf::Texture rayoT;

    sf::Texture mouseLeftG;
    sf::Texture mouseRightG;

    sf::CircleShape maskCircle1, maskCircle2, maskCircle3;
    sf::RenderTexture rTexture;
    sf::Image img;

    Text tVida;
    Reloj *mCds;
    float *mCoolDowns;

    int activo = 1;

    Text *cdRayo1;
    Text *cdRayo2;

    bool *draws;
    
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
    
    std::vector<sf::Vector2f> arrayPts;
    std::vector<sf::Vector2f> arrayPts1;
    std::vector<sf::Vector2f> arrayPts2;
    std::vector<sf::Vector2f> arrayPts3;
    std::vector<sf::Vector2f> arrayPts4;
    std::vector<sf::Vector2f> arrayPts5;

//    sf::Vector2f arrayPts[20]; // Fuego 1
//    sf::Vector2f arrayPts1[128]; // Agua1
//    sf::Vector2f arrayPts2[100]; // Rayo 1
//    sf::Vector2f arrayPts3[150]; // Agua 2
//    sf::Vector2f arrayPts4[250]; // Fuego 2
//    sf::Vector2f arrayPts5[150]; // Rayo 2

    Reloj r2,r1,a1,a2,f1,f2;
    int i;
    int iRayo1 = 0;
    int iRayo2 = 0;
    int iFuego1 = 0;
    int iFuego2 = 0;
    int iAgua1 = 0;
    int iAgua2 = 0;
    
    sf::VertexArray triangleRayo2;
    sf::VertexArray triangleRayo1;
    
    sf::VertexArray triangleAgua2;
    sf::VertexArray triangleAgua1;
    
    void cargarRayo();
    
    void cargarAgua();
    void cargarFuego();
    
    void calculaRayo1();
    void calculaRayo2();
    void calculaAgua1();
    void calculaAgua2();
    void calculaFuego1();
    void calculaFuego2();
    
    void renderRayo1();
    void renderRayo2();
    void renderAgua1();
    void renderAgua2();
    void renderFuego1();
    void renderFuego2();
    
    bool firstRayo1 = false;
    bool firstRayo2 = false;
    
    bool firstAgua1 = false;
    bool firstAgua2 = false;
    
    bool firstFuego1 = false;
    bool firstFuego2 = false;
};

#endif /* HUD_HPP */