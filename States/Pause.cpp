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
#include "StateStack.hpp"
#include "InGame.hpp"

Pause::Pause() {
    motor = Motor2D::Instance();
    

    
    
}

Pause::Pause(const Pause& orig) {
}

Pause::~Pause() {
}

void Pause::Clear() {
    
    printf("Clear Pausa 1\n");
    delete animatedSprite;
    printf("Clear Pausa 1\n");
    animation=NULL;
    printf("Clear Pausa 1\n");
    
    while(!menuPausa->empty()){
        delete menuPausa->back(), menuPausa->pop_back();
    }
    delete menuPausa;
    printf("Clear Pausa 1\n");
    //delete menuPausa;
    delete textoPausa;
    printf("Clear Pausa 1\n");
    delete mouseSprite;
    printf("Clear Pausa 1\n");
    delete spriteFondo;
    printf("Clear Pausa 1\n");
    delete spriteFondoOpciones;
    printf("Clear Pausa 1\n");
    delete spriteMancha;
    printf("Clear Pausa 1\n");
    delete spriteMancha2;
    printf("Clear Pausa 1\n");
    delete spritePersonaje;
    printf("Clear Pausa 1\n");
    //delete spriteRelleno;
    
}


void Pause::Inicializar() {
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
    
    menuPausa = new std::vector<Text*>();
    for(int i=0;i<15;i++){
        menuPausa->push_back(new Text());
    }
    
    printf("Empiezo inicializar de pausa\n");
    tecladoActivo = false;
    ratonSelecciona = false;
    float width = 1500;
    float height = 1500;
    colorAzul.r = 112;
    colorAzul.g = 112;
    colorAzul.b = 112;

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
    
printf("Empiezo inicializar el array del menu\n");
    menuPausa->at(0)->setFont(fontPausa);
    menuPausa->at(0)->setColor(sf::Color::White);
    menuPausa->at(0)->setString("Reanudar");
    menuPausa->at(0)->setStyle(sf::Text::Bold);
    menuPausa->at(0)->setPosition(80, 825);
    menuPausa->at(0)->setScale(1.2, 1.2);
    
printf("Primera posicion del array, si es esto que le jodan al mundo\n");
    menuPausa->at(1)->setFont(fontPausa);
    menuPausa->at(1)->setColor(colorAzul);
    menuPausa->at(1)->setString("Opciones");
    menuPausa->at(1)->setStyle(sf::Text::Bold);
    menuPausa->at(1)->setPosition(80, 900);
    menuPausa->at(1)->setScale(1.2, 1.2);


    menuPausa->at(2)->setFont(fontPausa);
    menuPausa->at(2)->setColor(colorAzul);
    menuPausa->at(2)->setString("Salir");
    menuPausa->at(2)->setStyle(sf::Text::Bold);
    menuPausa->at(2)->setPosition(750,850 );
    menuPausa->at(2)->setScale(1.8, 1.8);

    menuPausa->at(3)->setFont(fontPausa);
    menuPausa->at(3)->setColor(sf::Color::White);
    menuPausa->at(3)->setString("Audio");
    menuPausa->at(3)->setStyle(sf::Text::Bold);
    menuPausa->at(3)->setPosition(80, 825);
    menuPausa->at(3)->setScale(1.2, 1.2);

    menuPausa->at(4)->setFont(fontPausa);
    menuPausa->at(4)->setColor(colorAzul);
    menuPausa->at(4)->setString("Video");
    menuPausa->at(4)->setStyle(sf::Text::Bold);
    menuPausa->at(4)->setPosition(80, 900);
    menuPausa->at(4)->setScale(1.2, 1.2);

    menuPausa->at(5)->setFont(fontPausa);
    menuPausa->at(5)->setColor(colorAzul);
    menuPausa->at(5)->setString("Personalizar");
    menuPausa->at(5)->setStyle(sf::Text::Bold);
    menuPausa->at(5)->setPosition(750,825 );
    menuPausa->at(5)->setScale(1, 1);

    menuPausa->at(6)->setFont(fontPausa);
    menuPausa->at(6)->setColor(colorAzul);
    menuPausa->at(6)->setString("Atrás");
    menuPausa->at(6)->setStyle(sf::Text::Bold);
    menuPausa->at(6)->setPosition(750,900 );
    menuPausa->at(6)->setScale(1.2, 1.2);

    menuPausa->at(7)->setFont(fontPausa);
    menuPausa->at(7)->setColor(colorAzul);
    menuPausa->at(7)->setString("Cambiar volumen");
    menuPausa->at(7)->setStyle(sf::Text::Bold);
    menuPausa->at(7)->setPosition(300, 350);
    menuPausa->at(7)->setScale(1.2, 1.2);

    menuPausa->at(8)->setFont(fontPausa);
    menuPausa->at(8)->setColor(colorAzul);
    menuPausa->at(8)->setString("Cambiar resolución");
    menuPausa->at(8)->setStyle(sf::Text::Bold);
    menuPausa->at(8)->setPosition(300, 350);
    menuPausa->at(8)->setScale(1.2, 1.2);

    menuPausa->at(9)->setFont(fontPausa);
    menuPausa->at(9)->setColor(colorAzul);
    menuPausa->at(9)->setString("Cambiar sprite del ratón");
    menuPausa->at(9)->setStyle(sf::Text::Bold);
    menuPausa->at(9)->setPosition(300, 350);
    menuPausa->at(9)->setScale(1.2, 1.2);

    printf("Ultima posicion del array, si es esto que le jodan al mundo\n");
    
    textoPausa->setFont(fontPausa);
    textoPausa->setColor(sf::Color::White);
    textoPausa->setScale(2,2);
    textoPausa->setString("PAUSA");
    textoPausa->setPosition(30, 200);
    textoPausa->setStyle(sf::Text::Bold);
    
    printf("Te odio 1\n");

    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    mouseSprite->setTexture(mouseTexture);
    mouseSprite->setScale(0.2, 0.2);
    mouseSprite->setPosition(20, 20);
    mouseSprite->setOrigin(64, 64);

    printf("Te odio 2\n");
    
    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    spriteFondo->setTexture(texturaFondo);
    spriteFondo->setTextRect(0, 0, 1280, 720);
    spriteFondo->setScale(1, 2);
    spriteFondo->setPosition(0, 0);
    transparent.a = 125;
    spriteFondo->setColor(transparent);

    printf("Te odio 3\n");
    
    spriteFondoOpciones->setTexture(texturaFondo);
    spriteFondoOpciones->setTextRect(0, 0, 500, 500);
    spriteFondoOpciones->setOrigin(250, 250);
    spriteFondoOpciones->setPosition(1500 / 2, 1500 / 2);
    transparent.a = 200;
    spriteFondoOpciones->setColor(transparent);

    printf("Te odio 4\n");
    
    spriteMancha->setTexture(texturaMancha);
    spriteMancha->setTextRect(0, 0, 1733, 1733);
    spriteMancha->setPosition(-125,500);
    spriteMancha->setScale(0.4, 0.4);

    printf("Te odio 5\n");
    
    spriteMancha2->setTexture(texturaMancha);
    spriteMancha2->setTextRect(0, 0, 1733, 1733);
    spriteMancha2->setPosition(500,500 );
    spriteMancha2->setScale(0.4, 0.4);

    spritePersonaje->setTexture(texturaPersonaje);
    spritePersonaje->setTextRect(0, 0, 1733, 1733);
    spritePersonaje->setOrigin(0, 0);
    spritePersonaje->setPosition(550,100 );
    spritePersonaje->setScale(1.75, 1.75);


    spriteRelleno->setTexture(texturaRelleno);
    spriteRelleno->setTextRect(0, 0, 1024, 2048);
    spriteRelleno->setScale(1, 2);
    
    printf("Termino inicializar de pausa\n");
}

