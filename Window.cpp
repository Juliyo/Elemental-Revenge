/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.cpp
 * Author: julio
 * 
 * Created on 27 de marzo de 2016, 17:22
 */

#include "Window.hpp"


Window* Window::pinstance = 0;
Window* Window::Instance(){
    if(pinstance == 0){
        pinstance= new Window;
    }
    return pinstance;
}
Window::Window() {
    ancho=1280;
    alto=720;
    mWindow = sf::RenderWindow(sf::VideoMode(ancho, alto), "Hito 2 - Rama - Transicion", sf::Style::Default);
}
sf::RenderWindow* Window::GetWindow(){
    return &mWindow;
}



