/* 
 * File:   Hud.cpp
 * Author: tonir
 * 
 * Created on 11 de marzo de 2016, 13:12
 */

#include "StringHelpers.hpp"
#include "Hud.hpp"
#include "Motor/Sprite.hpp"
#include "AnimatedSprite.hpp"
#include <iomanip>

Hud::Hud(Reloj *cds, float *coolDowns) {
    m = Motor2D::Instance();
    mCds = cds;
    mCoolDowns = coolDowns;
    
    cRayo1 = new ProgressBar(120, 150, sf::Vector2f(1000, 1500), mCoolDowns[0], 1, sf::Vector2f(0.5,0.6),sf::Color::Yellow);
    cRayo2 = new ProgressBar(120, 150, sf::Vector2f(1000, 1500), mCoolDowns[1], 0, sf::Vector2f(0.5,0.6),sf::Color::Yellow);
    cAgua1 = new ProgressBar(120, 150, sf::Vector2f(1300, 1500), mCoolDowns[2], 1, sf::Vector2f(0.5,0.6),sf::Color::Yellow);
    cAgua2 = new ProgressBar(120, 150, sf::Vector2f(1300, 1500), mCoolDowns[3], 0, sf::Vector2f(0.5,0.6),sf::Color::Yellow);
    cFuego1 = new ProgressBar(120, 25, sf::Vector2f(700, 1500), 0.35, 1, sf::Vector2f(0.5,0.6),sf::Color::Yellow);
    cFuego2 = new ProgressBar(120, 150, sf::Vector2f(700, 1500), mCoolDowns[5], 0, sf::Vector2f(0.5,0.6),sf::Color::Yellow);
    
    std::string ruta = "resources/Textures/hudHealthBar.png";
    std::string ruta2 = "resources/Textures/barraVida.png";

    barraVida.setTexture(ruta);
    barraVida.setScale(0.6f, 0.7f);
    barraVida.setSmooth(false);
    barraVida.setPosition(20, 15);

    sVida.setTexture(ruta2);
    sVida.setSmooth(false);
    sVida.setRepeated(false);
    sVida.setScale(0.6f, 0.7f);
    sVida.setPosition(20 + (130 * 0.6), 15 + (30 * 0.7));

    sVida.setTextRect(130, 30, (289 - 130), 58);

    cargarRayo();

    cargarAgua();
    
    cargarFuego();

}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
    
}

void Hud::renderHud(sf::Time elapsedTime) {

    cRayo1->update(elapsedTime);
    cRayo2->update(elapsedTime);
    cAgua1->update(elapsedTime);
    cAgua2->update(elapsedTime);
    cFuego1->update(elapsedTime);
    cFuego2->update(elapsedTime);
    
    m->draw(barraVida);
    m->draw(sVida);

    cRayo2->draw();
    cRayo1->draw();
    cAgua1->draw();
    cAgua2->draw();
    cFuego1->draw();
    cFuego2->draw();
    
    m->draw(fBlanco);
    m->draw(fuegoBueno);
    m->draw(fSombra);
    m->draw(fGlare);

    m->draw(rBlanco);
    m->draw(rayoBueno);
    m->draw(rSombra);
    m->draw(rGlare);

    m->draw(aBlanco);
    m->draw(aguaBueno);
    m->draw(aSombra);
    m->draw(aGlare);
    
    

}

void Hud::cambiaHechizo(int activar) {
    switch (activo) {
        case 3:

            break;
        case 2:

            break;
        case 1:

            break;
        default:
            break;
    }
    switch (activar) {
        case 3:
            
            activo = 3;
            break;
        case 2:

            activo = 2;
            break;
        case 1:

            activo = 1;
            break;
        default:
            break;
    }
}

void Hud::updateHud(float vidas) {
    sVida.setTextRect(130, 30, (289 - 130) / (15 / vidas), 58);
}

void Hud::cargarRayo() {

    rBlanco = new Sprite();
    rayoBueno = new Sprite();
    rGlare = new Sprite();
    rSombra = new Sprite();

    rBlanco->setTexture("resources/Textures/hud/blanco.png", true);
    rBlanco->setOrigin(rBlanco->getTextureSize().x / 2, rBlanco->getTextureSize().y / 2);
    rBlanco->setPosition(500, 900);
    rBlanco->setScale(0.5, 0.6);
    rayoBueno->setTexture("resources/Textures/hud/rayo.png", true);
    rayoBueno->setOrigin(rayoBueno->getTextureSize().x / 2, rayoBueno->getTextureSize().y / 2);
    rayoBueno->setPosition(500, 900);
    rayoBueno->setScale(0.5, 0.6);
    rGlare->setTexture("resources/Textures/hud/glare.png", true);
    rGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    rGlare->setPosition(500, 900);
    rGlare->setScale(0.5, 0.6);
    rSombra->setTexture("resources/Textures/hud/sombra.png", true);
    rSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    rSombra->setPosition(500, 900);
    rSombra->setScale(0.5, 0.6);
}

void Hud::resetRayo2() {
    cRayo2->reset();
}

void Hud::resetRayo1() {
    cRayo1->reset();
}

void Hud::cargarAgua() {

    aBlanco = new Sprite();
    aguaBueno = new Sprite();
    aGlare = new Sprite();
    aSombra = new Sprite();

    aBlanco->setTexture("resources/Textures/hud/blanco.png", true);
    aBlanco->setOrigin(rBlanco->getTextureSize().x / 2, rBlanco->getTextureSize().y / 2);
    aBlanco->setPosition(650, 900);
    aBlanco->setScale(0.5, 0.6);

    aguaBueno->setTexture("resources/Textures/hud/agua.png", true);
    aguaBueno->setOrigin(rayoBueno->getTextureSize().x / 2, rayoBueno->getTextureSize().y / 2);
    aguaBueno->setPosition(650, 900);
    aguaBueno->setScale(0.5, 0.6);

    aGlare->setTexture("resources/Textures/hud/glare.png", true);
    aGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    aGlare->setPosition(650, 900);
    aGlare->setScale(0.5, 0.6);

    aSombra->setTexture("resources/Textures/hud/sombra.png", true);
    aSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    aSombra->setPosition(650, 900);
    aSombra->setScale(0.5, 0.6);
}

void Hud::resetAgua2(){
    cAgua2->reset();
}
void Hud::resetAgua1() {
    cAgua1->reset();
}

void Hud::resetFuego1(){
    cFuego1->reset();
}

void Hud::resetFuego2(){
    cFuego2->reset();
}

void Hud::cargarFuego() {
    fBlanco = new Sprite();
    fuegoBueno = new Sprite();
    fGlare = new Sprite();
    fSombra = new Sprite();

    fBlanco->setTexture("resources/Textures/hud/blanco.png", true);
    fBlanco->setOrigin(rBlanco->getTextureSize().x / 2, rBlanco->getTextureSize().y / 2);
    fBlanco->setPosition(350, 900);
    fBlanco->setScale(0.5, 0.6);

    fuegoBueno->setTexture("resources/Textures/hud/fuego.png", true);
    fuegoBueno->setOrigin(rayoBueno->getTextureSize().x / 2, rayoBueno->getTextureSize().y / 2);
    fuegoBueno->setPosition(350, 900);
    fuegoBueno->setScale(0.5, 0.6);

    fGlare->setTexture("resources/Textures/hud/glare.png", true);
    fGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    fGlare->setPosition(350, 900);
    fGlare->setScale(0.5, 0.6);

    fSombra->setTexture("resources/Textures/hud/sombra.png", true);
    fSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    fSombra->setPosition(350, 900);
    fSombra->setScale(0.5, 0.6);
}
