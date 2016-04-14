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
#include "../Headers/StringHelpers.hpp"


Video::Video(std::string ruta, int f) {
    mRuta=ruta;
    numFrames=f;
    frames = new Sprite[numFrames];
    current_frame=0;
    dibujar=false;
    for(int i=0; i < numFrames;i++){
        frames[i].setTexture(ruta + toString(i) + ".png");
        frames[i].setSmooth(true);
        frames[i].setPosition(0,0);
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
        }
        dibujar=false;
    }else{
        Motor2D::Instance()->draw(frames[current_frame]);
    }
}

bool Video::getDibujar(bool a) {
    return a;
}

bool Video::setDibujar(bool a) {
    dibujar=a;
}

