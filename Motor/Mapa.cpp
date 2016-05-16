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

Mapa::Mapa() : ml("resources/Mapas") { //Ruta de la carpeta con los mapas

}

Mapa::Mapa(const Mapa& orig) : ml("resources/Mapas") {
}

void Mapa::mapLoader(std::string mapName) {
    world = InGame::Instance()->physicWorld;
    nombreMapa = "resources/Mapas/" + mapName;
    ml.Load(mapName);
    //Crea la matriz de colisiones de enteros para el pathfinder
    createCollisions();
    //Crea los objetos estaticos del mapa para el motor de fisicas
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

void Mapa::CreateBosses() {
    Boss *boss = InGame::Instance()->boss;
    
    boss->Inicializar(100, 100);
    boss->SetRectangleColision(0, 0, 60, 76);
    boss->CreateBody();
    
//    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
//    for (const auto& l : layers) {
//        if (l.name == "Boss") //static bodies which make up the map geometry
//        {
//            for (const auto& o : l.objects) {
//                boss->Inicializar(o.GetCentre().x, o.GetCentre().y);
//    boss->SetRectangleColision(0, 0, 60, 76);
//    boss->CreateBody();
//}
//        }
//    }
}

void Mapa::CreateMelees() {

    InGame::Instance()->melee = new std::vector<Melee*>();

    std::vector<Melee*> *melees = InGame::Instance()->melee;
    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
    for (const auto& l : layers) {
        if (l.name == "Melees") //static bodies which make up the map geometry
        {

            melees->reserve(l.objects.size());
            numEnemigos+=l.objects.size();
            for (const auto& o : l.objects) {
                int random = rand() % 2; // v1 in the range 0 to 99
                if (random == 0) {
                    Melee *melee = new Melee();
                    melee->Inicializar(o.GetCentre().x, o.GetCentre().y, Tipo::ID::Rata);
                    melee->SetRectangleColision(0, 0, 40, 34);
                    melee->CreateBody();
                    melees->push_back(melee);
                } else {
                    Melee *melee = new Melee();
                    melee->Inicializar(o.GetCentre().x, o.GetCentre().y, Tipo::ID::Ninja);
                    melee->SetRectangleColision(0, 0, 34, 34);
                    melee->CreateBody();
                    melees->push_back(melee);
                }
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

// Devuelve una capa concreta del mapa

const tmx::MapLayer& Mapa::GetLayer(const std::string& name) {
    const auto& layers = ml.GetLayers();
    for (const auto& l : layers) {
        if (l.name == name) return l;
    }
    return layers[0];
}

Mapa::~Mapa() {
    delete[] colisiones;

}

void Mapa::createCollisions() {

    TiXmlDocument doc;
    doc.LoadFile(nombreMapa.c_str());
    TiXmlElement* map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width", &_width);
    map->QueryIntAttribute("height", &_height);
    colisiones = new int*[_height];
    for (int i = 0; i < _height; i++) {
        colisiones[i] = new int[_width];
    }
    TiXmlElement *layer = map->FirstChildElement()->NextSiblingElement("layer");
    while (layer) {
        std::cout << layer->Attribute("name") << std::endl;
        std::string nombreCapa = layer->Attribute("name");
        if (nombreCapa.compare("Colision") == 0) {
            break;
        }
        layer = layer->NextSiblingElement("layer");
    }
    TiXmlElement *nodo = layer->FirstChildElement("data")->FirstChildElement("tile");
    int gid;
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            nodo->QueryIntAttribute("gid", &gid);
            if (gid != 0) {
                colisiones[i][j] = 1;
            } else {
                colisiones[i][j] = 0;
            }
            nodo = nodo->NextSiblingElement("tile");
        }
    }

}

void Mapa::CreateCasters() {

    InGame::Instance()->caster = new std::vector<Caster*>();
    std::vector<Caster*> *casters = InGame::Instance()->caster;
    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
    for (const auto& l : layers) {
        if (l.name == "Casters") //static bodies which make up the map geometry
        {
            casters->reserve(l.objects.size());
            numEnemigos+=l.objects.size();
            for (const auto& o : l.objects) {
                
                
                int random = rand() % 2; // v1 in the range 0 to 99
                if (random == 0) {
                    Caster *caster = new Caster();
                    caster->Inicializar(o.GetCentre().x, o.GetCentre().y, Tipo::Caster::Mago);
                   // caster->SetRectangleColision(0, 0, 34, 34);
                    caster->CreateBody();
                    casters->push_back(caster);
                } else {
                    Caster *caster = new Caster();
                caster->Inicializar(o.GetCentre().x, o.GetCentre().y, Tipo::Caster::Bandido);
                //caster->SetRectangleColision(0, 0, 34, 34);
                caster->CreateBody();
                casters->push_back(caster);
                }
                
            }
        }
    }
}

void Mapa::CreatePlayer() {
    InGame *world = InGame::Instance();
    world->player = new Player();




    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
    for (const auto& l : layers) {
        if (l.name == "Player") //static bodies which make up the map geometry
        {
            for (const auto& o : l.objects) {
                world->player -> Inicializar(o.GetCentre().x, o.GetCentre().y);
                world->player->SetRectangleColision(14, 12, 36, 52);
                world->player->CreateBody();
                world->player->SetEstado(Estado::ID::Vivo);
                world->player->hRayoBasico->clockCd.restart();
            }
        }
    }
}