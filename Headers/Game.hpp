
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemigo.hpp"

//#include "InGame.hpp"
//#include "Transition.hpp"
#include "Pause.hpp"
#include "Carga2.hpp"
#include "../Motor/Motor2D.hpp"
#include "../Motor/Reloj.hpp"
#include "Muerte.hpp"
//#include "../"

#include "../States/State.hpp"
#include "../States/StateStack.hpp"

#include <cmath>
#include <math.h>
#ifdef _WIN32
#include <Windows.h>
#endif

class Game {
public:
    Game();
    void run();
    Player* GetPlayer();

private:

    void processEvents(); // Captura y procesa eventos
    void update(sf::Time elapsedTime);
    void render(float interpolation, sf::Time elapsedTime);
    
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Maneja eventos
    void handlePlayerInput2(sf::Keyboard::Key key, bool isPressed); // Maneja eventos
    void handleMouseInput(sf::Mouse::Button button, bool isPressed); // Maneja eventos

    void updateView();
    void UpdatePlayerAnimation();
    Motor2D *motor;
   


private:
    static const sf::Time timePerFrame;

    //Graficos
    //InGame *EstadoInGame;
    //Transition *EstadoTransition;
    //Menu *EstadoMenu;
    Pause *EstadoPause;
    Muerte *EstadoMuerte;
    //LoadingState *EstadoCarga1;
    Carga2 *EstadoCarga2;
    
    StateStack *stateStack;
    
    float interpolation;
    
    bool estadoInGame = false;
    bool estadoTransition = false;
    bool estadoMenu = false;
    bool estadoPause = false;
    bool estadoMuerte = false;
    bool estadoCarga1 = false;
    bool estadoCarga2 = false;
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
    sf::Thread *thread;
    sf::Thread *thread2;
    
    void cargarInGameTransition();
    void cargarMapa();
    

};



#endif


