/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.hpp
 * Author: USUARIO
 *
 * Created on 20 de marzo de 2016, 17:32
 */

#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

class Map {
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();
    void leerMapa(int numMapa);
    void leerMapa2();
    void dibujaMapa1(sf::RenderWindow &window);
    void dibuja2Mapa1(sf::RenderWindow &window);
    
    void dibujaMapa2(sf::RenderWindow &window);
    void dibuja2Mapa2(sf::RenderWindow &window);
    
    void dibujaMapa3(sf::RenderWindow &window);
    void dibuja2Mapa3(sf::RenderWindow &window);
    
    int getMapaActual();
    
    sf::Sprite  getMap();
    int _numLayers=0;
    int ***_tilemap;
    int _height;
    int _width;
    int _tileHeigth;
    int _tileWidth;
    sf::Sprite ****_tilemapSprite;
    sf::Texture _tilesetTexture;
    sf::Sprite *_tilesetSprite;
private:
   
    int mapaActual;




};




#endif /* MAP_HPP */