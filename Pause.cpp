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
    
    

    
        if(!fontPausa.loadFromFile("resources/Fonts/BLOX2.ttf")){
        
    }
    mWindow = ref.GetWindow();
    float width=1280;
    float height=700;
    colorAzul.r=0;
    colorAzul.g=114;
    colorAzul.b=255;



    //Vista
    mWorldView = mWindow->getDefaultView();
    mWorldView.zoom(0.5f);
        if(!fontPausa.loadFromFile("resources/Fonts/Minecraft.ttf")){
        
    }
    
    //float width=mWindow->getSize().x;
    //float height=mWindow->getSize().y;
    
    menuPausa[0].setFont(fontPausa);
    menuPausa[0].setColor(sf::Color::Red);
    menuPausa[0].setString("Reanudar");
    menuPausa[0].setStyle(sf::Text::Bold);
    menuPausa[0].setPosition(sf::Vector2f(350, mWindow->getSize().y-250));
    
    menuPausa[1].setFont(fontPausa);
    menuPausa[1].setColor(colorAzul);
    menuPausa[1].setString("Opciones");
    menuPausa[1].setStyle(sf::Text::Bold);
    menuPausa[1].setPosition(sf::Vector2f(350, mWindow->getSize().y-200));
    
    
    menuPausa[2].setFont(fontPausa);
    menuPausa[2].setColor(colorAzul);
    menuPausa[2].setString("Salir");
    menuPausa[2].setStyle(sf::Text::Bold);
    menuPausa[2].setPosition(sf::Vector2f( mWindow->getSize().x-500, mWindow->getSize().y-225));
    menuPausa[2].scale(1.8,1.8);
    
    menuPausa[3].setFont(fontPausa);
    menuPausa[3].setColor(sf::Color::Red);
    menuPausa[3].setString("Audio");
    menuPausa[3].setStyle(sf::Text::Bold);
    menuPausa[3].setPosition(sf::Vector2f(350, mWindow->getSize().y-250));
    
    menuPausa[4].setFont(fontPausa);
    menuPausa[4].setColor(colorAzul);
    menuPausa[4].setString("Video");
    menuPausa[4].setStyle(sf::Text::Bold);
    menuPausa[4].setPosition(sf::Vector2f(350, mWindow->getSize().y-200));
    
    menuPausa[5].setFont(fontPausa);
    menuPausa[5].setColor(colorAzul);
    menuPausa[5].setString("Personalizar");
    menuPausa[5].setStyle(sf::Text::Bold);
    menuPausa[5].setPosition(sf::Vector2f( mWindow->getSize().x-500, mWindow->getSize().y-240));
    menuPausa[5].setScale(0.7,0.7);
    
    menuPausa[6].setFont(fontPausa);
    menuPausa[6].setColor(colorAzul);
    menuPausa[6].setString(L"Atrás");
    menuPausa[6].setStyle(sf::Text::Bold);
    menuPausa[6].setPosition(sf::Vector2f( mWindow->getSize().x-500, mWindow->getSize().y-200));
    
    menuPausa[7].setFont(fontPausa);
    menuPausa[7].setColor(colorAzul);
    menuPausa[7].setString("Cambiar volumen");
    menuPausa[7].setStyle(sf::Text::Bold);
    menuPausa[7].setPosition(sf::Vector2f( mWindow->getSize().x/2-225, mWindow->getSize().y/2-100));
    
    menuPausa[8].setFont(fontPausa);
    menuPausa[8].setColor(colorAzul);
    menuPausa[8].setString(L"Cambiar resolución");
    menuPausa[8].setStyle(sf::Text::Bold);
    menuPausa[8].setPosition(sf::Vector2f( mWindow->getSize().x/2-225, mWindow->getSize().y/2-100));
    
    menuPausa[9].setFont(fontPausa);
    menuPausa[9].setColor(colorAzul);
    menuPausa[9].setString(L"Cambiar sprite del ratón");
    menuPausa[9].setStyle(sf::Text::Bold);
    menuPausa[9].setPosition(sf::Vector2f( mWindow->getSize().x/2-225, mWindow->getSize().y/2-100));

    textoPausa.setFont(fontPausa);
    textoPausa.setColor(sf::Color::White);
    textoPausa.setString("PAUSA");
    textoPausa.setPosition(sf::Vector2f(350, 200));
    textoPausa.scale(3,3);
    
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
        texturaMancha.loadFromFile("resources/Textures/manchaSimple.png");
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
    spriteFondo.setOrigin(spriteFondo.getTextureRect().width/2,spriteFondo.getTextureRect().height/2);
    spriteFondo.setPosition(mWindow->getSize().x/2,mWindow->getSize().y/2);
    transparent.a=125;
    spriteFondo.setColor(transparent);
    
    spriteFondoOpciones.setTexture(texturaFondo);
    spriteFondoOpciones.setTextureRect(sf::IntRect(0, 0, 500, 500));
    spriteFondoOpciones.setOrigin(250,250);
    spriteFondoOpciones.setPosition(mWindow->getSize().x/2,mWindow->getSize().y/2);
    transparent.a=200;
    spriteFondoOpciones.setColor(transparent);
    
    spriteMancha.setTexture(texturaMancha);
    spriteMancha.setTextureRect(sf::IntRect(0, 0, 1733, 1733));
    spriteMancha.setOrigin(mWindow->getSize().x/2,mWindow->getSize().y/2);
    spriteMancha.setPosition(300,mWindow->getSize().y-350);
    spriteMancha.setScale(0.3,0.3);
    
    spriteMancha2.setTexture(texturaMancha);
    spriteMancha2.setTextureRect(sf::IntRect(0, 0, 1733, 1733));
    spriteMancha2.setOrigin(mWindow->getSize().x/2,mWindow->getSize().y/2);
    spriteMancha2.setPosition(850,mWindow->getSize().y-350);
    spriteMancha2.setScale(0.3,0.3);
    
    spritePersonaje.setTexture(texturaPersonaje);
    spritePersonaje.setTextureRect(sf::IntRect(0, 0, 1733, 1733));
    spritePersonaje.setOrigin(0,0);
    spritePersonaje.setPosition(mWindow->getSize().x/2+100,mWindow->getSize().y/2-200);
    printf("%d\n",spritePersonaje.getTextureRect().top);
    spritePersonaje.setScale(1,1);

    //transparent.a=80;
    //spriteAsesino.setColor(transparent);

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
   
    if(selectedItemIndexPausa<=7){
       mWindow->draw(spritePersonaje);
       mWindow->draw(spriteMancha);
       mWindow->draw(spriteMancha2);    
    }
    else{
       // mWindow->draw(spriteFondoOpciones);
    }
    //mWindow->draw(mouseSprite);
    
    if(selectedItemIndexPausa<3){
        textoPausa.setString("PAUSA");
        textoPausa.setScale(3,3);
        for(int i=0; i<3;i++){
            mWindow->draw(menuPausa[i]);
        }
    }
    
    if(selectedItemIndexPausa>=3 && selectedItemIndexPausa<8){
        textoPausa.setString("OPCIONES");
        textoPausa.setScale(2,2);
        for(int i=3; i<7;i++){
        mWindow->draw(menuPausa[i]);
        }
        }
        
    if(selectedItemIndexPausa>7){
        if(selectedItemIndexPausa==8){
            textoPausa.setString("Opciones de audio");
            textoPausa.setScale(1.5,1.5);
            textoPausa.setPosition(mWindow->getSize().x/2-225,textoPausa.getPosition().y);
            for(int i=7; i<8;i++){
            mWindow->draw(menuPausa[i]);
            }
        }
        if(selectedItemIndexPausa==9){
            textoPausa.setString("Opciones de video");
            textoPausa.setScale(1.5,1.5);
            textoPausa.setPosition(mWindow->getSize().x/2-225,textoPausa.getPosition().y);
            for(int i=8; i<9;i++){
            mWindow->draw(menuPausa[i]);
            }
        }
        if(selectedItemIndexPausa==10){
            textoPausa.setString("Personalizar");
            textoPausa.setScale(1.5,1.5);
            textoPausa.setPosition(mWindow->getSize().x/2-225,textoPausa.getPosition().y);
            for(int i=9; i<10;i++){
            mWindow->draw(menuPausa[i]);
            }
        }
    }
    mWindow->draw(textoPausa);
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
        
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa--;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        
    }
        }
        
        else{
            if(selectedItemIndexPausa-1>=3){
        
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa--;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        
    }
        }
}

