/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sound.cpp
 * Author: Julio
 * 
 * Created on 6 de mayo de 2016, 12:04
 */

#include <map>

#include "Sound.hpp"


Sound* Sound::mInstance = 0;

Sound* Sound::Instance() {
    if (mInstance == 0) {
        mInstance = new Sound;
    }
    return mInstance;
}
Sound::Sound() {
   sonidos=new std::map<std::string,sf::Sound*>();
}

Sound::Sound(const Sound& orig) {
}

Sound::~Sound() {
}

void Sound::load() {
    sonidos->insert(std::make_pair("resources/Sounds/Pistola.wav" , new sf::Sound()));
}

void Sound::play(std::string ruta) {
    sf::SoundBuffer *buffer=new sf::SoundBuffer();
    buffer->loadFromFile(ruta);
    std::map<std::string,sf::Sound*>::iterator it =sonidos->find(ruta);
    sf::Sound *sonido=it->second;
    sonido->setBuffer(*buffer);
    sonido->setVolume(100);
    sonido->play();
}
