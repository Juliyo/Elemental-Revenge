/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hechizo.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 12:30
 */

#include "../Headers/Hechizo.hpp"

Hechizo::Hechizo() {
   sf::Sprite hSprite;
   sf::Texture hTexture;
   float angleshot2=0.0f;
    hCd = 0;
    hDamage = 1;
    hLVL = 0;
    dibujar=false;
    sf::Clock tiempoCast;
    sf::Clock clockCd;
    primerCast=true;
}

Hechizo::Hechizo(const Hechizo& orig) {
}

Hechizo::~Hechizo() {
}

float Hechizo::getDamage() {
    return hDamage;
}

float Hechizo::getCD() {
    return hCd;
}
float Hechizo::getCast() {
    return hCast;
}

int Hechizo::getLevel() {
    return hLVL;
}

void Hechizo::setCD(float cd) {
    if (cd >= 0) {
        hCd = cd;
    }
}
void Hechizo::setCast(float cast) {
    if (cast >= 0) {
        hCast = cast;
    }
}
void Hechizo::setDamage(float dmg) {
    if (dmg > 0) {
        hDamage = dmg;
    }
}

void Hechizo::setLevel(int lvl) {
    if (lvl >= 0) {
        hLVL = lvl;
    }
}

void Hechizo::aumentaLVL(int lvl, float cd, float cast, float dmg) {
    if (lvl >= 0) {
        hLVL = lvl;
    }
    if (cast >= 0) {
        hCast = cast;
    }
    if (cd >= 0) {
        hCd = cd;
    }
        if (dmg > 0) {
        hDamage = dmg;
    }
}

void Hechizo::aumentaLVL() {
    int i=0;
    if(i==0){
            printf("Subo de nivel \n");
    
        hLVL += 1;
    
    
        hCast += 0.5;
    
    
        hCd -= 0.5;
    
       
        hDamage += 2;
    printf("nivel %d \n",hLVL);
    i++;
    }

}


