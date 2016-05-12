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

    cRayo1 = new ProgressBar(120, 150, sf::Vector2f(1670, 2275), mCoolDowns[0], 1, sf::Vector2f(0.3, 0.4), sf::Color::Yellow);
    cRayo2 = new ProgressBar(120, 150, sf::Vector2f(1670, 2275), mCoolDowns[1], 0, sf::Vector2f(0.3, 0.4), sf::Color::Yellow);
    cAgua1 = new ProgressBar(120, 150, sf::Vector2f(2000, 2275), mCoolDowns[2], 1, sf::Vector2f(0.3, 0.4), sf::Color::Yellow);
    cAgua2 = new ProgressBar(120, 150, sf::Vector2f(2000, 2275), mCoolDowns[3], 0, sf::Vector2f(0.3, 0.4), sf::Color::Yellow);
    cFuego1 = new ProgressBar(120, 25, sf::Vector2f(1335, 2275), mCoolDowns[4], 1, sf::Vector2f(0.3, 0.4), sf::Color::Yellow);
    cFuego2 = new ProgressBar(120, 150, sf::Vector2f(1335, 2275), mCoolDowns[5], 0, sf::Vector2f(0.3, 0.4), sf::Color::Yellow);
    
    cCurar = new ProgressBar(120, 180, sf::Vector2f(1501, 3675), mCoolDowns[7], 0, sf::Vector2f(0.2, 0.25), sf::Color::Yellow,sf::Color::Green, true);
    
    cFlash = new ProgressBar(120, 180, sf::Vector2f(3500, 3675), mCoolDowns[6], 0, sf::Vector2f(0.2, 0.25), sf::Color::Yellow,sf::Color::Green, true);

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
    
    cargarFlash();
    
    cargarCurar();

}

Hud::Hud(const Hud& orig) {
}



void Hud::renderHud(sf::Time elapsedTime,bool inPause) {

    if(!inPause){
        cRayo1->update(elapsedTime);
        cRayo2->update(elapsedTime);
        cAgua1->update(elapsedTime);
        cAgua2->update(elapsedTime);
        cFuego1->update(elapsedTime);
        cFuego2->update(elapsedTime);
        cCurar->update(elapsedTime);
        cFlash->update(elapsedTime);
    }
    m->draw(barraVida);
    m->draw(sVida);

    cRayo2->draw();
    cRayo1->draw();
    cAgua1->draw();
    cAgua2->draw();
    cFuego1->draw();
    cFuego2->draw();
    cCurar->draw();
    cFlash->draw();

    m->draw(fBlanco);
    if(activo==1){
        m->draw(fuegoBueno);
    }else{
        m->draw(fuegoB);
    }
    m->draw(fSombra);
    m->draw(fGlare);

    m->draw(rBlanco);
    if(activo==2){
        m->draw(rayoBueno);
    }else{
        m->draw(rayoB);
    }
    m->draw(rSombra);
    m->draw(rGlare);

    m->draw(aBlanco);
    if(activo==3){
        m->draw(aguaBueno);
    }else{
        m->draw(aguaB);
    }
    m->draw(aSombra);
    m->draw(aGlare);
    
    m->draw(cuBlanco);
    m->draw(curarBueno);
    m->draw(cuSombra);
    m->draw(cuGlare);
    
    m->draw(flBlanco);
    m->draw(flashBueno);
    m->draw(flSombra);
    m->draw(flGlare);
}

void Hud::cambiaHechizo(int activar) {
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
    
    rayoB = new Sprite();
    rBlanco = new Sprite();
    rayoBueno = new Sprite();
    rGlare = new Sprite();
    rSombra = new Sprite();
    
    rayoB->setTexture("resources/Textures/hud/rayoB.png",true);
    rayoB->setOrigin(rayoB->getTextureSize().x / 2, rayoB->getTextureSize().y / 2);
    rayoB->setPosition(500,910);
    rayoB->setScale(0.3,0.4);
    
    rBlanco->setTexture("resources/Textures/hud/blanco.png", true);
    rBlanco->setOrigin(rBlanco->getTextureSize().x / 2, rBlanco->getTextureSize().y / 2);
    rBlanco->setPosition(500, 910);
    rBlanco->setScale(0.3, 0.4);
    
    rayoBueno->setTexture("resources/Textures/hud/rayo.png", true);
    rayoBueno->setOrigin(rayoBueno->getTextureSize().x / 2, rayoBueno->getTextureSize().y / 2);
    rayoBueno->setPosition(500, 910);
    rayoBueno->setScale(0.3, 0.4);
    
    rGlare->setTexture("resources/Textures/hud/glare.png", true);
    rGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    rGlare->setPosition(500, 910);
    rGlare->setScale(0.3, 0.4);
    
    rSombra->setTexture("resources/Textures/hud/sombra.png", true);
    rSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    rSombra->setPosition(500, 910);
    rSombra->setScale(0.3, 0.4);
}

void Hud::cargarAgua() {

    aguaB = new Sprite();
    aBlanco = new Sprite();
    aguaBueno = new Sprite();
    aGlare = new Sprite();
    aSombra = new Sprite();

    aguaB->setTexture("resources/Textures/hud/aguaB.png",true);
    aguaB->setOrigin(aguaB->getTextureSize().x/2,aguaB->getTextureSize().y/2);
    aguaB->setPosition(600,910);
    aguaB->setScale(0.3,0.4);
    
    aBlanco->setTexture("resources/Textures/hud/blanco.png", true);
    aBlanco->setOrigin(aBlanco->getTextureSize().x / 2, aBlanco->getTextureSize().y / 2);
    aBlanco->setPosition(600, 910);
    aBlanco->setScale(0.3, 0.4);

    aguaBueno->setTexture("resources/Textures/hud/agua.png", true);
    aguaBueno->setOrigin(aguaBueno->getTextureSize().x / 2, aguaBueno->getTextureSize().y / 2);
    aguaBueno->setPosition(600, 910);
    aguaBueno->setScale(0.3, 0.4);

    aGlare->setTexture("resources/Textures/hud/glare.png", true);
    aGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    aGlare->setPosition(600, 910);
    aGlare->setScale(0.3, 0.4);

    aSombra->setTexture("resources/Textures/hud/sombra.png", true);
    aSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    aSombra->setPosition(600, 910);
    aSombra->setScale(0.3, 0.4);
}

