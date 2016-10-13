/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sound.cpp
 * Author: kike
 * 
 * Created on 6 de mayo de 2016, 16:54
 */

#include <iostream>

#include "Sound.hpp"

Sound::Sound(std::string str) {
    buffer=new sf::SoundBuffer();
    sound=new sf::Sound();
    buffer->loadFromFile(str);
}

Sound::Sound(const Sound& orig) {
}

Sound::~Sound() {
}

sf::SoundBuffer* Sound::getBuffer() {
    return buffer;
}

sf::Sound* Sound::getSound() {
    return sound;
}


