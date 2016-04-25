/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.cpp
 * Author: USUARIO
 * 
 * Created on 20 de marzo de 2016, 17:32
 */

#include "Mapa.hpp"

#include "tinystr.h"
#include "tinyxml.h"
#include "Motor2D.hpp"
#include "../States/StateStack.hpp"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../States/InGame.hpp"
#include "../Otros/tmxHelper.hpp"

using namespace std;

Mapa::Mapa()
: ml("resources/Mapas") {

}

void Mapa::mapLoader(std::string mapName) {
    world = InGame::Instance()->physicWorld;
    nombreMapa = "resources/Mapas/" + mapName;
    ml.Load(mapName);
    createCollisions();
    createStaticMeshes();
}

void Mapa::createStaticMeshes() {
    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
    for (const auto& l : layers) {
        if (l.name == "Static") //static bodies which make up the map geometry
        {
            for (const auto& o : l.objects) {
                //receive a pointer to the newly created body
                b2Body* b = tmx::BodyCreator::Add(o, *world);
            }
        }
    }
}

void Mapa::render() {
    Motor2D *m = Motor2D::Instance();
    const auto& layers = ml.GetLayers();
    for (const auto& l : layers) {
        ml.Draw(*m->mWindow, l, true);
    }
    //    ml.Draw(*m->mWindow,GetLayer("Capa 1"),false);
    //    ml.Draw(*m->mWindow,GetLayer("Capa 2"),false);
    //    ml.Draw(*m->mWindow,GetLayer("Capa 3"),false);
    //    ml.Draw(*m->mWindow,GetLayer("Capa 4"),false);
    //    ml.Draw(*m->mWindow,GetLayer("Capa 5"),false);

}

Mapa::Mapa(const Mapa& orig) :
ml("resources/Mapas") {
}
// Devuelve una capa concreta del mapa

const tmx::MapLayer& Mapa::GetLayer(const std::string& name) {
    const auto& layers = ml.GetLayers();
    for (const auto& l : layers) {
        if (l.name == name) return l;
    }
    return layers[0];
}

Mapa::~Mapa() {
    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            delete[] _tilemap[l][y];
        }
        delete[] _tilemap[l];
    }
    delete[] _tilemap;
}

