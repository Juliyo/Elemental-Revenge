
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hPP"

class Game : private sf::NonCopyable
{
public:
    Game();
    void			run();
    
    
private:
    void			processEvents();  // Captura y procesa eventos
    void			update(sf::Time elapsedTime);
    void			render(float interpolation);
    void			handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    void                        updateView();
    sf::View                    getLetterboxView(sf::View view, int windowWidth, int windowHeight);
    
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
    Player			player;
    
    //Estadisticas
    sf::Text			mStatisticsText;
    
    float                       interpolation;
	
    //Eventos
    bool			isMovingUp;
    bool			isMovingDown;
    bool			isMovingRight;
    bool			isMovingLeft;
    bool			firstTime;
    bool			isInterpolating;
};



#endif


