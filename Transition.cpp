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

    //Reserva memoria
    //animatedSprite = new AnimatedSprite();
    animation = new Animation();

    //Estado de Ingame
    EstadoActivo = false;

    //Referenciamos la ventana Singleton
    mWindow = ref.GetWindow();

    //Vista
    mWorldView = mWindow->getDefaultView();
    mWorldView.zoom(0.5f);

    //Carga XML
    TiXmlDocument doc;
    doc.LoadFile("resources/historia.xml");
    TiXmlElement* pregunta1 = doc.FirstChildElement("pregunta");
    TiXmlElement* respuesta1 = doc.FirstChildElement("respuesta1");
    TiXmlElement* respuesta2 = doc.FirstChildElement("respuesta2");

    std::string p1 = pregunta1->GetText();
    std::string r1 = respuesta1->GetText();
    std::string r2 = respuesta2->GetText();
    int key;
    pregunta1->Attribute("id", &key);

    arbol = new btree();
    arbol->insert(key, p1, respuesta1->GetText(), respuesta2->GetText());

    for (int i = 0; i < 6; i++) {
        pregunta1 = pregunta1->NextSiblingElement("pregunta");
        //std::cout<<respuesta1->GetText()<<std::endl;
        respuesta1 = respuesta1->NextSiblingElement("respuesta1");
        respuesta2 = respuesta2->NextSiblingElement("respuesta2");
        pregunta1->Attribute("id", &key);
        arbol->insert(key, pregunta1->GetText(), respuesta1->GetText(), respuesta2->GetText());
    }
    //Establecemos la raiz del arbol como el nodo actual
    currentNode = arbol->search(4);
    //Carga texturas
    try {
        texPregunta.loadFromFile(arbol->search(4)->pregunta);
        texturaOpcionA.loadFromFile("resources/UI Elements/colgante.png");
        texturaOpcionB.loadFromFile("resources/UI Elements/amuleto.png");
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaFondo.loadFromFile("resources/Textures/fondo.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
        cruzeta.loadFromFile("resources/UI Elements/cruzetas.png");
        pend.loadFromFile("resources/Textures/pend.png");
        texturaNextLevel.loadFromFile("resources/UI Elements/continuar.png");
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

    spriteRelleno.setTexture(texturaRelleno);
    spriteRelleno.setTextureRect(sf::IntRect(0, 0, 1024, 2048));
    spriteRelleno.setScale(1, 2);

    pregunta.setTexture(texPregunta);
    pregunta.setScale(0.35, 0.35);
    pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
    pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);

    spriteOpcionA.setTexture(texturaOpcionA);
    spriteOpcionA.setScale(0.5, 0.5);
    spriteOpcionA.setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
    spriteOpcionA.setPosition(500, 450);
    spriteOpcionA.setTextureRect(sf::IntRect(0, 0, 258, 97));

    spriteOpcionB.setTexture(texturaOpcionB);
    spriteOpcionB.setScale(0.5, 0.5);
    spriteOpcionB.setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
    spriteOpcionB.setPosition(800, 450);
    spriteOpcionB.setTextureRect(sf::IntRect(0, 0, 258, 97));


    nextLevel.setTexture(texturaNextLevel);
    nextLevel.setScale(0.5, 0.5);
    nextLevel.setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
    nextLevel.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 + 150);
    nextLevel.setTextureRect(sf::IntRect(0, 0, 271, 59));

    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setScale(0.2, 0.2);
    mouseSprite.setPosition(20, 20);
    mouseSprite.setOrigin(64, 64);

    cruzeta1.setTexture(cruzeta);
    cruzeta1.setOrigin(cruzeta.getSize().x / 2, cruzeta.getSize().y / 2);
    cruzeta1.setScale(0.25, 0.25);

    cruzeta2.setTexture(cruzeta);
    cruzeta2.setOrigin(cruzeta.getSize().x / 2, cruzeta.getSize().y / 2);
    cruzeta2.setScale(0.25, 0.25);

    animation->setSpriteSheet(pend);

    animation->addFrame(sf::IntRect(0, 0, 447, 335));
    animation->addFrame(sf::IntRect(447, 0, 447, 335));
    animation->addFrame(sf::IntRect(447 * 2, 0, 447, 335));
    animation->addFrame(sf::IntRect(447 * 3, 0, 447, 335));
    animation->addFrame(sf::IntRect(447 * 4, 0, 447, 335));
    animation->addFrame(sf::IntRect(447 * 5, 0, 447, 335));
    animation->addFrame(sf::IntRect(447 * 6, 0, 447, 335));
    animation->addFrame(sf::IntRect(447 * 7, 0, 447, 335));
    animation->addFrame(sf::IntRect(447 * 8, 0, 447, 335));

    animation->addFrame(sf::IntRect(0, 335, 447, 335));
    animation->addFrame(sf::IntRect(447, 335, 447, 335));
    animation->addFrame(sf::IntRect(447 * 2, 335, 447, 335));
    animation->addFrame(sf::IntRect(447 * 3, 335, 447, 335));
    animation->addFrame(sf::IntRect(447 * 4, 335, 447, 335));
    animation->addFrame(sf::IntRect(447 * 5, 335, 447, 335));
    animation->addFrame(sf::IntRect(447 * 6, 335, 447, 335));
    animation->addFrame(sf::IntRect(447 * 7, 335, 447, 335));
    animation->addFrame(sf::IntRect(447 * 8, 335, 447, 335));

    animation->addFrame(sf::IntRect(0, 335 * 2, 447, 335));
    animation->addFrame(sf::IntRect(447, 335 * 2, 447, 335));
    animation->addFrame(sf::IntRect(447 * 2, 335 * 2, 447, 335));
    animation->addFrame(sf::IntRect(447 * 3, 335 * 2, 447, 335));
    animation->addFrame(sf::IntRect(447 * 4, 335 * 2, 447, 335));
    animation->addFrame(sf::IntRect(447 * 5, 335 * 2, 447, 335));
    animation->addFrame(sf::IntRect(447 * 6, 335 * 2, 447, 335));
    animation->addFrame(sf::IntRect(447 * 7, 335 * 2, 447, 335));
    animation->addFrame(sf::IntRect(447 * 8, 335 * 2, 447, 335));

    animation->addFrame(sf::IntRect(0, 335 * 3, 447, 335));
    animation->addFrame(sf::IntRect(447, 335 * 3, 447, 335));
    animation->addFrame(sf::IntRect(447 * 2, 335 * 3, 447, 335));
    animation->addFrame(sf::IntRect(447 * 3, 335 * 3, 447, 335));
    animation->addFrame(sf::IntRect(447 * 4, 335 * 3, 447, 335));
    animation->addFrame(sf::IntRect(447 * 5, 335 * 3, 447, 335));
    animation->addFrame(sf::IntRect(447 * 6, 335 * 3, 447, 335));
    animation->addFrame(sf::IntRect(447 * 7, 335 * 3, 447, 335));
    animation->addFrame(sf::IntRect(447 * 8, 335 * 3, 447, 335));

    animation->addFrame(sf::IntRect(0, 335 * 4, 447, 335));
    animation->addFrame(sf::IntRect(447, 335 * 4, 447, 335));
    animation->addFrame(sf::IntRect(447 * 2, 335 * 4, 447, 335));
    animation->addFrame(sf::IntRect(447 * 3, 335 * 4, 447, 335));
    animation->addFrame(sf::IntRect(447 * 4, 335 * 4, 447, 335));
    animation->addFrame(sf::IntRect(447 * 5, 335 * 4, 447, 335));
    animation->addFrame(sf::IntRect(447 * 6, 335 * 4, 447, 335));
    animation->addFrame(sf::IntRect(447 * 7, 335 * 4, 447, 335));
    //animation->addFrame(sf::IntRect(447*8,335*4,447,335));
    animation->addFrame(sf::IntRect(447 * 7, 335 * 4, 447, 335));

    animatedSprite = new AnimatedSprite(sf::seconds(0.06), true, false);
    animatedSprite->setPosition(315, 100);
    animatedSprite->scale(1.5, 1.5);
    std::cout << arbol->search(2)->respuesta1 << std::endl;

}

