
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
    void calculaColision(BoundingBox *bb);
    void LoadMap(std::string mapName){
        map->mapLoader(mapName);
    }
    void updateQuadTree(){
        map->UpdateQuadTree();
    }
    std::vector<tmx::MapObject*> queryQuadTree(sf::FloatRect t){
        return map->QueryQuadTree(t);
    }
    void render(){
        map->render();
    }
    Mapa *map;
private:
    
};

#endif /* LEVEL_HPP */

