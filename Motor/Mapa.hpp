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

#include "../Motor/Motor2D.hpp"
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include <tmx/MapLayer.h>
#include "tinyxml.h"
#include <string>
#include <vector>
#include <Box2D/Box2D.h>

namespace Niveles{
    enum ID{
        Level1,
        Level2,
        Level3,
        Level4
    };
}

class Mapa {
public:
    Mapa();
    Mapa(const Mapa& orig);
    virtual ~Mapa();
    void leerMapa(int numMapa, int versionMapa);
    void leerMapa2();
    void dibujaMapa1();
    void dibuja2Mapa1();
    
    void dibujaMapa2();
    void dibuja2Mapa2();
    
    void dibujaMapa3();
    void dibuja2Mapa3();
    
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
    void mapLoader(std::string mapName);
    void render();
    const tmx::MapLayer& GetLayer(const std::string& name);
    void UpdateQuadTree(){
        Motor2D *m = Motor2D::Instance();
        sf::FloatRect viewBounds(m->getCenterFromView(1) - m->getSizeFromView(1) / 2.f, m->getSizeFromView(1));
        ml.UpdateQuadTree(viewBounds);
    }
    std::vector<tmx::MapObject*> QueryQuadTree(sf::FloatRect t){
        return ml.QueryQuadTree(t);
    }
    void createCollisions();
    int **colisiones;
    void createStaticMeshes();
    
private:
    int mapaActual;
    tmx::MapLoader ml;
    std::string nombreMapa;
    b2World *world;
};




#endif /* MAP_HPP */