Transition::Transition(const Transition& orig) {
}

Transition::~Transition() {
}

void Transition::Update(sf::Time elapsedTime) {
    if (buttonPressed && !firstTime && (!fadeEffect && !unfadeEffect)) {
        if (spriteOpcionA.getGlobalBounds().contains(mouseSprite.getPosition())) {
            izq = true;
            der = false;
            fadeEffect = true;
            transparent.a = 255;
            //aguaSkillTransition();
            firstTime = true;
        }
        if (spriteOpcionB.getGlobalBounds().contains(mouseSprite.getPosition())) {
            der = true;
            izq = false;
            fadeEffect = true;
            transparent.a = 255;
            //aguaSkillTransition();
            firstTime = true;
        }
        if (drawNextLevel) {
            if (nextLevel.getGlobalBounds().contains(mouseSprite.getPosition())) {
                changePregunta();
                drawNextLevel = false;
            }
        }

    }

    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    if (drawOpciones) {
        if (isPointOverSprite(mousePosition, spriteOpcionA)) {
            cruzeta1.setPosition(spriteOpcionA.getPosition());
            Bcruzeta = true;
        } else if (isPointOverSprite(mousePosition, spriteOpcionB)) {
            cruzeta1.setPosition(spriteOpcionB.getPosition());
            Bcruzeta = true;
        } else {
            Bcruzeta = false;
        }
    } else {
        if (isPointOverSprite(mousePosition, nextLevel)) {
            cruzeta2.setPosition(nextLevel.getPosition());
            Bcruzeta = true;
        } else {
            Bcruzeta = false;
        }
    }

    if (fadeEffect) {
        pregunta.setColor(transparent);
        spriteOpcionA.setColor(transparent);
        spriteOpcionB.setColor(transparent);
        cruzeta1.setColor(transparent);
        //simbolo.setColor(transparent);
        if (transparent.a - 20 < 1) {

            fadeEffect = false;
            transparent.a = 255;
            pregunta.setColor(transparent);
            spriteOpcionA.setColor(transparent);
            spriteOpcionB.setColor(transparent);
            cruzeta1.setColor(transparent);
            //simbolo.setColor(transparent);
            switch (currentNode->key_value) {
                case 4:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }
                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.3, 0.3);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.30, 0.30);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 2:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.5, 0.5);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.50, 0.50);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 6:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.50, 0.50);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.55, 0.55);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 1:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.45, 0.45);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.45, 0.45);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 3:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.35, 0.35);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.50, 0.50);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 5:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.55, 0.55);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.55, 0.55);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 7:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.55, 0.55);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta.setTexture(texPregunta);
                        pregunta.setScale(0.55, 0.55);
                        pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
                        pregunta.setTextureRect(sf::IntRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y));
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        pregunta.setColor(transparent);
                        spriteOpcionA.setColor(transparent);
                        spriteOpcionB.setColor(transparent);
                        cruzeta1.setColor(transparent);
                        //simbolo.setColor(transparent);
                        mejora = 'f';
                    }
                    break;

            }
            drawOpciones = false;
            firstTime = false;
            switch (mejora) {
                case 'a':
                    if (!simboloText.loadFromFile("resources/UI Elements/agua-icono.png")) {
                        std::cout << "Error cargando agua-icono" << std::endl;
                    }
                    simbolo.setTexture(simboloText);
                    simbolo.setScale(0.3, 0.3);
                    simbolo.setOrigin(simboloText.getSize().x / 2, simboloText.getSize().y / 2);
                    simbolo.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 + 50);
                    simbolo.setTextureRect(sf::IntRect(0, 0, simboloText.getSize().x, simboloText.getSize().y));
                    drawNextLevel = true;

                    // simbolo.setColor(transparent);
                    break;
                case 'f':
                    if (!simboloText.loadFromFile("resources/UI Elements/agua-icono.png")) {
                        std::cout << "Error cargando agua-icono" << std::endl;
                    }
                    simbolo.setTexture(simboloText);
                    simbolo.setScale(0.3, 0.3);
                    simbolo.setOrigin(simboloText.getSize().x / 2, simboloText.getSize().y / 2);
                    simbolo.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 + 50);
                    simbolo.setTextureRect(sf::IntRect(0, 0, simboloText.getSize().x, simboloText.getSize().y));
                    drawNextLevel = true;
                    break;
            }

        } else {
            transparent.a -= 20;
        }
    }
    if (unfadeEffect) {
        pregunta.setColor(transparent);
        spriteOpcionA.setColor(transparent);
        spriteOpcionB.setColor(transparent);
        cruzeta1.setColor(transparent);
        //simbolo.setColor(transparent);
        if (transparent.a + 20 > 255) {
            unfadeEffect = false;
            transparent.a = 255;
            pregunta.setColor(transparent);
            spriteOpcionA.setColor(transparent);
            spriteOpcionB.setColor(transparent);
            cruzeta1.setColor(transparent);
            //simbolo.setColor(transparent);
        } else {
            transparent.a += 20;
        }
    }

}

