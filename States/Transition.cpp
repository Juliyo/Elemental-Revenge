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
#include "StateStack.hpp"
#include "InGame.hpp"
#include "../Motor/Music.hpp"

Transition::Transition() {
    motor = Motor2D::Instance();

    motor->setCenterForView(4, 650, 350);



    /*musica = new sf::Music();
    musica->openFromFile("resources/Sounds/history.ogg");
    musica->setVolume(70);*/



}

Transition::Transition(const Transition& orig) {
}

Transition::~Transition() {
}

void Transition::Clear() {
    delete cruzeta1;
    delete cruzeta2;
    delete currentNode;
    delete firstNode;
    delete mouseSprite;
    delete nextLevel;
    delete simbolo;
    delete spriteFondo;
    delete spriteOpcionA;
    delete spriteOpcionB;
    delete spriteRelleno;
    delete video;
    delete arbol;
    delete pregunta;

}

void Transition::Inicializar() {

    spriteOpcionA = new Sprite();
    pregunta = new Sprite();
    spriteOpcionB = new Sprite();
    nextLevel = new Sprite();
    spriteRelleno = new Sprite();
    spriteFondo = new Sprite();
    mouseSprite = new Sprite();
    cruzeta1 = new Sprite();
    cruzeta2 = new Sprite();
    simbolo = new Sprite();

    video = new Video("resources/Videos/moltoFondaco/frame-", 9, 145, 110, 1, sf::Vector2f(1.7, 1.7));

    video->Inicializar();
    //Carga XML

    level = 0;
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

    firstNode = arbol->search(key);

    for (int i = 0; i < 6; i++) {
        pregunta1 = pregunta1->NextSiblingElement("pregunta");
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
        texturaOpcionA.loadFromFile("resources/UI Elements/amuleto.png");
        texturaOpcionB.loadFromFile("resources/UI Elements/colgante.png");
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaFondo.loadFromFile("resources/Textures/fondo.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
        cruzeta.loadFromFile("resources/UI Elements/cruzetas.png");
        texturaNextLevel.loadFromFile("resources/UI Elements/continuar.png");
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

    pregunta->setTexture(texPregunta);
    pregunta->setScale(0.35, 0.35);
    pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
    pregunta->setPosition(640, 360 - 100);

    spriteOpcionA->setTexture(texturaOpcionA);
    spriteOpcionA->setScale(0.5, 0.5);
    spriteOpcionA->setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
    spriteOpcionA->setPosition(500, 450);
    spriteOpcionA->setTextRect(0, 0, 258, 97);
    spriteOpcionA -> setColor(sf::Color::White);

    spriteOpcionB->setTexture(texturaOpcionB);
    spriteOpcionB->setScale(0.5, 0.5);
    spriteOpcionB->setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
    spriteOpcionB->setPosition(800, 450);
    spriteOpcionB->setTextRect(0, 0, 258, 97);
    spriteOpcionB -> setColor(sf::Color::White);

    nextLevel->setTexture(texturaNextLevel);
    nextLevel->setScale(0.5, 0.5);
    nextLevel->setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
    nextLevel->setPosition(640, 360 + 150);
    nextLevel->setTextRect(0, 0, 271, 59);

    mouseSprite->setTexture(mouseTexture);
    mouseSprite->setScale(0.2, 0.2);
    mouseSprite->setPosition(20, 20);
    mouseSprite->setOrigin(64, 64);

    cruzeta1->setTexture(cruzeta);
    cruzeta1->setOrigin(cruzeta.getSize().x / 2, cruzeta.getSize().y / 2);
    cruzeta1->setScale(0.25, 0.25);

    cruzeta2->setTexture(cruzeta);
    cruzeta2->setOrigin(cruzeta.getSize().x / 2, cruzeta.getSize().y / 2);
    cruzeta2->setScale(0.25, 0.25);

    Music *music = Music::Instance();
    music->Stop();
    music->Load(MUSICA::ID::Transiciones);
    music->Play();
}

void Transition::Update(sf::Time elapsedTime) {
    video->setDibujar(true);
    if (buttonPressed && !firstTime && (!fadeEffect && !unfadeEffect)) {
        if (spriteOpcionA->getGlobalBounds().contains(mouseSprite->getPosition())) {
            izq = true;
            der = false;
            izquierdaRes = true;
            derechaRes = false;
            fadeEffect = true;
            transparent.a = 255;
            transparent.g = 255;
            transparent.b = 255;
            transparent.r = 255;
            //aguaSkillTransition();
            firstTime = true;
        }
        if (spriteOpcionB->getGlobalBounds().contains(mouseSprite->getPosition())) {
            der = true;
            izq = false;
            izquierdaRes = false;
            derechaRes = true;
            fadeEffect = true;
            transparent.a = 255;
            transparent.g = 255;
            transparent.b = 255;
            transparent.r = 255;
            //aguaSkillTransition();
            firstTime = true;
        }
        if (drawNextLevel) { 
                printf("TU FLIPAS\n");
            if (nextLevel->getGlobalBounds().contains(mouseSprite->getPosition())) {
                printf("Estoy donde se supone que cambias el estado a InGame\n");
                changePregunta();
                preguntaContestada = true;
                drawNextLevel = false;
                buttonPressed = false;
                printf("Antes de cambiar de mapa\n");
                
                StateStack::Instance()->SetCurrentState(States::ID::Carga);
                StateStack::Instance()->GetState(States::ID::Carga)->Inicializar();


               

                level++;
                printf("Se supone que llego a la ultima linea de Ingame\n");
            }


        }
    }



    sf::Vector2f mousePosition = motor->getMousePosition();
    if (drawOpciones) {
        if (isPointOverSprite(mousePosition, *spriteOpcionA)) {
            cruzeta1->setPosition(spriteOpcionA->getPosition());
            Bcruzeta = true;
        } else if (isPointOverSprite(mousePosition, *spriteOpcionB)) {
            cruzeta1->setPosition(spriteOpcionB->getPosition());
            Bcruzeta = true;
        } else {
            Bcruzeta = false;
        }
    } else {
        if (isPointOverSprite(mousePosition, *nextLevel)) {
            cruzeta2->setPosition(nextLevel->getPosition());
            Bcruzeta = true;
        } else {
            Bcruzeta = false;
        }
    }

    if (fadeEffect) {
        pregunta->setColor(transparent);
        spriteOpcionA->setColor(transparent);
        spriteOpcionB->setColor(transparent);
        cruzeta1->setColor(transparent);
        simbolo->setColor(transparent);
        if (transparent.a - 20 < 1) {

            fadeEffect = false;
            transparent.a = 255;
            transparent.r = 255;
            transparent.g = 255;
            transparent.b = 255;
            pregunta->setColor(transparent);
            spriteOpcionA->setColor(transparent);
            spriteOpcionB->setColor(transparent);
            cruzeta1->setColor(transparent);

            simbolo->setColor(transparent);
            switch (currentNode->key_value) {
                case 4:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }
                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.3, 0.3);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.30, 0.30);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 2:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.5, 0.5);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.50, 0.50);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'r';
                    }
                    break;
                case 6:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.50, 0.50);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'r';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.55, 0.55);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 1:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.45, 0.45);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'r';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.65, 0.65);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'f';
                    }
                    break;
                case 3:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.50, 0.50);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.r = 255;
                        transparent.g = 255;
                        transparent.b = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.50, 0.50);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.g = 255;
                        transparent.b = 255;
                        transparent.r = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'r';
                    }
                    break;
                case 5:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.55, 0.55);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.g = 255;
                        transparent.b = 255;
                        transparent.r = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'a';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.55, 0.55);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.g = 255;
                        transparent.b = 255;
                        transparent.r = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'r';
                    }
                    break;
                case 7:
                    if (izq) {
                        if (!texPregunta.loadFromFile(currentNode->respuesta1)) {
                            std::cout << "Error cargando respuesta1" << std::endl;
                        }

                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.55, 0.55);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //izq = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.g = 255;
                        transparent.b = 255;
                        transparent.r = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'f';

                    } else {
                        if (!texPregunta.loadFromFile(currentNode->respuesta2)) {
                            std::cout << "Error cargando respuesta2" << std::endl;
                        }
                        pregunta->setTexture(texPregunta);
                        pregunta->setScale(0.55, 0.55);
                        pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
                        pregunta->setPosition(640, 360 - 100);
                        pregunta->setTextRect(0, 0, texPregunta.getSize().x, texPregunta.getSize().y);
                        //der = false;
                        unfadeEffect = true;
                        transparent.a = 0;
                        transparent.g = 255;
                        transparent.b = 255;
                        transparent.r = 255;
                        pregunta->setColor(transparent);
                        spriteOpcionA->setColor(transparent);
                        spriteOpcionB->setColor(transparent);
                        cruzeta1->setColor(transparent);
                        simbolo->setColor(transparent);
                        mejora = 'r';
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
                    simbolo->setTexture(simboloText);
                    simbolo->setScale(0.3, 0.3);
                    simbolo->setOrigin(simboloText.getSize().x / 2, simboloText.getSize().y / 2);
                    simbolo->setPosition(640, 360 + 50);
                    simbolo->setTextRect(0, 0, simboloText.getSize().x, simboloText.getSize().y);
                    drawNextLevel = true;

                    // simbolo.setColor(transparent);
                    break;
                case 'f':
                    if (!simboloText.loadFromFile("resources/UI Elements/fuego-icono.png")) {
                        std::cout << "Error cargando fuego-icono" << std::endl;
                    }
                    simbolo->setTexture(simboloText);
                    simbolo->setScale(0.3, 0.3);
                    simbolo->setOrigin(simboloText.getSize().x / 2, simboloText.getSize().y / 2);
                    simbolo->setPosition(640, 360 + 50);
                    simbolo->setTextRect(0, 0, simboloText.getSize().x, simboloText.getSize().y);
                    drawNextLevel = true;
                    break;
                case 'r':
                    if (!simboloText.loadFromFile("resources/UI Elements/rayo-icono.png")) {
                        std::cout << "Error cargando rayo-icono" << std::endl;
                    }
                    simbolo->setTexture(simboloText);
                    simbolo->setScale(0.3, 0.3);
                    simbolo->setOrigin(simboloText.getSize().x / 2, simboloText.getSize().y / 2);
                    simbolo->setPosition(640, 360 + 50);
                    simbolo->setTextRect(0, 0, simboloText.getSize().x, simboloText.getSize().y);
                    drawNextLevel = true;
                    break;
            }

        } else {
            transparent.a -= 20;
        }
    }
    if (unfadeEffect) {
        pregunta->setColor(transparent);
        spriteOpcionA->setColor(transparent);
        spriteOpcionB->setColor(transparent);
        cruzeta1->setColor(transparent);
        simbolo->setColor(transparent);
        if (transparent.a + 20 > 255) {
            unfadeEffect = false;
            transparent.a = 255;
            transparent.r = 255;
            transparent.g = 255;
            transparent.b = 255;
            pregunta->setColor(transparent);
            spriteOpcionA->setColor(transparent);
            spriteOpcionB->setColor(transparent);
            cruzeta1->setColor(transparent);
            simbolo->setColor(transparent);
        } else {
            transparent.a += 20;
        }
    }
}

