/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Video.cpp
 * Author: Julio
 * 
 * Created on 9 de abril de 2016, 1:09
 */

#include "Video.hpp"
#include "Textura.hpp"
#include "../Headers/StringHelpers.hpp"


Video::Video(std::string ruta, int f, int x, int y, int tipo, sf::Vector2f scale, bool setOrigin, sf::Vector2f size) {
    mRuta=ruta;
    numFrames=f;
    frames = new Sprite[numFrames];
    current_frame=0;
    dibujar=false;
    origin.x = size.x/2;
    origin.y = size.y/2;
    for(int i=0; i < numFrames;i++){
        if(tipo == 0){
            if(setOrigin){
                frames[i].setTexture(ruta + toString(i) + ".png");
                frames[i].setOrigin(origin.x,origin.y);
            }else{
                frames[i].setTexture(ruta + toString(i) + ".png");
            }
            
        }else if(tipo == 1){
            if(setOrigin){
                frames[i].setTexture(ruta + toString(i) + ".gif");
                frames[i].setOrigin(origin.x,origin.y);
            }else{
                frames[i].setTexture(ruta + toString(i) + ".gif");
            }
        }
        
        frames[i].setSmooth(true);
        frames[i].setPosition(x,y);
        frames[i].setScale(scale.x,scale.y);
    }
}

Video::Video(const Video& orig) {
}

Video::~Video() {
    
}
void Video::PlayVideo(){
    if(dibujar){
        Motor2D::Instance()->draw(frames[current_frame]);
        current_frame++;
        if(current_frame >= numFrames){
            current_frame=0;
            looped = true;
        }
        dibujar=false;
    }else{
        Motor2D::Instance()->draw(frames[current_frame]);
    }
}

bool Video::getDibujar() {
    return dibujar;
}

void Video::setDibujar(bool a) {
    dibujar=a;
}

bool Video::getLooped() {
    return looped;
}

void Video::setLooped(bool a) {
    looped=a;
}
