/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sound.hpp
 * Author: Julio
 *
 * Created on 6 de mayo de 2016, 12:04
 */

#ifndef SOUND_HPP
#define SOUND_HPP
#include <map>
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class Sound {
public:
    Sound();
    Sound(const Sound& orig);
    virtual ~Sound();
    static Sound* Instance(); // Singleton
    void load();
    void play(std::string ruta);
private:
    static Sound* mInstance;
    std::map<std::string,sf::Sound*> *sonidos;
};

#endif /* SOUND_HPP */