void Transition::changePregunta() {
    if (izq) {
        if (currentNode -> left == NULL) {
            if (salir)
                exit(0);
            salir = true;
            izq = false;
        } else {
            //std::cout<<currentNode -> left -> pregunta <<std::endl;
            currentNode = currentNode -> left;
            izq = false;
        }

    } else {
        if (currentNode -> right == NULL) {
            if (salir)
                exit(0);
            salir = true;
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
            spriteOpcionA->setTexture(texturaOpcionA);
            spriteOpcionA->setScale(0.5, 0.5);
            spriteOpcionA->setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA->setPosition(500, 450);
            spriteOpcionA->setTextRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y);

            spriteOpcionB->setTexture(texturaOpcionB);
            spriteOpcionB->setScale(0.5, 0.5);
            spriteOpcionB->setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB->setPosition(800, 450);
            spriteOpcionB->setTextRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y);

            pregunta->setTexture(texPregunta);
            pregunta->setScale(0.55, 0.55);
            pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta->setPosition(640, 360 - 100);
            cruzeta1->setScale(0.35, 0.35);

            break;
        case 6:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O31.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O32.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA->setTexture(texturaOpcionA);
            spriteOpcionA->setScale(0.35, 0.35);
            spriteOpcionA->setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA->setPosition(500, 450);
            spriteOpcionA->setTextRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y);

            spriteOpcionB->setTexture(texturaOpcionB);
            spriteOpcionB->setScale(0.35, 0.35);
            spriteOpcionB->setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB->setPosition(800, 450);
            spriteOpcionB->setTextRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y);

            pregunta->setTexture(texPregunta);
            pregunta->setScale(0.65, 0.65);
            pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta->setPosition(640, 360 - 100);
            cruzeta1->setScale(0.35, 0.35);
            break;
        case 1:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O41.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O42.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA->setTexture(texturaOpcionA);
            spriteOpcionA->setScale(0.5, 0.5);
            spriteOpcionA->setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA->setPosition(500, 450);
            spriteOpcionA->setTextRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y);

            spriteOpcionB->setTexture(texturaOpcionB);
            spriteOpcionB->setScale(0.5, 0.5);
            spriteOpcionB->setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB->setPosition(800, 450);
            spriteOpcionB->setTextRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y);

            pregunta->setTexture(texPregunta);
            pregunta->setScale(0.55, 0.55);
            pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta->setPosition(640, 360 - 100);

            cruzeta1->setScale(0.40, 0.40);
            break;
        case 3:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O51.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O52.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA->setTexture(texturaOpcionA);
            spriteOpcionA->setScale(0.5, 0.5);
            spriteOpcionA->setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA->setPosition(500, 450);
            spriteOpcionA->setTextRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y);

            spriteOpcionB->setTexture(texturaOpcionB);
            spriteOpcionB->setScale(0.5, 0.5);
            spriteOpcionB->setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB->setPosition(800, 450);
            spriteOpcionB->setTextRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y);

            pregunta->setTexture(texPregunta);
            pregunta->setScale(0.50, 0.50);
            pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta->setPosition(640, 360 - 100);
            cruzeta1->setScale(0.25, 0.25);
            break;
        case 5:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O61.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O62.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA->setTexture(texturaOpcionA);
            spriteOpcionA->setScale(0.5, 0.5);
            spriteOpcionA->setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA->setPosition(500, 450);
            spriteOpcionA->setTextRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y);

            spriteOpcionB->setTexture(texturaOpcionB);
            spriteOpcionB->setScale(0.5, 0.5);
            spriteOpcionB->setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB->setPosition(800, 450);
            spriteOpcionB->setTextRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y);

            pregunta->setTexture(texPregunta);
            pregunta->setScale(0.75, 0.75);
            pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta->setPosition(640, 360 - 100);
            cruzeta1->setScale(0.50, 0.50);
            break;
        case 7:
            if (!texturaOpcionA.loadFromFile("resources/UI Elements/O71.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            if (!texturaOpcionB.loadFromFile("resources/UI Elements/O72.png")) {
                std::cout << "Error cargando agua-icono" << std::endl;
            }
            spriteOpcionA->setTexture(texturaOpcionA);
            spriteOpcionA->setScale(0.5, 0.5);
            spriteOpcionA->setOrigin(texturaOpcionA.getSize().x / 2, texturaOpcionA.getSize().y / 2);
            spriteOpcionA->setPosition(500, 450);
            spriteOpcionA->setTextRect(0, 0, texturaOpcionA.getSize().x, texturaOpcionA.getSize().y);

            spriteOpcionB->setTexture(texturaOpcionB);
            spriteOpcionB->setScale(0.5, 0.5);
            spriteOpcionB->setOrigin(texturaOpcionB.getSize().x / 2, texturaOpcionB.getSize().y / 2);
            spriteOpcionB->setPosition(800, 450);
            spriteOpcionB->setTextRect(0, 0, texturaOpcionB.getSize().x, texturaOpcionB.getSize().y);

            pregunta->setTexture(texPregunta);
            pregunta->setScale(0.55, 0.55);
            pregunta->setOrigin(texPregunta.getSize().x / 2, texPregunta.getSize().y / 2);
            pregunta->setPosition(640, 360 - 100);
            cruzeta1->setScale(0.40, 0.40);
            break;
    }

    drawOpciones = true;
    drawNextLevel = false;
    unfadeEffect = true;
    transparent.a = 0;
    pregunta->setColor(transparent);
}

