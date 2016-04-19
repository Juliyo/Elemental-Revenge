/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Video.hpp
 * Author: Julio
 *
 * Created on 9 de abril de 2016, 1:09
 */

#ifndef VIDEO_HPP
#define VIDEO_HPP
#include "Motor2D.hpp"

class Video {
public:
    Video(std::string ruta, int f, int x, int y, int tipo, sf::Vector2f scale);
    Video(const Video& orig);
    virtual ~Video();
    
    void PlayVideo();
    bool setDibujar(bool a);
    bool getDibujar(bool a);
private:
    Sprite *frames;
    std::string mRuta;
    int numFrames;
    int current_frame;
    
    bool dibujar;
};

#endif /* VIDEO_HPP */

