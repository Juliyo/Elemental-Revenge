
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Entities/Player.hpp"
//#include "InGame.hpp"
//#include "Transition.hpp"
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
    virtual ~Game();

    void run();
    
private:

    void processEvents(); // Captura y procesa eventos
    void update(sf::Time elapsedTime);
    void render(float interpolation, sf::Time elapsedTime);
    Motor2D *motor;

private:
    static const sf::Time timePerFrame;
    StateStack *stateStack;
    float interpolation;
};
#endif