void Transition::changePregunta() {
    if (izq) {
        if (currentNode -> left == NULL) {
            exit(0);
            izq = false;
        } else {
            //std::cout<<currentNode -> left -> pregunta <<std::endl;
            currentNode = currentNode -> left;
            izq = false;
        }

    } else {
        if (currentNode -> right == NULL) {
            exit(0);
            der = false;
        } else {
            currentNode = currentNode -> right;
            der = false;
        }
    }
    if (!texPregunta.loadFromFile(currentNode->pregunta)) {
        std::cout << "Error cargando " + currentNode->pregunta << std::endl;
    }
    switch (currentNode->key_value) {
        case 2:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O21.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O22.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA.setTexture(texturaOpcionA);
            spriteOpcionA.setScale(0.5, 0.5);
            spriteOpcionA.setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA.setPosition(500, 450);
            spriteOpcionA.setTextureRect(sf::IntRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y));

            spriteOpcionB.setTexture(texturaOpcionB);
            spriteOpcionB.setScale(0.5, 0.5);
            spriteOpcionB.setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB.setPosition(800, 450);
            spriteOpcionB.setTextureRect(sf::IntRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y));
            
            pregunta.setTexture(texPregunta);
            pregunta.setScale(0.55, 0.55);
            pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
            break;
        case 6:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O31.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O32.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA.setTexture(texturaOpcionA);
            spriteOpcionA.setScale(0.5, 0.5);
            spriteOpcionA.setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA.setPosition(500, 450);
            spriteOpcionA.setTextureRect(sf::IntRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y));

            spriteOpcionB.setTexture(texturaOpcionB);
            spriteOpcionB.setScale(0.5, 0.5);
            spriteOpcionB.setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB.setPosition(800, 450);
            spriteOpcionB.setTextureRect(sf::IntRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y));
            
            pregunta.setTexture(texPregunta);
            pregunta.setScale(0.55, 0.55);
            pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
            break;
        case 1:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O41.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O42.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA.setTexture(texturaOpcionA);
            spriteOpcionA.setScale(0.5, 0.5);
            spriteOpcionA.setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA.setPosition(500, 450);
            spriteOpcionA.setTextureRect(sf::IntRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y));

            spriteOpcionB.setTexture(texturaOpcionB);
            spriteOpcionB.setScale(0.5, 0.5);
            spriteOpcionB.setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB.setPosition(800, 450);
            spriteOpcionB.setTextureRect(sf::IntRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y));
            
            pregunta.setTexture(texPregunta);
            pregunta.setScale(0.55, 0.55);
            pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
            break;
        case 3:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O51.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O52.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA.setTexture(texturaOpcionA);
            spriteOpcionA.setScale(0.5, 0.5);
            spriteOpcionA.setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA.setPosition(500, 450);
            spriteOpcionA.setTextureRect(sf::IntRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y));

            spriteOpcionB.setTexture(texturaOpcionB);
            spriteOpcionB.setScale(0.5, 0.5);
            spriteOpcionB.setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB.setPosition(800, 450);
            spriteOpcionB.setTextureRect(sf::IntRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y));
            
            pregunta.setTexture(texPregunta);
            pregunta.setScale(0.50, 0.50);
            pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
            break;
        case 5:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O61.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O62.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA.setTexture(texturaOpcionA);
            spriteOpcionA.setScale(0.5, 0.5);
            spriteOpcionA.setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA.setPosition(500, 450);
            spriteOpcionA.setTextureRect(sf::IntRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y));

            spriteOpcionB.setTexture(texturaOpcionB);
            spriteOpcionB.setScale(0.5, 0.5);
            spriteOpcionB.setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB.setPosition(800, 450);
            spriteOpcionB.setTextureRect(sf::IntRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y));
            
            pregunta.setTexture(texPregunta);
            pregunta.setScale(0.50, 0.50);
            pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
            break;
        case 7:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O71.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O72.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA.setTexture(texturaOpcionA);
            spriteOpcionA.setScale(0.5, 0.5);
            spriteOpcionA.setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA.setPosition(500, 450);
            spriteOpcionA.setTextureRect(sf::IntRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y));

            spriteOpcionB.setTexture(texturaOpcionB);
            spriteOpcionB.setScale(0.5, 0.5);
            spriteOpcionB.setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB.setPosition(800, 450);
            spriteOpcionB.setTextureRect(sf::IntRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y));
            
            pregunta.setTexture(texPregunta);
            pregunta.setScale(0.55, 0.55);
            pregunta.setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 - 100);
            break;
    }

    drawOpciones = true;
    drawNextLevel = false;
    unfadeEffect = true;
    transparent.a = 0;
    pregunta.setColor(transparent);
}