void Pause::Update(sf::Time timeElapsed) {
    sf::Color color2(112, 112, 112);
        if (motor->GetMouseSprite()->getGlobalBounds().intersects(menuPausa->at(0)->getGlobalBounds())) {
            printf("entro en if 1");
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menuPausa->at(0)->setColor(sf::Color::White);
                menuPausa->at(1)->setColor(color2);
                menuPausa->at(2)->setColor(color2);
                selectedItemIndexPausa = 0;
            } else {
                tecladoActivo = false;
            }
        } else if (motor->GetMouseSprite()->getGlobalBounds().intersects(menuPausa->at(1)->getGlobalBounds())) {
            printf("entro en if 2");
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menuPausa->at(0)->setColor(color2);
                menuPausa->at(1)->setColor(sf::Color::White);
                menuPausa->at(2)->setColor(color2);
                selectedItemIndexPausa = 1;
            } else {
                tecladoActivo = false;
            }
        } else if (motor->GetMouseSprite()->getGlobalBounds().intersects(menuPausa->at(2)->getGlobalBounds())) {
           
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menuPausa->at(0)->setColor(color2);
                menuPausa->at(1)->setColor(color2);
                menuPausa->at(2)->setColor(sf::Color::White);

                selectedItemIndexPausa = 2;
            } else {
                tecladoActivo = false;
            }
        } else {
            ratonSelecciona = false;
            if (!tecladoActivo) {
                menuPausa->at(0)->setColor(color2);
                menuPausa->at(1)->setColor(color2);
                menuPausa->at(2)->setColor(color2);
            }
        }
    
}