void Transition::Render(float interpolation, sf::Time elapsedTime) {

    motor->clear();
    //Pillamos la view anterior, activamos la del fondo, dibujamos el fondo y volvemos al estado anterior
    motor->SetView(0);
    motor->draw(spriteRelleno);
    motor->SetView(4);
    updateView();
    //motor->draw(spriteFondo);
    video->PlayVideo();

    motor->draw(pregunta);

    if (drawOpciones) {
        motor->draw(spriteOpcionA);
        motor->draw(spriteOpcionB);
        if (Bcruzeta) {
            motor->draw(cruzeta1);
        }
    } else {
        motor->draw(simbolo);
        motor->draw(nextLevel);
        if (Bcruzeta) {
            motor->draw(cruzeta2);
        }
    }

    motor->SetView(2);
    motor->SetView(4);
    motor->draw(mouseSprite);
    motor->display();
}

void Transition::updateView() {
    sf::FloatRect viewBounds(motor->getCenterFromView(4) - motor->getSizeFromView(4) / 2.f, motor->getSizeFromView(4));

    sf::Vector2f position = motor->getMousePosition();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);
    mouseSprite->setPosition(position.x, position.y);
    motor->setSizeForView(4, 640, 480);
    motor->SetView(4);
}

void Transition::HandleEvents(sf::Event& event) {
    switch (event.type) {
            /*case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code,true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code,false);
                break;*/
        case sf::Event::MouseButtonPressed:
            handleMouseInput(event.mouseButton.button, true);
            break;
        case sf::Event::MouseButtonReleased:
            handleMouseInput(event.mouseButton.button, false);
            break;
    }
}

void Transition::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left) {
        buttonPressed = isPressed;
    }
}

bool Transition::isPointOverSprite(const sf::Vector2f Position, Sprite &Sprite) {
    return (Position.x > Sprite.getPosition().x - Sprite.getLocalBounds().width / 2) && (Position.x < Sprite.getPosition().x + Sprite.getLocalBounds().width / 2) &&
            (Position.y > Sprite.getPosition().y - Sprite.getLocalBounds().height / 2) && (Position.y < Sprite.getPosition().y + Sprite.getLocalBounds().height / 2);
}

int Transition::getIzqODer() {

    if (izquierdaRes == true) {
        return 1;
    } else {
        return 2;
    }
}
