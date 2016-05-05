/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Carga1.cpp
 * Author: Julio
 * 
 * Created on 18 de abril de 2016, 12:32
 */

#include "LoadingState.hpp"
#include "../Motor/Text.hpp"
#include "../Motor/Video.hpp"


LoadingState::LoadingState() {
    motor = Motor2D::Instance();

    
    //motor->setCenterForView(3, 650, 350);

    spriteRelleno = new Sprite();
    spriteFondo = new Sprite();
    mouseSprite = new Sprite();
    cargando = new Text();
    mensaje = new Text();
    
    reloj1 = new Reloj();
    video = new Video("resources/Videos/solaire/frame-",36,500,500,1,sf::Vector2f(1,1),true,sf::Vector2f(960,512));
    
}

LoadingState::LoadingState(const LoadingState& orig) {
}

LoadingState::~LoadingState() {
}

void LoadingState::Inicializar() {
    video->Inicializar();
    //Carga texturas
    try {
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaFondo.loadFromFile("resources/Textures/fondo2.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    
    mouseSprite->setTexture(mouseTexture);
    mouseSprite->setScale(0.2, 0.2);
    mouseSprite->setPosition(20, 20);
    mouseSprite->setOrigin(64, 64);
    
    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    spriteFondo->setTexture(texturaFondo);
    spriteFondo->setTextRect(0, 0, 2000, 2000);

    spriteRelleno->setTexture(texturaRelleno);
    spriteRelleno->setTextRect(0, 0, 1024, 2048);
    spriteRelleno->setScale(1, 2);
    
    cargando->setFont("resources/Fonts/Minecraft.ttf");
    cargando->setString("Cargando");
    cargando->setPosition(400,450);
    cargando->setScale(1.2,1.2);
    
    mensaje->setFont("resources/Fonts/Minecraft.ttf");
    mensaje->setString("Historia++;");
    mensaje->setPosition(440,520);
    mensaje->setScale(0.6,0.6);
    
    loadingTask = new ParalellTask();
    
    loadingTask->Execute(mensaje);
}


void LoadingState::Update(sf::Time elapsedTime) {
    if(reloj1->getTiempo() > 0.5 && reloj1->getTiempo() < 1){
        cargando->setString("Cargando.");
    }
    if(reloj1->getTiempo() > 1 && reloj1->getTiempo() < 1.5){
        cargando->setString("Cargando..");
    }
    if(reloj1->getTiempo() > 1.5 && reloj1->getTiempo() < 2){
        cargando->setString("Cargando...");
    }
    if(reloj1->getTiempo() > 2){
        cargando->setString("Cargando");
        reloj1->restart();
    }
    video->setDibujar(true);
}

void LoadingState::Render(float interpolation, sf::Time elapsedTime) {
    motor->clear();

    motor->SetView(0);
    motor->draw(spriteRelleno);
    motor->SetView(3);
    updateView();
    //motor->draw(spriteFondo);
    
    video->PlayVideo();
    motor->draw(*cargando);
    motor->draw(*mensaje);
    
    motor->SetView(2);
    motor->SetView(3);
    motor->draw(mouseSprite);
    motor->display();
}

void LoadingState::updateView() {
    sf::FloatRect viewBounds(motor->getCenterFromView(3) - motor->getSizeFromView(3) / 2.f, motor->getSizeFromView(3));

    sf::Vector2f position = motor->getMousePosition();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);
    mouseSprite->setPosition(position.x, position.y);
    motor->setSizeForView(3, 640, 480);
    motor->SetView(3);
}

void LoadingState::HandleEvents(sf::Event& event) {
    return;
}


void LoadingState::transitionCargado() {
    mensaje->setString("Juego++;");
}


