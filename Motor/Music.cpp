/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Music.cpp
 * Author: kike
 * 
 * Created on 6 de mayo de 2016, 9:32
 */

#include "Music.hpp"

Music* Music::mInstance = 0;

Music* Music::Instance() {
    if (mInstance == 0) {
        mInstance = new Music;
    }
    return mInstance;
}

Music::Music(){
    mMusic = new sf::Music();
    mFilenames = new std::map<MUSICA::ID, std::string>();
    
    mFilenames->insert(std::make_pair(MUSICA::Menu , "resources/Sounds/Magicka.ogg"));
    mFilenames->insert(std::make_pair(MUSICA::Transiciones , "resources/Sounds/history.ogg"));
    mFilenames->insert(std::make_pair(MUSICA::Mapa1 , "resources/Sounds/Magicka2.ogg"));
    mFilenames->insert(std::make_pair(MUSICA::Mapa2 , "resources/Sounds/Creepy.ogg"));
    
    ultVol = 100.f;
    
    mMusic->setVolume(ultVol);
    currentTheme = MUSICA::Menu;
    isPlaying = false;
    printf("Termino constructor\n");
}

Music::~Music()
{
    delete mMusic; 
    mMusic=NULL;
    mFilenames->clear();
    delete mFilenames; 
    mFilenames=NULL;
}

void Music::Load(MUSICA::ID theme){
    currentTheme = theme;
    std::string filename = mFilenames->find(theme)->second;

	if (!mMusic->openFromFile(filename))
		throw std::string("Music " + filename + " could not be loaded.");
        else
            printf("La musica ha cargado correctamente\n");
    
}

void Music::Play(){
    if(!isPlaying){
        mMusic->setLoop(true);
        mMusic->play();
        isPlaying = true;
    }
}

void Music::Stop(){
    mMusic->stop();
    isPlaying = false;
}

void Music::SetVolume(float volume){
    if(volume < 0.f || volume > 100.f)
        throw std::string("Debes introducir un valor entre 0 y 100");
    
    std::cout << "Vol: " << mMusic->getVolume() << std::endl;
    
    if(volume != 0.f)
        ultVol = volume;
    
    mMusic->setVolume(volume);
}

void Music::SetPaused(bool paused){
	if (paused){
	mMusic->pause();
        isPlaying = false;
    }
	else{
        mMusic->play();
        isPlaying = true;
    }
}