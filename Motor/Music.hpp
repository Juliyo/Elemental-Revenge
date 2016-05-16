/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Music.hpp
 * Author: kike
 *
 * Created on 6 de mayo de 2016, 9:32
 */

#ifndef MUSIC_HPP
#define MUSIC_HPP
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace MUSICA
{
        enum ID
        {
                Menu=0,
                Transiciones=1,
                Mapa1=2,
                Mapa2=3,
                Mapa3=4,
                Boss=5
        };
}

class Music {
public:
    Music();
    Music(const Music& orig);
    virtual ~Music();
    static Music* Instance(); // Singleton

        void Load(MUSICA::ID Mapa1);
        void Play();
        void Stop();
        void SetPaused(bool paused);
        
        bool IsPaused(){ bool a =mMusic->Playing; return !mMusic->Playing; }
        
        void SetVolume(float volume);
        float GetVolume() const{ return mMusic->getVolume(); }
        
        MUSICA::ID      currentTheme;
        bool           isPlaying;   
        
        bool Activate(){ SetVolume((ultVol <= 4.f ? 60.f : ultVol)); }
        bool DeActivate(){ ultVol = GetVolume(); SetVolume(0.f); }
        
        float ultVol;
private:

    static Music* mInstance;
    
    sf::Music*			   mMusic;
    std::map<MUSICA::ID, std::string>*   mFilenames;

};

#endif /* MUSIC_HPP */

