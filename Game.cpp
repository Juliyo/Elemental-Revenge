/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <../Headers/Game.hpp>
#include <../Headers/StringHelpers.hpp>
#include <iostream>
#include <cmath>
//SOLO EN WINDOWS
#ifdef _WIN32
#include <Windows.h>
#endif

#include "Headers/Player.hpp"
#include "../Headers/WorldState.hpp"
#define kUpdateTimePS 1000/15

Game::Game()
: mWindow(sf::VideoMode(1280, 720), "SFML Application", sf::Style::Close)
, mWorldView(mWindow.getDefaultView())
, mPlayer(150.f)
, hFuegoBasico()
, mFont()
, mFondo()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingRight(false)
, mIsMovingLeft(false)
, contFuego(0) {
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(true);
    mWorldView.zoom(0.5f);
    //mWorldView.setViewport(sf::FloatRect(0.15f, 0.f, 0.7f, 1.f));
    mPlayer.mTexture.loadFromFile("resources/Textures/character.png");
    mPlayer.mSprite.setTexture(mPlayer.mTexture);
    mPlayer.mSprite.setTextureRect(sf::IntRect(0, 0, 31, 46));
    mPlayer.mSprite.setPosition(100, 100);

    //  mWindow.setMouseCursorVisible(false);

#ifdef _WIN32
    HWND handler = mWindow.getSystemHandle();
    RECT rWindow;
    GetWindowRect(handler, &rWindow);
    ClipCursor(&rWindow);
#endif

    mPlayer.mSprite.setOrigin(5, 46 / 2);


    if (!mFondoT.loadFromFile("resources/Textures/grasstext.png")) {
        //Error
    }
    mFondoT.setRepeated(true);
    mFondo.setTextureRect(sf::IntRect(0, 0, 2000, 2000));
    mFondo.setTexture(mFondoT);
    mFondo.setPosition(0, 0);

    mFont.loadFromFile("resources/Fonts/Sansation.ttf");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(mWindow.getSize().x, mWindow.getSize().y);
    mStatisticsText.setCharacterSize(10);
}

void Game::run() {
    int tecla;
    sf::Time timeElapsed;
    WorldState newState;
    WorldState lastState;
    
    while (mWindow.isOpen()) {
        processEvents();
        if(updateClock.getElapsedTime().asMilliseconds() > kUpdateTimePS){
            lastState = newState;
            timeElapsed=updateClock.restart();
            newState=updateGameStateSTICK(timeElapsed,lastState);
        }
        float percentTick= std::min(1.f,(float)updateClock.getElapsedTime().asSeconds()/kUpdateTimePS);
        renderWithInterpolation(lastState,newState,percentTick);

    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;

        }


    }
}

WorldState Game::updateGameStateSTICK( sf::Time timeElapsed, WorldState &lastState) {
    
    sf::Vector2f movement(0.f, 0.f);
    WorldState aState;
    if (mIsMovingUp)
        movement.y -= mPlayer.getVelocidad();
    if (mIsMovingDown)
        movement.y += mPlayer.getVelocidad();
    if (mIsMovingLeft)
        movement.x -= mPlayer.getVelocidad();
    if (mIsMovingRight)
        movement.x += mPlayer.getVelocidad();
    int a;
        //movement=normalize(movement)*mPlayer.getVelocidad();

    //mPlayer.mSprite.move(movement * timeElapsed.asSeconds());
    aState.jugadorX=mPlayer.mSprite.getPosition().x+movement.x * timeElapsed.asSeconds();
    aState.jugadorY=mPlayer.mSprite.getPosition().y+movement.y * timeElapsed.asSeconds();
    return aState;
}

void Game::updatePlayer(sf::Time elapsedTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= mPlayer.getVelocidad();
    if (mIsMovingDown)
        movement.y += mPlayer.getVelocidad();
    if (mIsMovingLeft)
        movement.x -= mPlayer.getVelocidad();
    if (mIsMovingRight)
        movement.x += mPlayer.getVelocidad();
    
        //movement=normalize(movement)*mPlayer.getVelocidad();

    mPlayer.mSprite.move(movement * elapsedTime.asSeconds());


}

void Game::renderWithInterpolation(WorldState &lastState, WorldState &newState, float percentTick) {
    mWindow.clear();
    mWindow.draw(mFondo);

    float jugadorX = lastState.jugadorX * (1-percentTick) + newState.jugadorX * percentTick;
    float jugadorY = lastState.jugadorY * (1-percentTick) + newState.jugadorY * percentTick;
    mPlayer.mSprite.setPosition(jugadorX,jugadorY);
    mWindow.draw(mPlayer.mSprite);

    mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime) {
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
        mStatisticsText.setString(
                "Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
                "Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
    
}