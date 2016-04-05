/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transition.cpp
 * Author: joselu
 * 
 * Created on 26 de marzo de 2016, 19:50
 */

#include "Transition.hpp"
#include "Window.hpp"
#include "btree.hpp"
#include <iostream>
#include <string>
#include "tinystr.h"
#include "tinyxml.h"

Transition::Transition() {
    
    //Estado de Ingame
    EstadoActivo = false;
    
    mWindow = ref.GetWindow();
    
    mWorldView = mWindow->getDefaultView();
    mWorldView.zoom(0.5f);
    
    
    TiXmlDocument doc;
    doc.LoadFile("resources/historia.xml");
    TiXmlElement* pregunta1 = doc.FirstChildElement("pregunta");
    TiXmlElement* respuesta1 = doc.FirstChildElement("respuesta1");
    TiXmlElement* respuesta2 = doc.FirstChildElement("respuesta2");
    
    std::string p1=pregunta1->GetText();
    std::string r1=respuesta1->GetText();
    std::string r2=respuesta2->GetText();
    int key;
    pregunta1->Attribute( "id", &key );
    int c=0;
    std::string torep="\n";
    for ( std::string::iterator it=p1.begin(); it!=p1.end(); ++it){
        if(*it=='%'){
            p1=p1.replace(c,1,torep);
        }
        c++;
    }
    
    arbol = new btree();
    /*char ch = 202;
    std::string hola = "ch boludo";
    hola.push_back(233);*/
    arbol->insert(key,p1,respuesta1->GetText(),respuesta2->GetText());
    
    for(int i=0; i<6; i++){
       pregunta1=pregunta1->NextSiblingElement("pregunta");
       respuesta1=respuesta1->NextSiblingElement("pregunta");
       respuesta2=respuesta2->NextSiblingElement("pregunta");
       pregunta1->Attribute( "id", &key );
       arbol->insert(key,pregunta1->GetText(),respuesta1->GetText(),respuesta2->GetText());
    }
    
     try {
        texPregunta.loadFromFile(arbol->search(4)->pregunta);
        texturaOpcionA.loadFromFile("resources/UI Elements/colgante.png");
        texturaOpcionB.loadFromFile("resources/UI Elements/amuleto.png");
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaFondo.loadFromFile("resources/Textures/fondo.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
        cruzeta.loadFromFile("resources/UI Elements/cruzetas.png");
    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 2000, 2000));
    
    pregunta.setTexture(texPregunta);
    spriteOpcionA.setTexture(texturaOpcionA);
    spriteOpcionB.setTexture(texturaOpcionB);

   
    
    spriteRelleno.setTexture(texturaRelleno);
    spriteRelleno.setTextureRect(sf::IntRect(0, 0, 1024, 2048));
    spriteRelleno.setScale(1, 2);
    
    pregunta.setScale(0.6,0.6);
    pregunta.setOrigin(texPregunta.getSize().x/2,texPregunta.getSize().y/2);
    pregunta.setPosition(mWindow->getSize().x/2,mWindow->getSize().y/2-100);
    
    spriteOpcionA.setScale(0.8,0.8);
    spriteOpcionA.setOrigin(texturaOpcionA.getSize().x/2,texturaOpcionA.getSize().y/2);
    
    spriteOpcionA.setPosition(500,450);
    spriteOpcionA.setTextureRect(sf::IntRect(0,0,144,62));
    
    spriteOpcionB.setScale(0.8,0.8);
    spriteOpcionB.setOrigin(texturaOpcionB.getSize().x/2,texturaOpcionB.getSize().y/2);
    spriteOpcionB.setPosition(800,450);
    spriteOpcionB.setTextureRect(sf::IntRect(0,0,144,62));

    
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setScale(0.2, 0.2);
    mouseSprite.setPosition(20, 20);
    mouseSprite.setOrigin(64, 64);

    cruzeta1.setTexture(cruzeta);
    cruzeta1.setOrigin(cruzeta.getSize().x/2,cruzeta.getSize().y/2);
    cruzeta1.setScale(0.25,0.25);
    
    
    
        

}

Transition::Transition(const Transition& orig) {
}

Transition::~Transition() {
}


void Transition::Update(sf::Time elapsedTime){
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    if(isPointOverSprite(mousePosition, spriteOpcionA)){
        cruzeta1.setPosition(spriteOpcionA.getPosition());
        Bcruzeta=true;
    }else if(isPointOverSprite(mousePosition, spriteOpcionB)){
        cruzeta1.setPosition(spriteOpcionB.getPosition());
        Bcruzeta=true;
    }else{
        Bcruzeta=false;
    }
    
}

bool Transition::isPointOverSprite(const sf::Vector2f Position, const sf::Sprite &Sprite)
{
	return	(Position.x > Sprite.getPosition().x - Sprite.getLocalBounds().width/2) && (Position.x < Sprite.getPosition().x + Sprite.getLocalBounds().width/2 ) && 
			(Position.y > Sprite.getPosition().y - Sprite.getLocalBounds().height/2) && (Position.y < Sprite.getPosition().y + Sprite.getLocalBounds().height/2 );
}

void Transition::render(float interpolation, sf::Time elapsedTime){
    
    mWindow->clear();

    //Pillamos la view anterior, activamos la del fondo, dibujamos el fondo y volvemos al estado anterior
    sf::View previa = mWindow->getView();
    mWindow->setView(mBackgroundView);
    mWindow->draw(spriteRelleno);
    mWindow->setView(previa);

    updateView();
    mWindow->draw(spriteFondo);
    mWindow->draw(pregunta);

    mWindow->draw(textoPregunta);
    mWindow->draw(spriteOpcionA);
    mWindow->draw(spriteOpcionB);
    if(Bcruzeta){
        mWindow->draw(cruzeta1);
    }

    previa = mWindow->getView();

    mWindow->setView(getLetterboxView(mHud, ref.ancho, ref.alto, 640, 480));
    mWindow->setView(previa);

    
    mWindow->draw(mouseSprite);
    // mWindow.draw(mStatisticsText);
    mWindow->display();
}


sf::View Transition::getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = viewRatioWidth / (float) viewRatioHeight;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;

        posX = (1 - sizeX) / 2.0;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.0;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}


void Transition::updateView() {

    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

    sf::Vector2f position = mousePosition;
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);

    mouseSprite.setPosition(position);

    mWorldView.setSize(640, 480);

    mWindow->setView(getLetterboxView(mWorldView, ref.ancho, ref.alto, 640, 480));
}

void Transition::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left) {
        if(isPressed){
            if(spriteOpcionA.getGlobalBounds().contains(mouseSprite.getPosition())){
                printf("FDSAF");
            }
        }
    }

}