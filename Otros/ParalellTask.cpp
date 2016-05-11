/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParalellTask.cpp
 * Author: julio
 * 
 * Created on 21 de abril de 2016, 18:37
 */

#include "ParalellTask.hpp"
#include <SFML/System/Lock.hpp>
#include "../States/StateStack.hpp"
#include "../States/InGame.hpp"
#include <iostream>
#include <functional>

ParalellTask::ParalellTask() : mThread(&ParalellTask::RunTask, this), mFinished(false), loading(false) {
}


ParalellTask::~ParalellTask() {
}

void ParalellTask::Execute(Text *texto) {
    mFinished = false;
    mElapsedTime.restart();
    mTexto = texto;
    mThread.launch();
}

bool ParalellTask::IsFinished() {
    sf::Lock lock(mMutex);
    return mFinished;
}

float ParalellTask::GetCompletion() {
    sf::Lock lock(mMutex);
    return mElapsedTime.getElapsedTime().asSeconds();
}

void ParalellTask::setLevel(int newLevel) {
    level=newLevel;
}


void ParalellTask::RunTask() {

        printf("Dime que llegas o reviento algo\n");
    bool ended = false;
    while (!ended) {
        printf("Dime que llegas o reviento algo\n");
        sf::Lock lock(mMutex);
        if(level==0){
            
        if (!loading) {
            StateStack::Instance()->GetState(States::ID::Transition)->Inicializar();
            mTexto->setString("Juego++");
            StateStack::Instance()->GetState(States::ID::InGame)->Inicializar();
            StateStack::Instance()->GetState(States::ID::Pause)->Inicializar();//TODO: llamarlo desde el inicializar de loadingState
            StateStack::Instance()->GetState(States::ID::Muerte)->Inicializar();
            loading = true;
            
        }
        if (mElapsedTime.getElapsedTime().asSeconds() >= 5.f && loading) {
            ended = true;
            this->level++;  
            StateStack::Instance()->SetCurrentState(States::ID::Transition);
        }

    }else{
                mTexto->setString("Mapa++");
                InGame::Instance()->physicWorld = new b2World(tmx::SfToBoxVec(sf::Vector2f(0.f, 0.f)));
                InGame::Instance()->ct = new ContactListener();
                InGame::Instance()->physicWorld->SetContactListener(InGame::Instance()->ct);
                InGame::Instance()->level->LoadMap(static_cast<Niveles::ID> (level-1));

                if(level>1){
                   if (InGame::Instance()->level->currentLevel!= Niveles::Level1) {
                    while (!InGame::Instance()->caster->empty()) {
                        InGame::Instance()->caster->pop_back();
                    }
                    while (!InGame::Instance()->colaEnemigos->empty()) {
                    InGame::Instance()->colaEnemigos->pop_back();
                    }

                    while (!InGame::Instance()->melee->empty()) {
                        InGame::Instance()->melee->pop_back();
                    }
                    delete InGame::Instance()->player;

                }
                }
                InGame::Instance()->level->map->CreateMelees();
                InGame::Instance()->level->map->CreateCasters();
                InGame::Instance()->level->map->CreatePlayer();   
                
            if (mElapsedTime.getElapsedTime().asSeconds() >= 3.f && loading) {
            ended = true;
            this->level++;  
            StateStack::Instance()->SetCurrentState(States::ID::InGame);
        }
    }
      std::cout << "Termino metodo con level"  <<level <<std::endl;
    }
        
        sf::Lock lock(mMutex);
        mFinished = true;
        
}


