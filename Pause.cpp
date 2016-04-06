/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pause.cpp
 * Author: kike
 * 
 * Created on 6 de abril de 2016, 9:38
 */
#include <iostream>
#include <string>
#include "Pause.hpp"
#include "Window.hpp"

Pause::Pause(){
    
    
        mWindow = ref.GetWindow();

    //Vista
    mWorldView = mWindow->getDefaultView();
    mWorldView.zoom(0.5f);
        if(!fontPausa.loadFromFile("resources/Fonts/Minecraft.ttf")){
        
    }
    
    float width=mWindow->getSize().x;
    float height=mWindow->getSize().y;
    
    menuPausa[0].setFont(fontPausa);
    menuPausa[0].setColor(sf::Color::Red);
    menuPausa[0].setString("Play");
    menuPausa[0].setPosition(sf::Vector2f(width/2-50, height/(MAX_NUMBER_OF_ITEMS+1) *1.5));
    
    menuPausa[1].setFont(fontPausa);
    menuPausa[1].setColor(sf::Color::Blue);
    menuPausa[1].setString("Options");
    menuPausa[1].setPosition(sf::Vector2f(width/2-50, height/(MAX_NUMBER_OF_ITEMS+1) *2));
    
    
    menuPausa[2].setFont(fontPausa);
    menuPausa[2].setColor(sf::Color::Blue);
    menuPausa[2].setString("Exit");
    menuPausa[2].setPosition(sf::Vector2f(width/2-50, height/(MAX_NUMBER_OF_ITEMS+1) *2.5));
    
    
    menuPausa[3].setFont(fontPausa);
    menuPausa[3].setColor(sf::Color::Red);
    menuPausa[3].setString("OPTIONS");
    menuPausa[3].setPosition(sf::Vector2f(width/2-50, height/(MAX_NUMBER_OF_ITEMS+1) *1.5));
    
    selectedItemIndexPausa=0;
    
        //Reserva memoria
    //animatedSprite = new AnimatedSprite();
    animation = new Animation();//para el fondo SOLO declarado
    
    //Estado de Ingame
    EstadoActivo = false;

    //Referenciamos la ventana Singleton

    
    //texturas
    
        try {
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaFondo.loadFromFile("resources/Textures/fondo.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
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
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 500, 300));
    spriteFondo.setOrigin(spriteFondo.getTextureRect().width/2,spriteFondo.getTextureRect().height/2);
    spriteFondo.setPosition(mWindow->getSize().x/2,mWindow->getSize().y/2);

    spriteRelleno.setTexture(texturaRelleno);
    spriteRelleno.setTextureRect(sf::IntRect(0, 0, 1024, 2048));
    spriteRelleno.setScale(1, 2);
}
void Pause:: Update(sf::Time elapsedTime){
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
}
void Pause::render(float interpolation, sf::Time elapsedTime){
       //mWindow->clear();

    updateView();
    mWindow->draw(spriteFondo);
    mWindow->draw(mouseSprite);
    
        if(selectedItemIndexPausa<3){
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){

        mWindow->draw(menuPausa[i]);
       
    }
    }
    else{
        mWindow->draw(menuPausa[3]);
    }
    
    mWindow->display();
    }
    
void Pause::handleMouseInput(sf::Mouse::Button button, bool isPressed){
        if (button == sf::Mouse::Button::Left) {
        if(isPressed){
            buttonPressed = isPressed;
        }
    }
    }
    
sf::View Pause::getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight){
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
    
    void Pause::updateView(){
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
    
Pause::Pause(const Pause& orig) {
}

Pause::~Pause() {
}

void Pause::MoveUp(){
    
    
        if(selectedItemIndexPausa<3){

    if(selectedItemIndexPausa-1>=0){
        
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Blue);
        selectedItemIndexPausa--;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        
    }
        }
}

void Pause::MoveDown(){
    
    
        if(selectedItemIndexPausa<3){

    if(selectedItemIndexPausa+1<MAX_NUMBER_OF_ITEMS){
        
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Blue);
        selectedItemIndexPausa++;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        
    }
        }
    
}


void Pause::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    
    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        MoveUp();
    } else if (key == sf::Keyboard::S) {
        MoveDown();
    } else if (key == sf::Keyboard::Return) {
        if(selectedItemIndexPausa==1){
        selectedItemIndexPausa=3;
        }
        if(selectedItemIndexPausa==2){
            mWindow->close();
        }

    } else if (key == sf::Keyboard::Escape) {
        if(selectedItemIndexPausa<3){
        mWindow->close();}
        else{
            selectedItemIndexPausa=1;
        }
    } 
}
