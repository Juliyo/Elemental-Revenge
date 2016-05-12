
/* 
 * File:   Level.cpp
 * Author: tonir
 * 
 * Created on 21 de abril de 2016, 15:13
 */

#include "Level.hpp"
#include "../Otros/MapFactory.hpp"

Level::Level() {
    map = new Mapa();
    mapNiveles = new std::map<Niveles::ID, std::string>();
    CreateLevels();
}

Level::Level(const Level& orig) {
}

Level::~Level() {
    delete map;
    delete mapNiveles;
}

void Level::CreateLevels() {
    mapNiveles->insert(std::make_pair(Niveles::ID::Level1, MapFactory::CreateLevel(Niveles::ID::Level1)));
    mapNiveles->insert(std::make_pair(Niveles::ID::Level2, MapFactory::CreateLevel(Niveles::ID::Level2)));
    mapNiveles->insert(std::make_pair(Niveles::ID::Level3, MapFactory::CreateLevel(Niveles::ID::Level3)));
    mapNiveles->insert(std::make_pair(Niveles::ID::Level4, MapFactory::CreateLevel(Niveles::ID::Level4)));
}

void Level::LoadMap(Niveles::ID nivel) {
    std::map<Niveles::ID, std::string>::iterator it = mapNiveles->find(nivel);
    map->mapLoader(it->second);
    currentLevel = nivel;
}

void Level::render() {
    map->render();
}
