/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor2D.cpp
 * Author: Usuario
 * 
 * Created on 5 de abril de 2016, 13:52
 */

#include "Motor2D.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
Motor2D* Motor2D::mInstance = 0;
Motor2D* Motor2D::Instance(){
    if(mInstance == 0){
        mInstance= new Motor2D;
    }
    return mInstance;
}
Motor2D::Motor2D() {
}

Motor2D::Motor2D(const Motor2D& orig) {
}

Motor2D::~Motor2D() {
}

void Motor2D::SetView(int v){
    switch(v){
        case 0:
            mWindow->setView(*fondo);
           
             break;
        
           
        case 1:
             mWindow->setView(*pantalla);
             break;
        
           
        case 2:
             mWindow->setView(*HUD);
             break;  
    }
}
void Motor2D::Draw(Sprite sp) {
    mWindow->draw(sp);
}