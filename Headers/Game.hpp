
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemigo.hpp"

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
    
private:
    static const sf::Time	timePerFrame;
	
    
    //Recursos
    sf::Texture                 texturaFondo;
    sf::Sprite                  spriteFondo;
    sf::Font                    contFonts;
    
    //Graficos
    sf::RenderWindow		mWindow;
    sf::View                    mWorldView;
    Player			player;
    Enemigo			enemigo;
    
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


