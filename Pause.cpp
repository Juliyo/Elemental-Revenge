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
Pause* Pause::mInstance = 0;

Pause* Pause::Instance() {
    if (mInstance == 0) {
        mInstance = new Pause;
    }
    return mInstance;
}

Pause::Pause() {
    motor = Motor2D::Instance();
    
    EstadoActivo = false;
    
    selectedItemIndexPausa = 0;

    //Reserva memoria
    spriteRelleno = new Sprite();
    spritePersonaje = new Sprite();
    spriteFondo = new Sprite();
    spriteFondoOpciones = new Sprite();
    spriteMancha = new Sprite();
    spriteMancha2 = new Sprite();
    mouseSprite = new Sprite();
    textoPausa = new Text();
    menuPausa = new Text[10];
    
    //Estado de Ingame
    EstadoActivo = false;
    
    float width = 1500;
    float height = 1500;
    colorAzul.r = 0;
    colorAzul.g = 114;
    colorAzul.b = 255;

    //texturas
    try {
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaFondo.loadFromFile("resources/Textures/fondo.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
        texturaMancha.loadFromFile("resources/Textures/manchaSimple.png");
        texturaPersonaje.loadFromFile("resources/Textures/fondoPersonaje.png");
        fontPausa.loadFromFile("resources/Fonts/BLOX2.ttf");
        fontPausa.loadFromFile("resources/Fonts/Minecraft.ttf");
    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    

    menuPausa[0].setFont(fontPausa);
    menuPausa[0].setColor(sf::Color::Red);
    menuPausa[0].setString("Reanudar");
    menuPausa[0].setStyle(sf::Text::Bold);
    menuPausa[0].setPosition(600, 1500 - 550);

    menuPausa[1].setFont(fontPausa);
    menuPausa[1].setColor(colorAzul);
    menuPausa[1].setString("Opciones");
    menuPausa[1].setStyle(sf::Text::Bold);
    menuPausa[1].setPosition(600, 1500 - 500);


    menuPausa[2].setFont(fontPausa);
    menuPausa[2].setColor(colorAzul);
    menuPausa[2].setString("Salir");
    menuPausa[2].setStyle(sf::Text::Bold);
    menuPausa[2].setPosition(1000, 1500 - 525);
    menuPausa[2].setScale(1.8, 1.8);

    menuPausa[3].setFont(fontPausa);
    menuPausa[3].setColor(sf::Color::Red);
    menuPausa[3].setString("Audio");
    menuPausa[3].setStyle(sf::Text::Bold);
    menuPausa[3].setPosition(900, 1500 - 500);

    menuPausa[4].setFont(fontPausa);
    menuPausa[4].setColor(colorAzul);
    menuPausa[4].setString("Video");
    menuPausa[4].setStyle(sf::Text::Bold);
    menuPausa[4].setPosition(350, 1500 - 200);

    menuPausa[5].setFont(fontPausa);
    menuPausa[5].setColor(colorAzul);
    menuPausa[5].setString("Personalizar");
    menuPausa[5].setStyle(sf::Text::Bold);
    menuPausa[5].setPosition(1500 - 500, 1500 - 240);
    menuPausa[5].setScale(0.7, 0.7);

    menuPausa[6].setFont(fontPausa);
    menuPausa[6].setColor(colorAzul);
    menuPausa[6].setString("Atrás");
    menuPausa[6].setStyle(sf::Text::Bold);
    menuPausa[6].setPosition(1500 - 500, 1500 - 200);

    menuPausa[7].setFont(fontPausa);
    menuPausa[7].setColor(colorAzul);
    menuPausa[7].setString("Cambiar volumen");
    menuPausa[7].setStyle(sf::Text::Bold);
    menuPausa[7].setPosition(1500 / 2 - 225, 1500 / 2 - 100);

    menuPausa[8].setFont(fontPausa);
    menuPausa[8].setColor(colorAzul);
    menuPausa[8].setString("Cambiar resolución");
    menuPausa[8].setStyle(sf::Text::Bold);
    menuPausa[8].setPosition(1500 / 2 - 225, 1500 / 2 - 100);

    menuPausa[9].setFont(fontPausa);
    menuPausa[9].setColor(colorAzul);
    menuPausa[9].setString("Cambiar sprite del ratón");
    menuPausa[9].setStyle(sf::Text::Bold);
    menuPausa[9].setPosition(1500 / 2 - 225, 1500 / 2 - 100);

    textoPausa->setFont(fontPausa);
    textoPausa->setColor(sf::Color::White);
    textoPausa->setString("PAUSA");
    textoPausa->setPosition(600, 500);
    textoPausa->setScale(3, 3);

    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    mouseSprite->setTexture(mouseTexture);
    mouseSprite->setScale(0.2, 0.2);
    mouseSprite->setPosition(20, 20);
    mouseSprite->setOrigin(64, 64);

    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    spriteFondo->setTexture(texturaFondo);
    spriteFondo->setTextRect(0, 0, 1280, 720);
    spriteFondo->setOrigin(spriteFondo->getTextureRect().width / 2, spriteFondo->getTextureRect().height / 2);
    spriteFondo->setPosition(1500 / 2, 1500 / 2);
    transparent.a = 125;
    spriteFondo->setColor(transparent);

    spriteFondoOpciones->setTexture(texturaFondo);
    spriteFondoOpciones->setTextRect(0, 0, 500, 500);
    spriteFondoOpciones->setOrigin(250, 250);
    spriteFondoOpciones->setPosition(1500 / 2, 1500 / 2);
    transparent.a = 200;
    spriteFondoOpciones->setColor(transparent);

    spriteMancha->setTexture(texturaMancha);
    spriteMancha->setTextRect(0, 0, 1733, 1733);
    spriteMancha->setOrigin(1500 / 2, 1500 / 2);
    spriteMancha->setPosition(300, 1500 - 350);
    spriteMancha->setScale(0.3, 0.3);

    spriteMancha2->setTexture(texturaMancha);
    spriteMancha2->setTextRect(0, 0, 1733, 1733);
    spriteMancha2->setOrigin(1500 / 2, 1500 / 2);
    spriteMancha2->setPosition(850, motor->getAltoVentana() - 350);
    spriteMancha2->setScale(0.3, 0.3);

    spritePersonaje->setTexture(texturaPersonaje);
    spritePersonaje->setTextRect(0, 0, 1733, 1733);
    spritePersonaje->setOrigin(0, 0);
    spritePersonaje->setPosition(1500 / 2 + 100, 1500 / 2 - 200);
    spritePersonaje->setScale(1, 1);


    spriteRelleno->setTexture(texturaRelleno);
    spriteRelleno->setTextRect(0, 0, 1024, 2048);
    spriteRelleno->setScale(1, 2);
}

Pause::Pause(const Pause& orig) {
}

Pause::~Pause() {
}

void Pause::render(float interpolation, sf::Time elapsedTime) {
    motor->draw(spriteFondo);
    if (selectedItemIndexPausa <= 7) {
        motor->draw(spritePersonaje);
        motor->draw(spriteMancha);
        motor->draw(spriteMancha2);
    } else {
        // mWindow->draw(spriteFondoOpciones);
    }
    //mWindow->draw(mouseSprite);

    if (selectedItemIndexPausa < 3) {
        textoPausa->setString("PAUSA");
        textoPausa->setScale(3, 3);
        for (int i = 0; i < 3; i++) {
            motor->draw(menuPausa[i]);
        }
    }

    if (selectedItemIndexPausa >= 3 && selectedItemIndexPausa < 8) {
        textoPausa->setString("OPCIONES");
        textoPausa->setScale(2, 2);
        for (int i = 3; i < 7; i++) {
            motor->draw(menuPausa[i]);
        }
    }

    if (selectedItemIndexPausa > 7) {
        if (selectedItemIndexPausa == 8) {
            textoPausa->setString("Opciones de audio");
            textoPausa->setScale(1.5, 1.5);
            textoPausa->setPosition(motor->getAnchoVentana() / 2 - 225, textoPausa->getPosition().y);
            for (int i = 7; i < 8; i++) {
                motor->draw(menuPausa[i]);
            }
        }
        if (selectedItemIndexPausa == 9) {
            textoPausa->setString("Opciones de video");
            textoPausa->setScale(1.5, 1.5);
            textoPausa->setPosition(motor->getAnchoVentana() / 2 - 225, textoPausa->getPosition().y);
            for (int i = 8; i < 9; i++) {
                motor->draw(menuPausa[i]);
            }
        }
        if (selectedItemIndexPausa == 10) {
            textoPausa->setString("Personalizar");
            textoPausa->setScale(1.5, 1.5);
            textoPausa->setPosition(motor->getAnchoVentana() / 2 - 225, textoPausa->getPosition().y);
            for (int i = 9; i < 10; i++) {
                motor->draw(menuPausa[i]);
            }
        }
    }
    motor->draw(*textoPausa);
  //  motor->display();
}

void Pause::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left) {
        if (isPressed) {
            buttonPressed = isPressed;
        }
    }
}


