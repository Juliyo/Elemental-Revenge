/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cargar.h
 * Author: alfon
 *
 * Created on 16 de marzo de 2016, 13:33
 */

#ifndef CARGAR_H
#define	CARGAR_H
#include <SFML/Graphics.hpp>

class Cargar {
public:
    Cargar();
    Cargar(const Cargar& orig);
    virtual ~Cargar();
    void leerMapa();
    void dibuja(sf::RenderWindow &window);
    sf::Sprite  fondo;
    sf::Sprite  getMapa();
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
   

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    /*ANADIDO*/
    sf::Texture fond;
     
     /*ANADIDO*/

};

#endif	/* CARGAR_H */

