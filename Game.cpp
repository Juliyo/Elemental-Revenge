/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <../Headers/Game.hpp>
#include <../Headers/StringHelpers.hpp>
#include "Headers/Player.hpp"



//const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

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
    mWorldView.zoom(0.5f);
    mPlayer.mTexture.loadFromFile("resources/Textures/character.png");
    mPlayer.mSprite.setTexture(mPlayer.mTexture);
    mPlayer.mSprite.setTextureRect(sf::IntRect(0, 0, 31, 46));
    mPlayer.mSprite.setPosition(100, 100);
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
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }

        updateStatistics(elapsedTime);
        render();
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

            case sf::Event::MouseButtonReleased:




                hFuegoBasico[contFuego].hSprite.setPosition(mPlayer.mSprite.getPosition());
                sf::Vector2f mousePosition = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
                float angleShot = atan2(mousePosition.y - hFuegoBasico[contFuego].hSprite.getPosition().y,
                        mousePosition.x - hFuegoBasico[contFuego].hSprite.getPosition().x);
                hFuegoBasico[contFuego].angleshot2 = angleShot; //so it goes in a straight line
                contFuego++;
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;

        }


    }
}

void Game::update(sf::Time elapsedTime) {
    updatePlayer(elapsedTime);
    updateHechizo(elapsedTime);
    updateView(elapsedTime);
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

    mPlayer.mSprite.move(movement * elapsedTime.asSeconds());


}

void Game::updateHechizo(sf::Time elapsedTime) {
    int i;
    for (int i = 0; i < 20; i++) {
        sf::Vector2f movement(800 * cos(hFuegoBasico[i].angleshot2) * 1.0f, 800 * sin(hFuegoBasico[i].angleshot2) * 1.0f);
        hFuegoBasico[i].hSprite.move(movement * elapsedTime.asSeconds());
    }

}

void Game::updateView(sf::Time elapsedTime) {
    sf::Vector2f mousePosition = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
    float x = ((mousePosition.x) / 4.5 + mPlayer.mSprite.getPosition().x);
    float y = ((mousePosition.y) / 4.5 + mPlayer.mSprite.getPosition().y);

    mWorldView.setCenter(x, y);
    mWindow.setView(mWorldView);
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mFondo);

    //
    for(int i=0;i<20;i++){
            mWindow.draw( hFuegoBasico[contFuego].hSprite);
    }

    mWindow.draw(mPlayer.mSprite);
    mWindow.draw(mStatisticsText);


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