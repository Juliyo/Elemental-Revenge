/* 
 * File:   Hud.cpp
 * Author: tonir
 * 
 * Created on 11 de marzo de 2016, 13:12
 */


#include "StringHelpers.hpp"
#include "Hud.hpp"
#include "Motor/Sprite.hpp"
#include <iomanip>
Hud::Hud(Reloj *cds, float *coolDowns) {
    mCds = cds;
    mCoolDowns = coolDowns;
    
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
    sVida.setPosition(20+(130*0.6), 15+(30*0.7));
    
    sVida.setTextRect(130, 30, (289-130), 58);
    
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
    
    agua.setPosition(20,735);
    agua.setScale(0.5f,0.6f);
    
    rayo.setPosition(20+50,740+rayo.getTextureSize().y*0.6);
    rayo.setScale(0.5f,0.6f);
    
    fuego.setPosition(20,745+(rayo.getTextureSize().y*2)*0.6);
    fuego.setScale(0.5f,0.6f);
    
    cdRayo1 = new Text();
    cdRayo1->setFont("resources/Fonts/Sansation.ttf");
    cdRayo1->setString(toString((mCoolDowns[0] - mCds[0].getTiempo())));
    cdRayo1->setPosition(156,847);
    cdRayo1->setScale(0.6,0.6);
    
    cdRayo2 = new Text();
    cdRayo2->setFont("resources/Fonts/Sansation.ttf");
    cdRayo2->setString(toString((mCoolDowns[1] - mCds[1].getTiempo())));
    cdRayo2->setPosition(190,847);
    cdRayo2->setScale(0.6,0.6);
    
    draws = new bool[6];
    for(int i = 0;i<6;i++){
        draws[i] = true;
    }
    
    for(int i = 0;i<3;++i){
        arrLeftMouse[i] = new Sprite("resources/Textures/leftMouse.png",true);
        arrRightMouse[i] = new Sprite("resources/Textures/rightMouse.png",true);
        arrLeftMouse[i]->setScale(0.6,0.6);
        arrRightMouse[i]->setScale(0.6,0.6);
    }
    //Agua
    
    
    //Rayo
    arrLeftMouse[1]->setPosition(161,848);
    arrRightMouse[1]->setPosition(191,848);
    //Fuego
    
    activo = 2;
    maskCircle1.setFillColor(sf::Color::Magenta);
    maskCircle1.setPosition(agua.getPosition());
    maskCircle1.setRadius(10);
    maskCircle2.setRadius(10);
    maskCircle3.setRadius(10);
    maskCircle2.setFillColor(sf::Color::Magenta);
    maskCircle2.setPosition(rayo.getPosition());
    maskCircle3.setFillColor(sf::Color::Magenta);
    maskCircle3.setPosition(fuego.getPosition());
    
    
    
    rBlanco.setTexture("resources/Textures/hud/blanco.png");
    rBlanco.setPosition(200,200);
    rBlanco.setScale(1,1.2);
    rayoBueno.setTexture("resources/Textures/hud/rayo.png");
    rayoBueno.setPosition(200,200);
    rayoBueno.setScale(1,1.2);
    rFondo.setTexture("resources/Textures/hud/fondo.png");
    rFondo.setPosition(200,200);
    rFondo.setScale(1,1.2);
    rGlare.setTexture("resources/Textures/hud/glare.png");
    rGlare.setPosition(200,200);
    rGlare.setScale(1,1.2);
    rSombra.setTexture("resources/Textures/hud/sombra.png");
    rSombra.setPosition(200,200);
    rSombra.setScale(1,1.2);
    
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

void Hud::renderHud() {
    Motor2D *m = Motor2D::Instance();
    sf::Texture txt;
    sf::Image img;
    img = rFondo.getSfTexture().copyToImage();
    img.createMaskFromColor(sf::Color::Cyan);
    rTexture.clear();
    txt.loadFromImage(img);
    rFondo.setTexture(txt);

    m->draw(barraVida);
    m->draw(sVida);
    m->draw(agua);
    m->draw(rayo);
    m->draw(fuego);
    if(draws[0]){
        m->draw(arrLeftMouse[1]);
    }else{
        m->draw(*cdRayo1);
    }
    if(draws[1]){
        m->draw(arrRightMouse[1]);
    }else{
        m->draw(*cdRayo2);
    }
    
    m->draw(rFondo,sf::BlendMultiply);
    m->draw(rBlanco);
    m->draw(rayoBueno);
    m->draw(rSombra);
    m->draw(rGlare);
}


void Hud::cambiaHechizo(int activar) {
    switch(activo){
        case 3:
            agua.setPosition(20,735);
            agua.setTexture(aguaGris);
            break;
        case 2:
            rayo.setPosition(20,740+rayo.getTextureSize().y*0.6);
            rayo.setTexture(rayoGris);
            break;
        case 1:
            fuego.setPosition(20,745+(rayo.getTextureSize().y*2)*0.6);
            fuego.setTexture(fuegoGris);
            break;
    }
    
    switch(activar){
        case 3:
            agua.setPosition(20+50,735);
            agua.setTexture(aguaT);
            activo = 3;
            break;
        case 2:
            rayo.setPosition(20+50,740+rayo.getTextureSize().y*0.6);
            rayo.setTexture(rayoT);
            activo = 2;
            break;
        case 1:
            fuego.setPosition(20+50,745+(rayo.getTextureSize().y*2)*0.6);
            fuego.setTexture(fuegoT);
            activo = 1;
            break;
    }
}

void Hud::Update(){
    
    float tRayo1 = mCoolDowns[0] - mCds[0].getTiempo();
    float tRayo2 = mCoolDowns[1] - mCds[1].getTiempo();
    
    std::stringstream ss;
    std::stringstream s2;
    
    ss << std::fixed <<std::setprecision(1)<<tRayo1;
    s2 << std::fixed <<std::setprecision(1)<<tRayo2;

    if(tRayo1<=0){
        draws[0] = true;
    }else{
        cdRayo1->setString(ss.str());
        draws[0] = false;
    }
    if(tRayo2<=0){
        draws[1] = true;
    }else{
        cdRayo2->setString(s2.str());
        draws[1] = false;
    }
    
    //ss.clear();
}
void Hud::updateHud(float vidas) {
    sVida.setTextRect(130, 30, (289-130)/(15/vidas), 58);
    std::string str;
    str = toString(vidas) + "/15";
    tVida.setString(str);
}

