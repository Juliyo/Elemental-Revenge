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
    cAgua1 = new ProgressBar(120, 150, sf::Vector2f(1600, 1500), mCoolDowns[2], 1, sf::Vector2f(0.5,0.6),sf::Color::Yellow);
    
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

    mouseLeftG.loadFromFile("resources/Textures/leftMouseG.png");
    mouseRightG.loadFromFile("resources/Textures/rightMouseG.png");

    aguaT.loadFromFile("resources/Textures/hudAgua.png");
    rayoT.loadFromFile("resources/Textures/hudRayo.png");
    fuegoT.loadFromFile("resources/Textures/hudFuego.png");

    aguaGris.loadFromFile("resources/Textures/hudAguaG.png");
    rayoGris.loadFromFile("resources/Textures/hudRayoG.png");
    fuegoGris.loadFromFile("resources/Textures/hudFuegoG.png");

    agua.setTexture(aguaGris);
    rayo.setTexture(rayoT);
    fuego.setTexture(fuegoGris);

    agua.setPosition(20, 735);
    agua.setScale(0.5f, 0.6f);

    rayo.setPosition(20 + 50, 740 + rayo.getTextureSize().y * 0.6);
    rayo.setScale(0.5f, 0.6f);

    fuego.setPosition(20, 745 + (rayo.getTextureSize().y * 2)*0.6);
    fuego.setScale(0.5f, 0.6f);

    cdRayo1 = new Text();
    cdRayo1->setFont("resources/Fonts/Sansation.ttf");
    cdRayo1->setString(toString((mCoolDowns[0] - mCds[0].getTiempo())));
    cdRayo1->setPosition(156, 847);
    cdRayo1->setScale(0.6, 0.6);

    cdRayo2 = new Text();
    cdRayo2->setFont("resources/Fonts/Sansation.ttf");
    cdRayo2->setString(toString((mCoolDowns[1] - mCds[1].getTiempo())));
    cdRayo2->setPosition(190, 847);
    cdRayo2->setScale(0.6, 0.6);

    draws = new bool[6];
    for (int i = 0; i < 6; i++) {
        draws[i] = true;
    }
    for (int i = 0; i < 3; ++i) {
        arrLeftMouse[i] = new Sprite("resources/Textures/leftMouse.png", true);
        arrRightMouse[i] = new Sprite("resources/Textures/rightMouse.png", true);
        arrLeftMouse[i]->setScale(0.6, 0.6);
        arrRightMouse[i]->setScale(0.6, 0.6);
    }
    //Agua


    //Rayo
    arrLeftMouse[1]->setPosition(161, 848);
    arrRightMouse[1]->setPosition(191, 848);
    //Fuego

    activo = 2;

    //calculaRayo2();
    cargarRayo();

    //calculaAgua2();
    //calculaAgua1();
    cargarAgua();

}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

void Hud::renderHud(sf::Time elapsedTime) {
    //renderRayo1();
    //renderRayo2();
    //renderAgua1(elapsedTime);
    cRayo1->update(elapsedTime);
    cRayo2->update(elapsedTime);
    cAgua1->update(elapsedTime);
    
    m->draw(barraVida);
    m->draw(sVida);
    m->draw(agua);
    m->draw(rayo);
    m->draw(fuego);

    cRayo2->draw();
    cRayo1->draw();
    cAgua1->draw();

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
            agua.setPosition(20, 735);
            agua.setTexture(aguaGris);
            break;
        case 2:
            rayo.setPosition(20, 740 + rayo.getTextureSize().y * 0.6);
            rayo.setTexture(rayoGris);
            break;
        case 1:
            fuego.setPosition(20, 745 + (rayo.getTextureSize().y * 2)*0.6);
            fuego.setTexture(fuegoGris);
            break;
        default:
            break;
    }
    switch (activar) {
        case 3:
            agua.setPosition(20 + 50, 735);
            agua.setTexture(aguaT);
            activo = 3;
            break;
        case 2:
            rayo.setPosition(20 + 50, 740 + rayo.getTextureSize().y * 0.6);
            rayo.setTexture(rayoT);
            activo = 2;
            break;
        case 1:
            fuego.setPosition(20 + 50, 745 + (rayo.getTextureSize().y * 2)*0.6);
            fuego.setTexture(fuegoT);
            activo = 1;
            break;
        default:
            break;
    }
}

