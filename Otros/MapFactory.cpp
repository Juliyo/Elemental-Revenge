/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MapFactory.cpp
 * Author: tonir
 * 
 * Created on 22 de abril de 2016, 10:10
 */

#include "MapFactory.hpp"
#include <string>

std::string MapFactory::CreateLevel(Niveles::ID id) {
    if (id == Niveles::Level1) {
        std::string m = "mapaBosqueAlfa.tmx";
        return m;
    } else if (id == Niveles::Level2) {
        std::string m = "LVL22.tmx";
        return m;
    } else if (id == Niveles::Level3) {
        std::string m = "CasaAbandonadaV2prueba.tmx";
        return m;
    } else if (id == Niveles::Level4) {
        std::string m = "mansionV2.tmx";
        return m;
    }
}
