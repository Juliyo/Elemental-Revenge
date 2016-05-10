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
    sonidos->insert(std::make_pair("resources/Sounds/Cascada.ogg" , new Sound("resources/Sounds/Cascada.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/Damage.wav" , new Sound("resources/Sounds/Damage.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/Muerte.wav" , new Sound("resources/Sounds/Muerte.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/Pausa.wav" , new Sound("resources/Sounds/Pausa.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/CasaFuego.ogg" , new Sound("resources/Sounds/CasaFuego.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/Truenos.ogg" , new Sound("resources/Sounds/Truenos.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/Fbasico.wav" , new Sound("resources/Sounds/Fbasico.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/Rbasico.wav" , new Sound("resources/Sounds/Rbasico.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/Abasico.wav" , new Sound("resources/Sounds/Abasico.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/Favanzado.wav" , new Sound("resources/Sounds/Favanzado.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/Ravanzado.wav" , new Sound("resources/Sounds/Ravanzado.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/Aavanzado.wav" , new Sound("resources/Sounds/Aavanzado.wav")));
    sonidos->insert(std::make_pair("resources/Sounds/assassindie.ogg" , new Sound("resources/Sounds/assassindie.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/assassinhit.ogg" , new Sound("resources/Sounds/assassinhit.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/banditdie.ogg" , new Sound("resources/Sounds/banditdie.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/bandithit.ogg" , new Sound("resources/Sounds/bandithit.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/necromancerdead.ogg" , new Sound("resources/Sounds/necromancerdead.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/necromancerhurt.ogg" , new Sound("resources/Sounds/necromancerhurt.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/portalclose.ogg" , new Sound("resources/Sounds/portalclose.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/ratdie.ogg" , new Sound("resources/Sounds/ratdie.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/rathit.ogg" , new Sound("resources/Sounds/rathit.ogg")));
    sonidos->insert(std::make_pair("resources/Sounds/flash.wav" , new Sound("resources/Sounds/flash.wav")));
}

void SoundManager::play(std::string ruta) {
    std::map<std::string,Sound*>::iterator it =sonidos->find(ruta);
    sf::Sound* sonido=it->second->getSound();
    sonido->setBuffer(*it->second->getBuffer());
    sonido->play();
}

void SoundManager::stop(std::string ruta) {
    std::map<std::string,Sound*>::iterator it =sonidos->find(ruta);
    sf::Sound* sonido=it->second->getSound();
    sonido->stop();
}

void SoundManager::setVolumen(std::string ruta,float vol) {
    std::map<std::string,Sound*>::iterator it =sonidos->find(ruta);
    sf::Sound* sonido=it->second->getSound();
    sonido->setVolume(vol);
}