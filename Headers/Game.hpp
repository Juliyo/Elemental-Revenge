/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.hpp
 * Author: julio
 *
 * Created on 19 de febrero de 2016, 17:19
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include<SFML/Window/Mouse.hpp>
#include "../Headers/Player.hpp"
#include "../Headers/hFireBasic.hpp"
#include <cmath>
#include "../Headers/WorldState.hpp"


class Game : private sf::NonCopyable
{
	public:
							Game();
		void					run();
		

	private:
		void					processEvents();
                WorldState                              updateGameStateSTICK(sf::Time timeElapsed,WorldState &lastState);
                void                                    renderWithInterpolation(WorldState &lastState, WorldState &newState, float percentTick);
                void                                    updatePlayer(sf::Time elapsedTime);
                void                                    updateHechizo(sf::Time elapsedTime);
                void                                    updateView(sf::Time elapsedTime);
                sf::Vector2f                            normalize(const sf::Vector2f& source);
		void					render();

		void					updateStatistics(sf::Time elapsedTime);	
		void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		

	private:
		static const float		PlayerSpeed;
		static const sf::Time           TimePerFrame;
                
                sf::Clock                               clock;
                sf::Clock                               updateClock;               
		sf::RenderWindow                        mWindow;
		Player                                  mPlayer;
		sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
                sf::View                                mWorldView;
                sf::FloatRect                           mWorldBounds;
                sf::Vector2f                            mSpawnPosition;
                sf::Sprite                              mFondo;
                sf::Texture                             mFondoT;
		std::size_t				mStatisticsNumFrames;
                hFireBasic                              hFuegoBasico[20];
		bool					mIsMovingUp;
		bool					mIsMovingDown;
		bool					mIsMovingRight;
		bool					mIsMovingLeft;
                int                                     contFuego;
                
};


#endif /* GAME_HPP */

