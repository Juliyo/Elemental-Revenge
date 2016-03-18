
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game : private sf::NonCopyable
{
public:
    Game();
    void			run();
    
    
private:
    void			processEvents();  // Captura y procesa eventos
    void			update(sf::Time elapsedTime);
    void			render(float interpolation, sf::Time elapsedTime);
    void			handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    void                        updateView();
    void                        UpdatePlayerAnimation();
    sf::View                    getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight);
    
private:
    static const sf::Time	timePerFrame;
    
    //Recursos
    sf::Texture                 texturaFondo;
    sf::Sprite                  spriteFondo;
    sf::Texture                 texturaRelleno;
    sf::Sprite                  spriteRelleno;
    sf::Font                    contFonts;
    sf::Texture                 mouseTexture;
    sf::Sprite                  mouseSprite;
    
    //Graficos
    sf::RenderWindow		mWindow;
    sf::View                    mWorldView;
    sf::View                    mBackgroundView;
    sf::View                    mHud;
    Player			*player;
    
    //Estadisticas
    sf::Text			mStatisticsText;
    
    float                       interpolation;
	
    //Eventos
    bool			isMovingUp;
    bool			isMovingDown;
    bool			isMovingRight;
    bool			isMovingLeft;
    bool                        noKeyWasPressed = true;
    bool			firstTime;
    bool			isInterpolating;
};



#endif


