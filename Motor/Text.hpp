/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Text.hpp
 * Author: tonir
 *
 * Created on 8 de abril de 2016, 17:36
 */

#ifndef TEXT_HPP
#define TEXT_HPP
#include <string>
#include "SFML/Graphics.hpp"
class Text: public sf::Drawable{
public:
    Text();
    void setString(std::string texto);
    void setFont(std::string ruta);
    void setFont(sf::Font fuente);
    std::string getText();
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    void setStyle(int a);
    void setColor(int r, int g, int b, int a);
    void setColor(sf::Color color);
    void setPosition(int x, int y);
    void setScale(float x, float y);
    void setOrigin(float x, float y);
    Text(const Text& orig);
    virtual ~Text();
private:
    sf::Text m_text;
    sf::Font m_font;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(m_text, states);
    }
};

#endif /* TEXT_HPP */

