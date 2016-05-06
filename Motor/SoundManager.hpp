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

#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP
#include <map>
#include "Sound.hpp"


class SoundManager {
public:
    SoundManager();
    SoundManager(const SoundManager& orig);
    virtual ~SoundManager();
    static SoundManager* Instance(); // Singleton
    void load();
    void play(std::string ruta);
private:
    static SoundManager* mInstance;
    std::map<std::string,Sound*> *sonidos;
};

#endif /* SOUND_HPP */

