/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sound.hpp
 * Author: kike
 *
 * Created on 6 de mayo de 2016, 16:54
 */

#ifndef SOUND_HPP
#define SOUND_HPP
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class Sound {
public:
    Sound(std::string str);
    Sound(const Sound& orig);
    virtual ~Sound();
    sf::Sound* getSound();
    sf::SoundBuffer* getBuffer();
private:
    sf::Sound* sound;
    sf::SoundBuffer* buffer;
};

#endif /* SOUND_HPP */

