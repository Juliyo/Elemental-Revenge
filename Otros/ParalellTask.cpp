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

void ParalellTask::RunTask() {
    bool ended = false;
    while (!ended) {
        sf::Lock lock(mMutex);
        if (!loading) {
            StateStack::Instance()->GetState(States::ID::Transition)->Inicializar();
            mTexto->setString("Juego++");
            StateStack::Instance()->GetState(States::ID::InGame)->Inicializar();
            StateStack::Instance()->GetState(States::ID::Pause)->Inicializar();//TODO: llamarlo desde el inicializar de loadingState
            StateStack::Instance()->GetState(States::ID::Muerte)->Inicializar();//TODO: llamarlo desde el inicializar de loadingState
            loading = true;
        }
        if (mElapsedTime.getElapsedTime().asSeconds() >= 5.f && loading) {
            ended = true;
            StateStack::Instance()->SetCurrentState(States::ID::Transition);
        }

    }

    {
        sf::Lock lock(mMutex);
        mFinished = true;
    }
}
