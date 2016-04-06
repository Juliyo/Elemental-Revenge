/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor2D.hpp
 * Author: Usuario
 *
 * Created on 5 de abril de 2016, 13:52
 */

#ifndef MOTOR2D_HPP
#define MOTOR2D_HPP

#include "Sprite.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class Motor2D {
public:
    Motor2D();
    static Motor2D* Instance();
    Motor2D(const Motor2D& orig);
    virtual ~Motor2D();
    void SetView(int v);
    
    
    float getAngleShot(sf::Vector2f posicion);
    void Inicializar();
    
    void clear();
    void draw(Sprite *sp);
    void draw(Sprite **sp);
    void display();
    

    void inicializarVentana(std::string titulo, int ancho, int alto);
    
    bool isWindowOpen();
    void closeWindow();
    
    sf::Vector2f getMousePosition();
    sf::RenderWindow *mWindow;
private:
    static Motor2D *mInstance;
    sf::View *fondo;
    sf::View *pantalla;
    sf::View *HUD;
    sf::Vector2f *raton;
};

#endif /* MOTOR2D_HPP */

