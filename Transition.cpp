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


Transition::Transition() {
    
    //Estado de Ingame
    EstadoActivo = false;
    
     try {
        texturaFondo.loadFromFile("resources/Textures/asesinatoMaestro.png");
        texturaOpcionA.loadFromFile("resources/Textures/colgante.png");
        texturaOpcionB.loadFromFile("resources/Textures/simbolo.png");
        contFonts.loadFromFile("resources/Fonts/Sansation.ttf");
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    spriteFondo.setTexture(texturaFondo);
    spriteOpcionA.setTexture(texturaOpcionA);
    spriteOpcionB.setTexture(texturaOpcionB);

    texturaRelleno.setSmooth(true);
    texturaRelleno.setRepeated(1);
    spriteRelleno.setTexture(texturaRelleno);
    spriteRelleno.setTextureRect(sf::IntRect(0, 0, 1024, 2048));
    spriteRelleno.setScale(1, 2);
    //spriteFondo.setTextureRect(sf::IntRect(0, 0, 2000, 2000));
    spriteFondo.setOrigin(320,240);
    spriteFondo.setPosition(640,360);
    
    spriteOpcionA.setScale(0.6,0.6);
    spriteOpcionA.setOrigin(0,0);
    spriteOpcionA.setPosition(400,450);    
    
    spriteOpcionB.setScale(0.6,0.6);
    spriteOpcionB.setOrigin(0,0);
    spriteOpcionB.setPosition(800,450);

    
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setScale(0.2, 0.2);
    mouseSprite.setPosition(20, 20);
    mouseSprite.setOrigin(64, 64);

    
    mWindow = ref.GetWindow();
    
    mWorldView = mWindow->getDefaultView();
    mWorldView.zoom(0.5f);
    
    /*TiXmlDocument doc;
    doc.LoadFile("resources/mapafinal2.tmx");
    TiXmlElement* map = doc.FirstChildElement("map");*/
    
    arbol = new btree();
    std::string pregunta = "Tu maestro ha sido asesinado y las únicas pistas son un símbolo en una hoja de papel y un amuleto, ¿qué pista debes seguir?";
    std::string r1 = "sdf";
    std::string r2 = "sdf";
    arbol->insert(1,pregunta,r1,r2);
    
    
    textoPregunta.setFont(contFonts);
    textoPregunta.setColor(sf::Color::Red);
    textoPregunta.setPosition(200,200);
    std::cout<<arbol->search(1)->pregunta<<std::endl;
    textoPregunta.setString(arbol->search(1)->pregunta);
}

Transition::Transition(const Transition& orig) {
}

Transition::~Transition() {
}


void Transition::Update(sf::Time elapsedTime){
    
    
    
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
    mWindow->draw(textoPregunta);
    mWindow->draw(spriteOpcionA);
    mWindow->draw(spriteOpcionB);

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