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
    hCd = 0;
    hDamage = 1;
    hLVL = 0;
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

int Hechizo::getLevel() {
    return hLVL;
}

void Hechizo::setCD(float cd) {
    if (cd >= 0) {
        hCd = cd;
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
/*void Hechizo::Draw(sf::RenderWindow& window){
	renderState.GetSprite().setPosition(physicsState.GetPosition());
	window.draw(renderState.GetSprite());
}*/

void Hechizo::DrawWithInterpolation(sf::RenderWindow& window, float interpolation, PhysicsState *physicsState){
	renderState.Draw(window, physicsState->GetPreviousPosition(), physicsState->GetPosition(), interpolation);
}