bool Transition::isPointOverSprite(const sf::Vector2f Position, const sf::Sprite &Sprite) {
    return (Position.x > Sprite.getPosition().x - Sprite.getLocalBounds().width / 2) && (Position.x < Sprite.getPosition().x + Sprite.getLocalBounds().width / 2) &&
            (Position.y > Sprite.getPosition().y - Sprite.getLocalBounds().height / 2) && (Position.y < Sprite.getPosition().y + Sprite.getLocalBounds().height / 2);
}

void Transition::render(float interpolation, sf::Time elapsedTime) {

    mWindow->clear();
    //Pillamos la view anterior, activamos la del fondo, dibujamos el fondo y volvemos al estado anterior
    sf::View previa = mWindow->getView();
    mWindow->setView(mBackgroundView);
    mWindow->draw(spriteRelleno);
    mWindow->setView(previa);
    updateView();
    /*animatedSprite->play(*animation);
    animatedSprite->update(elapsedTime);
    mWindow->draw(*animatedSprite);*/
    mWindow->draw(spriteFondo);

    mWindow->draw(pregunta);

    if (drawOpciones) {
        mWindow->draw(spriteOpcionA);
        mWindow->draw(spriteOpcionB);
        if (Bcruzeta) {
            mWindow->draw(cruzeta1);
        }
    } else {
        mWindow->draw(simbolo);
        mWindow->draw(nextLevel);
        if (Bcruzeta) {
            mWindow->draw(cruzeta2);
        }
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
        buttonPressed = isPressed;
    }

}