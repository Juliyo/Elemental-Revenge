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

class Motor2D {
public:
    Motor2D();
    static Motor2D* Instance();
    Motor2D(const Motor2D& orig);
    virtual ~Motor2D();
    void SetView(int v);
    void Draw(Sprite sp);
    
    sf::View *fondo;
    sf::View *pantalla;
    sf::View *HUD;
    sf::RenderWindow *mWindow;
    sf::Mouse *raton;
    
    
    
private:
    static Motor2D *mInstance;
};

#endif /* MOTOR2D_HPP */

