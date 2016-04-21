/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParalellTask.hpp
 * Author: julio
 *
 * Created on 21 de abril de 2016, 18:37
 */

#ifndef PARALELLTASK_HPP
#define PARALELLTASK_HPP
#include <SFML/System.hpp>
#include "../Motor/Text.hpp"
class ParalellTask {
public:
    ParalellTask();
    virtual ~ParalellTask();
    
    void			Execute(Text *texto);
    bool			IsFinished();
    float			GetCompletion();
private:
    void			RunTask();
    
    sf::Thread                  mThread;
    sf::Clock                   mElapsedTime;
    sf::Mutex                   mMutex;
    
    Text                        *mTexto;
    
    bool			mFinished;
    bool                        loading;

};

#endif /* PARALELLTASK_HPP */

