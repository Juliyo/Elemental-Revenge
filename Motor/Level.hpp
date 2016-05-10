
/* 
 * File:   Level.hpp
 * Author: tonir
 *
 * Created on 21 de abril de 2016, 15:13
 */

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <deque>
#include <SFML/Graphics.hpp>
#include "Mapa.hpp"
#include <vector>
#include "../Otros/BoundingBox.h"

class Level {
public:
    Level();
    Level(const Level& orig);
    virtual ~Level();
    void CreateLevels();
    void LoadMap(Niveles::ID nivel);
    void render();
    Mapa *map;
    Niveles::ID currentLevel;
private:
    std::map<Niveles::ID,std::string> *mapNiveles;
    
};

#endif /* LEVEL_HPP */