void Hud::cargarCurar() {
    cuBlanco = new Sprite();
    curarBueno = new Sprite();
    cuGlare = new Sprite();
    cuSombra = new Sprite();
    
    cuBlanco->setTexture("resources/Textures/hud/blanco.png", true);
    cuBlanco->setOrigin(rBlanco->getTextureSize().x / 2, rBlanco->getTextureSize().y / 2);
    cuBlanco->setPosition(300, 920);
    cuBlanco->setScale(0.2, 0.25);

    curarBueno->setTexture("resources/Textures/hud/curar.png", true);
    curarBueno->setOrigin(rayoBueno->getTextureSize().x / 2, rayoBueno->getTextureSize().y / 2);
    curarBueno->setPosition(300, 920);
    curarBueno->setScale(0.2, 0.25);

    cuGlare->setTexture("resources/Textures/hud/glare.png", true);
    cuGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    cuGlare->setPosition(300, 920);
    cuGlare->setScale(0.2, 0.25);

    cuSombra->setTexture("resources/Textures/hud/sombra.png", true);
    cuSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    cuSombra->setPosition(300, 920);
    cuSombra->setScale(0.2, 0.25);
}

void Hud::resetCurar() {
    cCurar->reset();
}


void Hud::resetAgua2() {
    cAgua2->reset();
}

void Hud::resetAgua1() {
    cAgua1->reset();
}

void Hud::resetFuego1() {
    cFuego1->reset();
}

void Hud::resetFuego2() {
    cFuego2->reset();
}
void Hud::resetRayo2() {
    cRayo2->reset();
}

void Hud::resetRayo1() {
    cRayo1->reset();
}

void Hud::resetFlash() {
    cFlash->reset();
}


void Hud::cargarFuego() {
    fuegoB = new Sprite();
    fBlanco = new Sprite();
    fuegoBueno = new Sprite();
    fGlare = new Sprite();
    fSombra = new Sprite();

    fuegoB->setTexture("resources/Textures/hud/fuegoB.png",true);
    fuegoB->setOrigin(rBlanco->getTextureSize().x / 2, rBlanco->getTextureSize().y / 2);
    fuegoB->setPosition(400,910);
    fuegoB->setScale(0.3,0.4);
    
    fBlanco->setTexture("resources/Textures/hud/blanco.png", true);
    fBlanco->setOrigin(rBlanco->getTextureSize().x / 2, rBlanco->getTextureSize().y / 2);
    fBlanco->setPosition(400, 910);
    fBlanco->setScale(0.3, 0.4);

    fuegoBueno->setTexture("resources/Textures/hud/fuego.png", true);
    fuegoBueno->setOrigin(rayoBueno->getTextureSize().x / 2, rayoBueno->getTextureSize().y / 2);
    fuegoBueno->setPosition(400, 910);
    fuegoBueno->setScale(0.3, 0.4);

    fGlare->setTexture("resources/Textures/hud/glare.png", true);
    fGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    fGlare->setPosition(400, 910);
    fGlare->setScale(0.3, 0.4);

    fSombra->setTexture("resources/Textures/hud/sombra.png", true);
    fSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    fSombra->setPosition(400, 910);
    fSombra->setScale(0.3, 0.4);
}

void Hud::cargarFlash(){
    flashBueno = new Sprite();
    flBlanco = new Sprite();
    flGlare = new Sprite();
    flRayo = new Sprite();
    flSombra = new Sprite();
    
    flBlanco->setTexture("resources/Textures/hud/blanco.png", true);
    flBlanco->setOrigin(rBlanco->getTextureSize().x / 2, rBlanco->getTextureSize().y / 2);
    flBlanco->setPosition(700, 920);
    flBlanco->setScale(0.2, 0.25);

    flashBueno->setTexture("resources/Textures/hud/flash.png", true);
    flashBueno->setOrigin(rayoBueno->getTextureSize().x / 2, rayoBueno->getTextureSize().y / 2);
    flashBueno->setPosition(700, 920);
    flashBueno->setScale(0.2, 0.25);

    flGlare->setTexture("resources/Textures/hud/glare.png", true);
    flGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    flGlare->setPosition(700, 920);
    flGlare->setScale(0.2, 0.25);

    flSombra->setTexture("resources/Textures/hud/sombra.png", true);
    flSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    flSombra->setPosition(700, 920);
    flSombra->setScale(0.2, 0.25);
}


Hud::~Hud() {
    delete cRayo1;
    delete cRayo2;
    delete cAgua1;
    delete cAgua2;
    delete cFuego1;
    delete cFuego2;

    delete rayoBueno;
    delete rBlanco;
    delete rGlare;
    delete rSombra;
    
    //Agua
    delete aguaBueno;
    delete aBlanco;
    delete aGlare;
    delete aSombra;

    //Fuego
    delete fuegoBueno;
    delete fBlanco;
    delete fGlare;
    //delete fRayo;
    delete fSombra;
    
    /*delete mCds;
    delete m;*/
    m = nullptr;
    delete curarBueno;

}