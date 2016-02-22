/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.hpp
 * Author: tonir
 *
 * Created on 22 de febrero de 2016, 11:32
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
class Player{
public:
    Player(float velocidad);
    int         getVida();
    void        setVida(int vidaNueva);
    float       getVelocidad();
    void        setVelocidad(float velocidad);
    
    sf::Texture mTexture;
    sf::Sprite  mSprite;
    
private:
    float   mVelocidad;
    int     mVida;
    
};

#endif /* PLAYER_HPP */