void Pause::MoveUp() {
    if (selectedItemIndexPausa < 3) {

        if (selectedItemIndexPausa - 1 >= 0) {

            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa--;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);

        }
    } else {
        if (selectedItemIndexPausa - 1 >= 3 && selectedItemIndexPausa <= 7) {

            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa--;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);

        }
    }
}

void Pause::MoveDown() {
    if (selectedItemIndexPausa < 3) {

        if (selectedItemIndexPausa + 1 < MAX_NUMBER_OF_ITEMS) {

            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa++;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);

        }
    } else {
        if (selectedItemIndexPausa + 1 <= 7) {

            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa++;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);

        }
    }
}

void Pause::MoveLeft() {
    if (selectedItemIndexPausa < 3) {
        if (selectedItemIndexPausa == 2) {

            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa = 0;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);

        }
    }
    if (selectedItemIndexPausa >= 3 && selectedItemIndexPausa < 7) {

        if (selectedItemIndexPausa == 5) {
            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa = 3;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        }
        if (selectedItemIndexPausa == 6) {
            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa = 4;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        }
    }
}

void Pause::MoveRight() {
    if (selectedItemIndexPausa < 3) {

        if (selectedItemIndexPausa == 0 || selectedItemIndexPausa == 1) {
            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa = 2;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        }

    }
    if (selectedItemIndexPausa >= 3 && selectedItemIndexPausa < 7) {

        if (selectedItemIndexPausa == 3) {
            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa = 5;
            menuPausa[selectedItemIndexPausa].setColor(sf::Color::Red);
        }
        if (selectedItemIndexPausa == 4) {
            menuPausa[selectedItemIndexPausa].setColor(colorAzul);
            selectedItemIndexPausa = 6;
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
        if (selectedItemIndexPausa == 3) {
            selectedItemIndexPausa = 8;
        }
        if (selectedItemIndexPausa == 4) {
            selectedItemIndexPausa = 9;
        }
        if (selectedItemIndexPausa == 5) {
            selectedItemIndexPausa = 10;
        }

        if (selectedItemIndexPausa == 1) {
            selectedItemIndexPausa = 3;
        }
    } else if (key == sf::Keyboard::Escape) {
        if (selectedItemIndexPausa < 3) {
            //mWindow->close();
        }
        if (selectedItemIndexPausa > 3 && selectedItemIndexPausa < 7) {
            selectedItemIndexPausa = 1;
        }
        if (selectedItemIndexPausa >= 7) {

            if (selectedItemIndexPausa == 8) {
                selectedItemIndexPausa = 3;
            }
            if (selectedItemIndexPausa == 9) {
                selectedItemIndexPausa = 4;
            }
            if (selectedItemIndexPausa == 10) {

                selectedItemIndexPausa = 5;
            }
        }
    }

    if (key == sf::Keyboard::Return) {
        if (selectedItemIndexPausa == 6) {
            selectedItemIndexPausa = 1;
            menuPausa[6].setColor(colorAzul);
            menuPausa[3].setColor(sf::Color::Red);
        }
    }
}