void Pause::Render(float interpolation, sf::Time elapsedTime) {
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
        textoPausa->setScale(5, 5);
        for (int i = 0; i < 3; i++) {
            motor->draw(*menuPausa->at(i));
        }
    }

    if (selectedItemIndexPausa >= 3 && selectedItemIndexPausa < 8) {
        textoPausa->setString("OPCIONES");
        textoPausa->setScale(4, 4);
        for (int i = 3; i < 7; i++) {
            motor->draw(*menuPausa->at(i));
        }
    }

    if (selectedItemIndexPausa > 7) {
        if (selectedItemIndexPausa == 8) {
            textoPausa->setString("Opciones de audio");
            textoPausa->setScale(1.5, 1.5);
            for (int i = 7; i < 8; i++) {
                motor->draw(*menuPausa->at(i));
            }
        }
        if (selectedItemIndexPausa == 9) {
            textoPausa->setString("Opciones de video");
            textoPausa->setScale(1.5, 1.5);

            for (int i = 8; i < 9; i++) {
                motor->draw(*menuPausa->at(i));
            }
        }
        if (selectedItemIndexPausa == 10) {
            textoPausa->setString("Personalizar");
            textoPausa->setScale(1.5, 1.5);

            for (int i = 9; i < 10; i++) {
                motor->draw(*menuPausa->at(i));
            }
        }
    }
    motor->draw(*textoPausa);
    motor->SetView(1); //vista del juego

    motor-> DrawMouse();

    motor->display();
  //  motor->display();
}

void Pause::HandleEvents(sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code,true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code,false);
            break;
        case sf::Event::MouseButtonPressed:
            handleMouseInput(event.mouseButton.button,true);
            break;
        case sf::Event::MouseButtonReleased:
            handleMouseInput(event.mouseButton.button,false);
            break;
    }
}

void Pause::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left) {
        if (isPressed) {
            buttonPressed = isPressed;
        }
    }
}
void Pause::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if(isPressed==false){
    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        if (!ratonSelecciona) {
            tecladoActivo = true;
            MoveUp();
        }
    } else if (key == sf::Keyboard::S) {
        if (!ratonSelecciona) {
            tecladoActivo = true;
            MoveDown();
        }
    } else if (key == sf::Keyboard::A) {
        if (!ratonSelecciona) {
            tecladoActivo = true;
            MoveLeft();
        }
    } else if (key == sf::Keyboard::D) {
        if (!ratonSelecciona) {
            tecladoActivo = true;
            MoveRight();
        }
    } else if (key == sf::Keyboard::Return) {
        printf("%d\n",selectedItemIndexPausa);
        if (selectedItemIndexPausa == 0) {
             StateStack::Instance()->SetCurrentState(States::ID::InGame);
        }
        
        if (selectedItemIndexPausa == 2) {
             StateStack::Instance()->GetState(States::ID::InGame)->Clear();
             printf("Se ha borrado InGame correctamente \n");

             StateStack::Instance()->GetState(States::ID::Muerte)->Clear();
             printf("Se ha borrado Muerte correctamente \n");
            StateStack::Instance()->GetState(States::ID::Transition)->Clear();
            printf("Se ha borrado Transicion correctamente \n");
            StateStack::Instance()->GetState(States::ID::Carga)->Clear();
            printf("Se ha borrado Carga correctamente \n");
             StateStack::Instance()->GetState(States::ID::Pause)->Clear();
             printf("Se ha borrado Pausa correctamente \n");
             StateStack::Instance()->SetCurrentState(States::ID::Menu);
        }
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
            menuPausa->at(6)->setColor(colorAzul);
            menuPausa->at(3)->setColor(sf::Color::White);
        }
    }
    }
}

void Pause::MoveUp() {
    if (selectedItemIndexPausa < 3) {

        if (selectedItemIndexPausa - 1 >= 0) {

            menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa--;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);

        }
    } else {
        if (selectedItemIndexPausa - 1 >= 3 && selectedItemIndexPausa <= 7) {

            menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa--;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);

        }
    }
}

void Pause::MoveDown() {
    if (selectedItemIndexPausa < 3) {

        if (selectedItemIndexPausa + 1 < MAX_NUMBER_OF_ITEMS) {

            menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa++;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);

        }
    } else {
        if (selectedItemIndexPausa + 1 <= 7) {

           menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa++;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);

        }
    }
}

void Pause::MoveLeft() {
    if (selectedItemIndexPausa < 3) {
        if (selectedItemIndexPausa == 2) {

           menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa = 0;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);

        }
    }
    if (selectedItemIndexPausa >= 3 && selectedItemIndexPausa < 7) {

        if (selectedItemIndexPausa == 5) {
            menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa = 3;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);
        }
        if (selectedItemIndexPausa == 6) {
            menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa = 4;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);
        }
    }
}

void Pause::MoveRight() {
    if (selectedItemIndexPausa < 3) {

        if (selectedItemIndexPausa == 0 || selectedItemIndexPausa == 1) {
            menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa = 2;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);
        }

    }
    if (selectedItemIndexPausa >= 3 && selectedItemIndexPausa < 7) {

        if (selectedItemIndexPausa == 3) {
            menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa = 5;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);
        }
        if (selectedItemIndexPausa == 4) {
            menuPausa->at(selectedItemIndexPausa)->setColor(colorAzul);
            selectedItemIndexPausa = 6;
            menuPausa->at(selectedItemIndexPausa)->setColor(sf::Color::White);
        }

    }
}



