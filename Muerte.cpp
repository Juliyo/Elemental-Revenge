/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Muerte.cpp
 * Author: kike
 * 
 * Created on 13 de abril de 2016, 18:20
 */
#include <iostream>
#include <string>
#include "Muerte.hpp"
#include "Window.hpp"

Muerte::Muerte() {

    mWindow = ref.GetWindow();
    float width = 1280;
    float height = 700;




    //Vista
    mWorldView = mWindow->getDefaultView();
    mWorldView.zoom(0.5f);
    if (!fontMuerte.loadFromFile("resources/Fonts/OptimusPrinceps.ttf")) {

    }
textoMuerte.setFont(fontMuerte);
    textoMuerte.setColor(sf::Color::Red);
    textoMuerte.setString("HAS MUERTO");
    textoMuerte.setOrigin(sf::Vector2f(textoMuerte.getGlobalBounds().width/2, textoMuerte.getGlobalBounds().height/2));
    textoMuerte.setPosition(sf::Vector2f(mWindow->getSize().x/2, mWindow->getSize().y/2));
    textoMuerte.scale(2,2);
    
    animation = new Animation(); //para el fondo SOLO declarado

    //Estado de Ingame
    EstadoActivo = false;

    //Referenciamos la ventana Singleton


    //texturas

    try {
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaFondo.loadFromFile("resources/Textures/fondo.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
        texturaPersonaje.loadFromFile("resources/Textures/fondoPersonaje.png");

    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setScale(0.2, 0.2);
    mouseSprite.setPosition(20, 20);
    mouseSprite.setOrigin(64, 64);

    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 1280, 720));
    spriteFondo.setOrigin(spriteFondo.getTextureRect().width / 2, spriteFondo.getTextureRect().height / 2);
    spriteFondo.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2);
    transparent.a = 150;
    spriteFondo.setColor(transparent);
    
    spriteRelleno.setTexture(texturaFondo);
    spriteRelleno.setTextureRect(sf::IntRect(0, 0, 1280, 100));
    spriteRelleno.setOrigin(spriteRelleno.getTextureRect().width / 2, spriteRelleno.getTextureRect().height / 2);
    spriteRelleno.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2+20);
    transparent.a = 200;
    spriteRelleno.setColor(transparent);
}


Muerte::Muerte(const Muerte& orig) {
}

Muerte::~Muerte() {
}

void Muerte::Update(sf::Time elapsedTime) {
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
}
void Muerte::render(float interpolation, sf::Time elapsedTime) {
    //mWindow->clear()
    updateView();
    mWindow->draw(spriteFondo);
    mWindow->draw(spriteRelleno);
    mWindow->draw(textoMuerte);
    mWindow->display();
}
void Muerte::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left) {
        if (isPressed) {
            buttonPressed = isPressed;
        }
    }
}

sf::View Muerte::getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight) {
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
void Muerte::updateView() {
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