void Mapa::leerMapa(int numMapa, int versionMapa) {

    mapaActual = numMapa;

    TiXmlDocument doc;
    if (numMapa == 1) {
        doc.LoadFile("resources/mapaBosqueAlfa.tmx");
    }
    if (numMapa == 2) {

        if (versionMapa == 1) {
            doc.LoadFile("resources/CasaAbandonadaV2.tmx");
        } else {
            doc.LoadFile("resources/LVL22.tmx");
        }
    }

    if (numMapa == 3) {
        doc.LoadFile("resources/mansionV2.tmx");
    }
    TiXmlElement* map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width", &_width);
    map->QueryIntAttribute("height", &_height);
    map->QueryIntAttribute("tilewidth", &_tileWidth);
    map->QueryIntAttribute("tileheight", &_tileHeigth);

    TiXmlElement *img = map->FirstChildElement("tileset");
    int numTil = 0;
    while (img) {
        numTil++;
        img = img->NextSiblingElement("tileset");
    }

    string filename;

    img = map->FirstChildElement("tileset");

    while (img) {
        filename = (string) img->FirstChildElement("image")->Attribute("source");
        img = img->NextSiblingElement("tileset");
    }

    _tilesetTexture.loadFromFile(filename);
    TiXmlElement *layer = map->FirstChildElement("layer");
    while (layer) {
        _numLayers++;
        layer = layer->NextSiblingElement("layer");
    }

    _tilemap = new int**[_numLayers];
    for (int i = 0; i < _numLayers; i++) {
        _tilemap[i] = new int*[_height];
    }

    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            _tilemap[l][y] = new int[_width];
        }
    }

    TiXmlElement *data;

    layer = map->FirstChildElement("layer");
    string *name = new string[_numLayers];
    int j = 0;
    int l = 0;

    while (layer) {
        data = layer->FirstChildElement("data")->FirstChildElement("tile");
        name[j] = (string) layer->Attribute("name");
        while (data) {
            for (int y = 0; y < _height; y++) {
                for (int x = 0; x < _width; x++) {
                    data->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                    data = data->NextSiblingElement("tile");
                }
            }
        }
        l++;
        layer = layer->NextSiblingElement("layer");
        j++;
    }

    _tilemapSprite = new sf::Sprite***[_numLayers];

    for (int l = 0; l < _numLayers; l++) {
        _tilemapSprite[l] = new sf::Sprite**[_height];
    }

    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            _tilemapSprite[l][y] = new sf::Sprite*[_width];
            for (int x = 0; x < _width; x++) {
                _tilemapSprite[l][y][x] = new sf::Sprite();
            }
        }
    }

    int columns = _tilesetTexture.getSize().x / _tileWidth;
    int rows = _tilesetTexture.getSize().y / _tileHeigth;


    _tilesetSprite = new sf::Sprite[columns * rows];
    int t = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            _tilesetTexture.setSmooth(1);
            _tilesetSprite[t].setTexture(_tilesetTexture);
            _tilesetSprite[t].setTextureRect(sf::IntRect(x*_tileWidth, y*_tileHeigth, _tileWidth, _tileHeigth));
            t++;
        }
    }
    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                int gid = _tilemap[l][y][x] - 1;
                if (gid >= rows * columns) {
                    std::cout << "ERROR\n";
                } else if (gid > 0) {

                    _tilemapSprite[l][y][x] = new sf::Sprite(_tilesetTexture, _tilesetSprite[gid].getTextureRect());
                    _tilemapSprite[l][y][x]->setPosition(x*_tileWidth, y * _tileHeigth);
                } else {
                    _tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }

}

void Mapa::dibujaMapa1() {
    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                if (l != 3 && l != 2) {
                    if (_tilemapSprite[l][y][x] != NULL) {
                        Motor2D::Instance()->draw(*(_tilemapSprite[l][y][x]));
                        cuenta++;
                    }
                }
            }
        }
    }
    //std::cout<<"Cuenta: "<<cuenta<<std::endl;
    cuenta = 0;
}

void Mapa::dibuja2Mapa1() {

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_tilemapSprite[2][y][x] != NULL) {
                Motor2D::Instance()->draw(*(_tilemapSprite[2][y][x]));
            }
        }
    }

}

void Mapa::dibujaMapa2() {


    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            //if (l != 3 && l != 5) {
            if (_tilemapSprite[0][y][x] != NULL) {
                Motor2D::Instance()->draw(*(_tilemapSprite[0][y][x]));
                cuenta++;
            }

            if (_tilemapSprite[2][y][x] != NULL) {
                Motor2D::Instance()->draw(*(_tilemapSprite[2][y][x]));
                cuenta++;
            }
            if (_tilemapSprite[4][y][x] != NULL) {
                Motor2D::Instance()->draw(*(_tilemapSprite[4][y][x]));
                cuenta++;
            }
        }
    }

    cuenta++;
    //std::cout<<"Cuenta: "<<cuenta<<std::endl;
    cuenta = 0;
}

void Mapa::dibuja2Mapa2() {

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_tilemapSprite[5][y][x] != NULL) {
                Motor2D::Instance()->draw(*(_tilemapSprite[5][y][x]));
            }
            if (_tilemapSprite[1][y][x] != NULL) {
                Motor2D::Instance()->draw(*(_tilemapSprite[1][y][x]));
            }
        }
    }

}

void Mapa::dibujaMapa3() {
    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                if (l != 3 && l != 1 && l != 6) {
                    if (_tilemapSprite[l][y][x] != NULL) {
                        Motor2D::Instance()->draw(*(_tilemapSprite[l][y][x]));
                        cuenta++;
                    }
                }
            }
        }
    }

    //std::cout<<"Cuenta: "<<cuenta<<std::endl;
    cuenta = 0;
}

