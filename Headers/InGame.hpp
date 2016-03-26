/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InGame.hpp
 * Author: joselu
 *
 * Created on 26 de marzo de 2016, 19:49
 */

#ifndef INGAME_HPP
#define INGAME_HPP

#include "State.hpp"
#include "SFML/System.hpp"


class InGame:public State {
public:
    InGame();
    InGame(const InGame& orig);
    virtual ~InGame();
    void    run();

    void Update(sf::Time elapsedTime);
    
    void			handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    void			handleMouseInput(sf::Mouse::Button button, bool isPressed);  // Maneja eventos
    
    void			render(float interpolation, sf::Time elapsedTime);

    
    void			processEvents();  // Captura y procesa eventos

    
private:
    
};

#endif /* INGAME_HPP */

