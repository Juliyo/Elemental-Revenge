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

#include "SoundManager.hpp"


SoundManager* SoundManager::mInstance = 0;

SoundManager* SoundManager::Instance() {
    if (mInstance == 0) {
        mInstance = new SoundManager;
    }
    return mInstance;
}
SoundManager::SoundManager() {
   sonidos=new std::map<std::string,Sound*>();
}

SoundManager::SoundManager(const SoundManager& orig) {
}

SoundManager::~SoundManager() {
}

void SoundManager::load() {
    sonidos->insert(std::make_pair("resources/Sounds/Pistola.wav" , new Sound("resources/Sounds/Pistola.wav")));
}

void SoundManager::play(std::string ruta) {
    std::map<std::string,Sound*>::iterator it =sonidos->find(ruta);
    sf::Sound* sonido=it->second->getSound();
    sonido->setBuffer(*it->second->getBuffer());
    sonido->setVolume(100);
    sonido->play();
}
