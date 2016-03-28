/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.hpp
 * Author: julio
 *
 * Created on 27 de marzo de 2016, 17:22
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SFML/Graphics.hpp"
class Window {
public:
    static Window* Instance();
    sf::RenderWindow* GetWindow();
    int ancho;
    int alto;
    
protected:
    Window();
    Window(const Window &);
    Window &operator= (const Window &);
private:
    static Window* pinstance;
    sf::RenderWindow *mWindow;
};

#endif /* WINDOW_HPP */

