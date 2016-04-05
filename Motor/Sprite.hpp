/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sprite.hpp
 * Author: Usuario
 *
 * Created on 5 de abril de 2016, 14:40
 */

#ifndef SPRITE_HPP
#define SPRITE_HPP

class Sprite: public sf::Drawable {
public:
    Sprite();
    Sprite(const Sprite& orig);
    virtual ~Sprite();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* SPRITE_HPP */

