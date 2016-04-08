/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Videos.hpp
 * Author: Julio
 *
 * Created on 9 de abril de 2016, 0:52
 */

#ifndef VIDEOS_HPP
#define VIDEOS_HPP

class Videos {
public:
    Videos(std::string ruta);
    Videos(const Videos& orig);
    virtual ~Videos();
private:
    sf::Sprite *frames;
    void playVideo();
};

#endif /* VIDEOS_HPP */

