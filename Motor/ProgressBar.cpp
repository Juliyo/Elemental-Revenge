/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProgrssBar.cpp
 * Author: tonir
 * 
 * Created on 19 de abril de 2016, 19:04
 */

#include "ProgressBar.hpp"

ProgressBar::ProgressBar(float r, int nFrames, sf::Vector2f center, float tiempo, bool izquierda, sf::Vector2f escala, sf::Color color1, sf::Color color2) {
    radio = r;
    numFrames = nFrames;
    centro = center;
    m_frameTime = sf::seconds(tiempo / (float) (nFrames + 1));
    m_currentTime = sf::Time::Zero;

    triangleFan.setPrimitiveType(sf::TrianglesFan);
    puntos.push_back(centro);

    float incre = 3.15 / numFrames;

    if (izquierda) {
        for (double angle = 2 * PI; angle >= PI; angle -= incre) {
            sf::Vector2f p(centro.x + radio * sin(angle), centro.y + radio * cos(angle));
            puntos.push_back(p);
        }
    } else {
        for (double angle = 0; angle <= PI; angle += incre) {
            sf::Vector2f p(centro.x + radio * sin(angle), centro.y + radio * cos(angle));
            puntos.push_back(p);
        }
    }
    m = Motor2D::Instance();
    trans.scale(escala);
    rs.transform = trans;
    loadingColor = color1;
    completedColor = color2;
    rellena();
}

ProgressBar::ProgressBar(const ProgressBar& orig) {
}

ProgressBar::~ProgressBar() {
}

void ProgressBar::update(sf::Time elapsedTime) {
    if (firstTime) {

        // add delta time
        m_currentTime += elapsedTime;

        // if current time is bigger then the frame time advance one frame
        if (m_currentTime >= m_frameTime) {
            // reset time, but keep the remainder
            m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());

            // get next Frame index
            if (contador + 1 < (numFrames + 1)) {
                contador++;
            } else {
                //Animacion terminada
                if(!completado){
                    for (int i = 0; i <= numFrames; i++) {
                        triangleFan[i].color = completedColor;
                        triangleFan[i].color.a = 200;
                    }
                    completado = true;
                }
            }
            //if (contador != (numFrames + 1)) {
                triangleFan.append(puntos.at(contador-1));
                triangleFan[contador-1].color = loadingColor;
                triangleFan[contador-1].color.a = 200;
            //}
        }
    }
}

void ProgressBar::draw() {
    m->draw(triangleFan, rs);
}

void ProgressBar::reset() {
    triangleFan.clear();
    contador = 0;
    m_currentTime = sf::Time::Zero;
    firstTime = true;
    completado = false;
}

void ProgressBar::setTime(int tiempo) {
    m_frameTime = sf::seconds(tiempo / (float) numFrames+1);
}

void ProgressBar::rellena() {
    for (int i = 0; i < numFrames+1; i++) {
        triangleFan.append(puntos.at(i));
        triangleFan[i].color = completedColor;
        triangleFan[i].color.a = 200;
    }
}