void Hud::Update() {
    //std::cout<<Motor2D::Instance()->getMousePosition().x<<", "<<Motor2D::Instance()->getMousePosition().y<<std::endl;
    float tRayo1 = mCoolDowns[0] - mCds[0].getTiempo();
    float tRayo2 = mCoolDowns[1] - mCds[1].getTiempo();

    std::stringstream ss;
    std::stringstream s2;

    ss << std::fixed << std::setprecision(1) << tRayo1;
    s2 << std::fixed << std::setprecision(1) << tRayo2;

    if (tRayo1 <= 0) {
        draws[0] = true;
    } else {
        cdRayo1->setString(ss.str());
        draws[0] = false;
    }
    if (tRayo2 <= 0) {
        draws[1] = true;
    } else {
        cdRayo2->setString(s2.str());
        draws[1] = false;
    }
}

void Hud::updateHud(float vidas) {
    sVida.setTextRect(130, 30, (289 - 130) / (15 / vidas), 58);
    std::string str;
    str = toString(vidas) + "/15";
    tVida.setString(str);
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

void Hud::calculaRayo1() {
}

void Hud::renderRayo1() {
}

void Hud::calculaRayo2() {

}

void Hud::renderRayo2() {
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
    aBlanco->setPosition(800, 900);
    aBlanco->setScale(0.5, 0.6);

    aguaBueno->setTexture("resources/Textures/hud/agua.png", true);
    aguaBueno->setOrigin(rayoBueno->getTextureSize().x / 2, rayoBueno->getTextureSize().y / 2);
    aguaBueno->setPosition(800, 900);
    aguaBueno->setScale(0.5, 0.6);

    aGlare->setTexture("resources/Textures/hud/glare.png", true);
    aGlare->setOrigin(rGlare->getTextureSize().x / 2, rGlare->getTextureSize().y / 2);
    aGlare->setPosition(800, 900);
    aGlare->setScale(0.5, 0.6);

    aSombra->setTexture("resources/Textures/hud/sombra.png", true);
    aSombra->setOrigin(rSombra->getTextureSize().x / 2, rSombra->getTextureSize().y / 2);
    aSombra->setPosition(800, 900);
    aSombra->setScale(0.5, 0.6);
}

void Hud::calculaAgua1() {
    //60
    //105*0.03 / 60 = 0.052
    m_frameTime = sf::seconds((3/150.f));
    m_currentTime = sf::Time::Zero;


    sf::Vector2f centro(1600, 1500);
    triangleAgua1.clear();
    triangleAgua1.setPrimitiveType(sf::TrianglesFan);
    triangleAgua1.append(centro);
    triangleAgua1[0].color = sf::Color::Green;

    double radius = 120;
    const double PI = 3.14159265359;
    iAgua1 = 0;
    for (double angle = 2 * PI; angle >= PI; angle -= 0.021) {
        sf::Vector2f p(centro.x + radius * sin(angle), centro.y + radius * cos(angle));
        arrayPts1.push_back(p);
        iAgua1++;
    }
    //    std::cout<<"Direccion memoria arrayPts1: "<<arrayPts1<<std::endl;
    //    std::cout<<"Direccion memoria arrayPts1[0]: "<<&arrayPts1[0]<<std::endl;
    //    std::cout<<"Direccion memoria arrayPts2: "<<arrayPts2<<std::endl;
    //    std::cout<<"Direccion memoria arrayPts2[0]: "<<&arrayPts2[0]<<std::endl;
    iAgua1 = 1;
}

void Hud::renderAgua1(sf::Time elapsedTime) {
    if (firstAgua1) {

        // add delta time
        m_currentTime += elapsedTime;

        // if current time is bigger then the frame time advance one frame
        if (m_currentTime >= m_frameTime) {
            // reset time, but keep the remainder
            m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());

            // get next Frame index
            if (iAgua1 + 1 < 150) {
                iAgua1++;
            }
            triangleAgua1.append(arrayPts1.at(iAgua1));
            triangleAgua1[iAgua1].color = sf::Color::Green;
            triangleAgua1[iAgua1].color.a = 200;

        }
    }
}

void Hud::resetAgua1() {
    cAgua1->reset();
}

void Hud::calculaAgua2() {

}

void Hud::renderAgua2() {

}

void Hud::cargarFuego() {

}

void Hud::calculaFuego1() {

}

void Hud::renderFuego1() {

}

void Hud::calculaFuego2() {

}

void Hud::renderFuego2() {

}
