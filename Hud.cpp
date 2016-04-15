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
    mCds = cds;
    mCoolDowns = coolDowns;

    arrayPts = new sf::Vector2f[20]; //Fuego 1
    arrayPts1 = new sf::Vector2f[50]; //Agua 1
    arrayPts2 = new sf::Vector2f[100]; //Rayo 1
    arrayPts3 = new sf::Vector2f[250]; // Agua 2
    arrayPts4 = new sf::Vector2f[250]; // Fuego 2
    arrayPts5 = new sf::Vector2f[150]; // Rayo 2

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
    cargarRayo();
    calculaRayo2();
    iRayo2 = 0;
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

void Hud::renderHud() {

    renderRayo2();
    Motor2D *m = Motor2D::Instance();

    m->draw(barraVida);
    m->draw(sVida);
    m->draw(agua);
    m->draw(rayo);
    m->draw(fuego);
    if (draws[0]) {
        m->draw(arrLeftMouse[1]);
    } else {
        m->draw(*cdRayo1);
    }
    if (draws[1]) {
        m->draw(arrRightMouse[1]);
    } else {
        m->draw(*cdRayo2);
    }
    sf::Transform transform;
    transform.scale(1, 1.2);
    sf::RenderStates st;
    st.transform = transform;
    m->draw(triangleRayo2, st);
    m->draw(rBlanco);
    m->draw(rayoBueno);
    m->draw(rSombra);
    m->draw(rGlare);

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
    std::cout << "tRayo1: " << tRayo1 << std::endl;
}

void Hud::updateHud(float vidas) {
    sVida.setTextRect(130, 30, (289 - 130) / (15 / vidas), 58);
    std::string str;
    str = toString(vidas) + "/15";
    tVida.setString(str);
}

void Hud::cargarRayo() {
    rBlanco.setTexture("resources/Textures/hud/blanco.png", true);
    rBlanco.setOrigin(rBlanco.getTextureSize().x / 2, rBlanco.getTextureSize().y / 2);
    rBlanco.setPosition(200, 200);
    rBlanco.setScale(1, 1.2);
    rayoBueno.setTexture("resources/Textures/hud/rayo.png", true);
    rayoBueno.setOrigin(rayoBueno.getTextureSize().x / 2, rayoBueno.getTextureSize().y / 2);
    rayoBueno.setPosition(200, 200);
    rayoBueno.setScale(1, 1.2);
    rGlare.setTexture("resources/Textures/hud/glare.png", true);
    rGlare.setOrigin(rGlare.getTextureSize().x / 2, rGlare.getTextureSize().y / 2);
    rGlare.setPosition(200, 200);
    rGlare.setScale(1, 1.2);
    rSombra.setTexture("resources/Textures/hud/sombra.png", true);
    rSombra.setOrigin(rSombra.getTextureSize().x / 2, rSombra.getTextureSize().y / 2);
    rSombra.setPosition(200, 200);
    rSombra.setScale(1, 1.2);
}

void Hud::calculaRayo1() {

}

void Hud::renderRayo1() {

}

void Hud::calculaRayo2() {
    //150
    //105*0.03 / 150 = 0.021
    sf::Vector2f punto(200, 165);
    triangleRayo2.setPrimitiveType(sf::TrianglesFan);
    triangleRayo2.append(punto);
    triangleRayo2[0].color = sf::Color::Green;

    sf::Vector2f centro(200, 165);
    double radius = 120;
    const double PI = 3.14159265359;
    iRayo2 = 0;
    for (double angle = 0; angle <= PI; angle += 0.021) {
        sf::Vector2f p(centro.x + radius * sin(angle), centro.y + radius * cos(angle));
        arrayPts5[iRayo2] = p;
        iRayo2++;
    }
    //sf::Vector2f v(arrayPts5[0].x, (arrayPts5[0].y)-(2*radius));
    //arrayPts5[250] = v;
    iRayo2 = 0;
}

void Hud::renderRayo2() {
    // 20/150 = 0.13
    if (r2.getTiempo() >= 0.13) {

        if (iRayo2 < 150) {
            triangleRayo2.append(arrayPts5[iRayo2]);
            triangleRayo2[iRayo2].color = sf::Color::Green;
            triangleRayo2[iRayo2].color.a = 200;
        }
        r2.restart();
        iRayo2++;
    } 

}

void Hud::resetRayo2() {
    triangleRayo2.clear();
    sf::Vector2f punto(200, 165);
    triangleRayo2.append(punto);
    triangleRayo2[0].color = sf::Color::Green;
    iRayo2 = 0;
    r2.restart();
}

void Hud::cargarAgua() {

}

void Hud::calculaAgua1() {
    sf::Vector2f punto(478, 502);
    triangleRayo2.setPrimitiveType(sf::TrianglesFan);
    triangleRayo2.append(punto);
    triangleRayo2[0].color = sf::Color::Green;

    sf::Vector2f centro(478, 502);
    double radius = 120;
    const double PI = 3.14159265359;
    i = 0;
    for (double angle = 0; angle <= PI; angle += 0.063) {
        sf::Vector2f p(centro.x + radius * sin(angle), centro.y + radius * cos(angle));
        //triangleRayo2.append(p);
        arrayPts1[i] = p;
        i++;
    }
    sf::Vector2f v(arrayPts1[0].x, (arrayPts1[0].y)-(2 * radius));
    arrayPts1[50] = v;
    i = 0;
}

void Hud::renderAgua1() {
    if (r2.getTiempo() > 0.15) {
        r2.restart();
        if (i < 50) {
            triangleRayo2.append(arrayPts1[i]);
            triangleRayo2[i].color = sf::Color::Green;
            triangleRayo2[i].color.a = 200;
            i++;
        }
        if (i == 50) {
            sf::Vector2f v(arrayPts1[0].x, (arrayPts1[0].y)-(2 * 120));
            triangleRayo2.append(v);
            triangleRayo2[50].color = sf::Color::Green;
            triangleRayo2[50].color.a = 200;
        }
    }
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