void Pause::MoveDown(){
    
    
        if(selectedItemIndexPausa<3){

    if(selectedItemIndexPausa+1<MAX_NUMBER_OF_ITEMS){
        
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa++;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        
    }
        }
        
        else{
            if(selectedItemIndexPausa+1<7){
        
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa++;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        
    }
        }
        
        
    
}



void Pause::MoveLeft(){
    
    
    if(selectedItemIndexPausa<3){
    if(selectedItemIndexPausa==2){
        
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa=0;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        
    }
    }
    else{
        
    if(selectedItemIndexPausa==5){
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa=3;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
    }
        if(selectedItemIndexPausa==6){
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa=4;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
    }
    
    }

    
}


void Pause::MoveRight(){
    
    
    if(selectedItemIndexPausa<3){

    if(selectedItemIndexPausa==0 || selectedItemIndexPausa==1){
        
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa=2;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        
    }
    
    }
        else{
        
    if(selectedItemIndexPausa==3){
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa=5;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
    }
        if(selectedItemIndexPausa==4){
        menuPausa[selectedItemIndexPausa].setColor(colorAzul);
        selectedItemIndexPausa=6;
        menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
    }
    
    }
}


void Pause::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    
    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        MoveUp();
    } else if (key == sf::Keyboard::S) {
        MoveDown();
    } else if (key == sf::Keyboard::A) {
        MoveLeft();
    } else if (key == sf::Keyboard::D) {
        MoveRight();
    } else if (key == sf::Keyboard::Return) {
        
        if(selectedItemIndexPausa==3){
            selectedItemIndexPausa=8;
        }
         if(selectedItemIndexPausa==4){
            selectedItemIndexPausa=9;
        }
        if(selectedItemIndexPausa==5){
            selectedItemIndexPausa=10;
        }
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
