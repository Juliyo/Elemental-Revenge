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

#include "btree.hpp"


Transition::Transition() {
    motor = Motor2D::Instance();
    //Estado de Ingame
    EstadoActivo = false;
     try {
        
        contFonts.loadFromFile("resources/Fonts/Sansation.ttf");
        
    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    spriteFondo.setTexture("resources/Textures/asesinatoMaestro.png", true);
    spriteOpcionA.setTexture("resources/Textures/colgante.png", true);
    spriteOpcionB.setTexture("resources/Textures/simbolo.png", true);

    spriteRelleno.setTexture("resources/Textures/background.png", true);
    spriteRelleno.setRepeated(true);
    spriteRelleno.setTextRect(0, 0, 1024, 2048);
    spriteRelleno.setScale(1, 2);

    spriteFondo.setOrigin(320,240);
    spriteFondo.setPosition(640,360);
    
    spriteOpcionA.setScale(0.6,0.6);
    spriteOpcionA.setOrigin(0,0);
    spriteOpcionA.setPosition(400,450);    
    
    spriteOpcionB.setScale(0.6,0.6);
    spriteOpcionB.setOrigin(0,0);
    spriteOpcionB.setPosition(800,450);

    
    mouseSprite.setTexture("resources/Textures/mouse.png");
    mouseSprite.setScale(0.2, 0.2);
    mouseSprite.setPosition(20, 20);
    mouseSprite.setOrigin(64, 64);

    motor->setZoomToView(0.5f,1);
    
    arbol = new btree();
    std::string pregunta = "Tu maestro ha sido asesinado y las únicas pistas son un símbolo en una hoja de papel y un amuleto, ¿qué pista debes seguir?";
    std::string r1 = "sdf";
    std::string r2 = "sdf";
    arbol->insert(1,pregunta,r1,r2);
    
    textoPregunta.setFont(contFonts);
    textoPregunta.setColor(sf::Color::Red);
    textoPregunta.setPosition(200,200);
    //std::cout<<arbol->search(1)->pregunta<<std::endl;
    textoPregunta.setString(arbol->search(1)->pregunta);
}

Transition::Transition(const Transition& orig) {
}

Transition::~Transition() {
}


void Transition::Update(sf::Time elapsedTime){
}

void Transition::render(float interpolation, sf::Time elapsedTime){
    
    motor->clear();
    motor->SetView(0);
    motor->draw(spriteRelleno);
    motor->SetView(1);
    updateView();
    motor->draw(spriteFondo);
    motor->draw(textoPregunta);
    motor->draw(spriteOpcionA);
    motor->draw(spriteOpcionB); 
    motor->SetView(2);
    motor->SetView(1);
    motor->draw(mouseSprite);
    motor->display();
}

void Transition::updateView() {
    sf::FloatRect viewBounds(motor->getCenterFromView(1) - motor->getSizeFromView(1) / 2.f, motor->getSizeFromView(1));

    sf::Vector2f position = motor->getMousePosition();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);
    
    mouseSprite.setPosition(position.x,position.y);
    motor->setSizeForView(1,640,480);
    motor->SetView(1);
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