void Mapa::dibuja2Mapa3() {

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            if (_tilemapSprite[1][y][x] != NULL) {
                Motor2D::Instance()->draw(*(_tilemapSprite[1][y][x]));
            }
            if (_tilemapSprite[6][y][x] != NULL) {
                Motor2D::Instance()->draw(*(_tilemapSprite[6][y][x]));
            }
        }
    }

}

sf::Sprite Mapa::getMap() {
    return ****_tilemapSprite;
}

void Mapa::leerMapa2() {


    TiXmlDocument doc;
    doc.LoadFile("resources/mapaBosqueAlfa.tmx");
    TiXmlElement* map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width", &_width);
    map->QueryIntAttribute("height", &_height);
    map->QueryIntAttribute("tilewidth", &_tileWidth);
    map->QueryIntAttribute("tileheight", &_tileHeigth);

    TiXmlElement *img = map->FirstChildElement("tileset");
    int numTil = 0;
    while (img) {
        numTil++;
        img = img->NextSiblingElement("tileset");
    }

    string filename;

    img = map->FirstChildElement("tileset");

    while (img) {
        filename = (string) img->FirstChildElement("image")->Attribute("source");
        img = img->NextSiblingElement("tileset");
    }

    _tilesetTexture.loadFromFile(filename);
    TiXmlElement *layer = map->FirstChildElement("layer");
    while (layer) {
        _numLayers++;
        layer = layer->NextSiblingElement("layer");
    }

    _tilemap = new int**[_numLayers];
    for (int i = 0; i < _numLayers; i++) {
        _tilemap[i] = new int*[_height];
    }

    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            _tilemap[l][y] = new int[_width];
        }
    }

    TiXmlElement *data;

    layer = map->FirstChildElement("layer");
    string *name = new string[_numLayers];
    int j = 0;
    int l = 0;

    while (layer) {
        data = layer->FirstChildElement("data")->FirstChildElement("tile");
        name[j] = (string) layer->Attribute("name");
        while (data) {
            for (int y = 0; y < _height; y++) {
                for (int x = 0; x < _width; x++) {
                    data->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                    data = data->NextSiblingElement("tile");
                }
            }
        }
        l++;
        layer = layer->NextSiblingElement("layer");
        j++;
    }

    _tilemapSprite = new sf::Sprite***[_numLayers];

    for (int l = 0; l < _numLayers; l++) {
        _tilemapSprite[l] = new sf::Sprite**[_height];
    }

    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            _tilemapSprite[l][y] = new sf::Sprite*[_width];
            for (int x = 0; x < _width; x++) {
                _tilemapSprite[l][y][x] = new sf::Sprite();
            }
        }
    }

    int columns = _tilesetTexture.getSize().x / _tileWidth;
    int rows = _tilesetTexture.getSize().y / _tileHeigth;



    _tilesetSprite = new sf::Sprite[columns * rows];
    int s = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            _tilesetTexture.setSmooth(1);
            _tilesetSprite[s].setTexture(_tilesetTexture);
            _tilesetSprite[s].setTextureRect(sf::IntRect(x*_tileWidth, y*_tileHeigth, _tileWidth, _tileHeigth));
            s++;
        }
    }


    for (int l = 0; l < _numLayers; l++) {
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                int gid = _tilemap[l][y][x] - 1;
                if (gid >= rows * columns) {
                    std::cout << "ERROR\n";
                } else if (gid > 0) {

                    _tilemapSprite[l][y][x] = new sf::Sprite(_tilesetTexture, _tilesetSprite[gid].getTextureRect());
                    _tilemapSprite[l][y][x]->setPosition(x*_tileWidth, y * _tileHeigth);
                } else {
                    _tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }

}

int Mapa::getMapaActual() {
    return mapaActual;
}
