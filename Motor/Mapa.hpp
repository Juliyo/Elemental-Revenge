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
    void createCollisions(){
        
        TiXmlDocument doc;
        doc.LoadFile(nombreMapa.c_str());
        TiXmlElement* map = doc.FirstChildElement("map");
        
        map->QueryIntAttribute("width", &_width);
        map->QueryIntAttribute("height", &_height);
        colisiones = new int*[_height];
        for(int i = 0;i<_height;i++){
            colisiones[i] = new int[_width];
        }
        TiXmlElement *layer = map->FirstChildElement()->NextSiblingElement("layer");
        while(layer){
            std::cout<<layer->Attribute("name")<<std::endl;
            std::string nombreCapa = layer->Attribute("name");
            if(nombreCapa.compare("Colision") == 0){
                break;
            }
            layer = layer->NextSiblingElement("layer");
        }
        TiXmlElement *nodo = layer->FirstChildElement("data")->FirstChildElement("tile");
        int gid;
        for(int i = 0;i<_width;++i){
            for(int j=0;j<_height;++j){
                nodo->QueryIntAttribute("gid", &gid);
                if(gid != 0){
                    colisiones[i][j] = 1;
                }else{
                    colisiones[i][j] = 0;
                }
                nodo = nodo->NextSiblingElement("tile");
            }
        }
        /*
        for(int i=0 ; i < _width ; i++){
            std::cout<<i<<std::endl;
        for(int j= 0;j<_height; j++){
            
            std::cout<<colisiones[i][j];
            
        }
        std::cout<<std::endl;
    }*/

    }
    int **colisiones;
    void createStaticMeshes();
    
private:
    int mapaActual;
    tmx::MapLoader ml;
    int cuenta=0;
    std::string nombreMapa;
    b2World *world;
};




#endif /* MAP_HPP */