
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemigo.hpp"
#include "State.hpp"
#include "InGame.hpp"
#include "Transition.hpp"

#include "Menu2.hpp"

#include "Pause.hpp"

class Game : private sf::NonCopyable
{
public:
    Game();
    void			run();
    Player*                     GetPlayer();
    
private:
    
    void			processEvents();  // Captura y procesa eventos
    void			update(sf::Time elapsedTime);
    void			render(float interpolation, sf::Time elapsedTime);
    void			handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    void			handlePlayerInput2(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    void			handleMouseInput(sf::Mouse::Button button, bool isPressed);  // Maneja eventos
    
    void                        updateView();
    void                        UpdatePlayerAnimation();
    

    
private:
    static const sf::Time	timePerFrame;
	
    //Graficos
    sf::RenderWindow		*mWindow;
    
    
    
    InGame                      *EstadoInGame;
    Transition                  *EstadoTransition;
    Menu2                       *EstadoMenu;  
    
    Pause                       *EstadoPause;
    
    float                       interpolation;
	
    //Eventos
    /*bool			isMovingUp;
    bool			isMovingDown;
    bool			isMovingRight;
    bool			isMovingLeft;
    bool                        rayoAdvancedCast = false;
    bool                        rayoBasicCast = false;
    
    bool                        noKeyWasPressed = true;
    bool			firstTime;
    bool			isInterpolating;
    bool                        isShooting;
    bool                        aux;*/
};



#endif


