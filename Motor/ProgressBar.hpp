/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProgrssBar.hpp
 * Author: tonir
 *
 * Created on 19 de abril de 2016, 19:04
 */

#ifndef PROGRSSBAR_HPP
#define PROGRSSBAR_HPP
#include "Motor2D.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
const double PI = 3.14159265359;

class ProgressBar {
public:

    ProgressBar(float r, int nFrames, sf::Vector2f center, int tiempo, bool izquierda, sf::Vector2f escala, sf::Color color1 = sf::Color::Green, sf::Color color2 = sf::Color::Green);

    void setTime(int tiempo);
    
    ProgressBar(const ProgressBar& orig);
    virtual ~ProgressBar();

    void update(sf::Time elapsedTime);
    void draw();
    void reset();

private:
    void rellena();
    sf::VertexArray triangleFan;
    sf::Time m_frameTime;
    sf::Time m_currentTime;
    bool firstTime = false;
    bool completado = false;
    float radio;
    sf::Vector2f centro;
    int numFrames;
    std::vector<sf::Vector2f> puntos;
    int contador = 0;
    Motor2D *m;
    sf::Transform trans;
    sf::RenderStates rs;
    sf::Color loadingColor;
    sf::Color completedColor;
};

#endif /* PROGRSSBAR_HPP */

