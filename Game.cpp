#include "Game.hpp"
#include <SFML/System.hpp>
#include "Pause.hpp"
#include "Map.hpp"

#include <cmath>
#include <math.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#define M_PI          3.141592653589793238462643383279502884 /* pi */
/************ VARIABLES GLOBALES ************/
const sf::Time Game::timePerFrame = sf::seconds(1.f / 15.f);
int ancho = 1280, alto = 720;
const float segStatistics = 0.5f; //segundos de refresco de las estadisticas

/************ CONSTRUCTOR **************/
Game::Game() {
    
    thread = new sf::Thread(&Game::cargarInGameTransition, this);
    thread2 = new sf::Thread(&Game::cargarMapa, this);
    motor = Motor2D::Instance();
    motor->Inicializar();
    motor->inicializarVentana("Hito 2 - Intento Motor", 1280, 720);
    
    /* EstadoInGame = new InGame();
     EstadoTransition = new Transition();
     EstadoPause = new Pause();
     EstadoMuerte = new Muerte();*/
    EstadoMenu = new Menu2();
    estadoMenu = true;

#ifdef _WIN32
    HWND handler = motor->getSystemHandle();
    RECT rWindow;
    GetWindowRect(handler, &rWindow);
    ClipCursor(&rWindow);
#endif

}

/**************  METODOS PRINCIPALES **************/

void Game::run() //Metodo principal
{
    Reloj clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; //Tiempo desde el ultimo cambio de frame

    while (motor->isWindowOpen()) {
        sf::Time elapsedTime = clock.restart(); //Actualizamos variables de tiempo
        timeSinceLastUpdate += elapsedTime;
        processEvents();
        //Llevamos control en las actualizaciones por frame
        while (timeSinceLastUpdate > timePerFrame) // 15 veces/segundo
        {
            timeSinceLastUpdate -= timePerFrame;
            //Realizamos actualizaciones
            update(timePerFrame);

        }

        interpolation = (float) std::min(1.f, timeSinceLastUpdate.asSeconds() / timePerFrame.asSeconds());
        render(interpolation, elapsedTime);
    }
}

/***************  METODOS DE FISICA Y DISPLAY  *************/

void Game::update(sf::Time elapsedTime) //Actualiza la fisica
{
    if (estadoInGame == true && EstadoInGame->EstadoActivo) {
        EstadoInGame->Update(elapsedTime);
    }
    if (estadoTransition == true && EstadoTransition->EstadoActivo) {
        EstadoTransition->Update(elapsedTime);
    }
    if (estadoCarga1 == true && EstadoCarga1->EstadoActivo) {
        EstadoCarga1->Update(elapsedTime);
    }
    if(estadoCarga2 == true && EstadoCarga2->EstadoActivo){
        EstadoCarga2->Update(elapsedTime);
    }
    if (estadoMenu == true && EstadoMenu->EstadoActivo) {
        EstadoMenu->Update(elapsedTime);
    }

}

void Game::render(float interpolation, sf::Time elapsedTime) //Dibuja
{
    if (estadoInGame == true && EstadoInGame->EstadoActivo) {
        EstadoInGame->render(interpolation, elapsedTime);
    }
    if (estadoTransition == true && EstadoTransition->EstadoActivo) {
        EstadoTransition->render(interpolation, elapsedTime);
    }

    if (estadoMenu == true && EstadoMenu->EstadoActivo) {

        motor->clear();

        EstadoMenu->render();

        motor->display();
    }
    if (estadoPause == true && EstadoPause->EstadoActivo) {
        EstadoInGame->renderForPause(interpolation, elapsedTime);
        EstadoPause->render(interpolation, elapsedTime);
    }
    if (estadoMuerte == true && EstadoMuerte->EstadoActivo) {
        EstadoInGame->renderForPause(interpolation, elapsedTime);
        EstadoMuerte->render(interpolation, elapsedTime);
    }
    if (estadoCarga1 == true && EstadoCarga1->EstadoActivo) {
        EstadoCarga1->render(interpolation, elapsedTime);
    }
    if (estadoCarga2 == true && EstadoCarga2->EstadoActivo) {
        EstadoCarga2->render(interpolation, elapsedTime);
    }
}

/************** EVENTOS ****************/

void Game::processEvents() //Captura y procesa eventos
{
    sf::Event event;
    while (motor->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                //handlePlayerInput(event.key.code, true);
                if (estadoInGame == true && EstadoInGame->EstadoActivo) {
                    EstadoInGame->handlePlayerInput(event.key.code, true);
                }
                if (estadoMenu == true && EstadoMenu->EstadoActivo) {
                    EstadoMenu->handlePlayerInput(event.key.code, true);
                }

                break;

            case sf::Event::KeyReleased:
                if (estadoInGame == true && EstadoInGame->EstadoActivo) {
                    EstadoInGame->handlePlayerInput(event.key.code, false);
                }
                if (estadoPause == true && EstadoPause->EstadoActivo) {
                    EstadoPause->handlePlayerInput2(event.key.code, true);
                }
                handlePlayerInput(event.key.code, false);
                handlePlayerInput2(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                if (estadoInGame == true && EstadoInGame->EstadoActivo) {
                    EstadoInGame->handleMouseInput(event.mouseButton.button, true);
                }
                if (estadoTransition == true && EstadoTransition->EstadoActivo) {
                    EstadoTransition->handleMouseInput(event.mouseButton.button, true);
                }
                if (estadoMenu == true && EstadoMenu->EstadoActivo) {
                    EstadoMenu->handleMouseInput(event.mouseButton.button, true);
                    if (EstadoMenu->getSetectedItemIndex() == 0) {
                        EstadoMenu->pararMusica();
                        EstadoMenu->EstadoActivo = false;
                        EstadoCarga1 = new Carga1();
                        EstadoCarga1 -> EstadoActivo = true;
                        estadoCarga1 = true;

                        thread->launch();
                        
                    }
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (estadoInGame == true && EstadoInGame->EstadoActivo) {
                    EstadoInGame->handleMouseInput(event.mouseButton.button, false);
                }
                if (estadoTransition == true && EstadoTransition->EstadoActivo) {
                    EstadoTransition->handleMouseInput(event.mouseButton.button, false);
                }
                if (estadoMenu == true && EstadoMenu->EstadoActivo) {
                    EstadoMenu->handleMouseInput(event.mouseButton.button, false);
                }

                handleMouseInput(event.mouseButton.button, false);
                break;

            case sf::Event::Closed:
                motor->closeWindow();
                break;

            case sf::Event::Resized:
#ifdef _WIN32
                HWND handler = motor->getSystemHandle();
                RECT rWindow;
                GetWindowRect(handler, &rWindow);
                ClipCursor(&rWindow);
#endif
                motor->setAltoVentana(event.size.height);
                motor->setAnchoVentana(event.size.width);
                motor->SetView(1);
                motor->SetView(2);
                motor->setSizeForView(3, 640, 480);
                motor->SetView(3);
                break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::M) { //Para pasar de nivel
        if (estadoInGame == true) {
            EstadoInGame->EstadoActivo = false;
        }
        if (estadoTransition == true) {
            EstadoTransition->EstadoActivo = true;
            EstadoInGame->musica->stop();
            EstadoTransition->musica->play();
        }
        if (estadoPause == true) {
            EstadoPause->EstadoActivo = false;
        }

    } else if (key == sf::Keyboard::N) {
        if (estadoTransition == true) {
            EstadoTransition->EstadoActivo = false;
        }
        if (estadoInGame == true) {
            EstadoInGame->EstadoActivo = false;
        }
    } else if (key == sf::Keyboard::Return && estadoMenu == true && EstadoMenu->EstadoActivo) {
        if (EstadoMenu->getSetectedItemIndex() == 0) {
            EstadoMenu->pararMusica();
            EstadoMenu->EstadoActivo = false;

            EstadoCarga1 = new Carga1();
            EstadoCarga1 -> EstadoActivo = true;
            estadoCarga1 = true;
           
            thread->launch();
        }
    } else if (key == sf::Keyboard::Return && estadoPause == true && EstadoPause->EstadoActivo) {
        if (EstadoPause->getSetectedItemIndexPause() == 0) {
            EstadoPause->EstadoActivo = false;
            EstadoInGame->EstadoActivo = true;
        }
        if (EstadoPause->getSetectedItemIndexPause() == 2) {
            EstadoPause->EstadoActivo = false;


            delete EstadoTransition;
            EstadoTransition = new Transition();
            delete EstadoInGame;
            EstadoInGame = new InGame();

            EstadoMenu->EstadoActivo = true;
            //////////////////AQUI VAN LOS SETS
        }
    } else if (key == sf::Keyboard::P && estadoInGame == true && EstadoInGame->EstadoActivo) {
        EstadoTransition->EstadoActivo = false;
        EstadoInGame->EstadoActivo = false;
        EstadoPause->SetSetectedItemIndexPause(0);
        EstadoPause->EstadoActivo = true;
    } else if (key == sf::Keyboard::O && estadoInGame == true && EstadoInGame->EstadoActivo) {
        EstadoTransition->EstadoActivo = false;
        EstadoInGame->EstadoActivo = false;
        EstadoMuerte->relojMuerte.restart();
        EstadoMuerte->EstadoActivo = true;
    } else if (key == sf::Keyboard::O && estadoMuerte == true && EstadoMuerte->EstadoActivo) {
        EstadoTransition->EstadoActivo = false;
        EstadoInGame->EstadoActivo = true;
        EstadoMuerte->SetEscala();
        EstadoMuerte->EstadoActivo = false;
    }

}

void Game::cargarInGameTransition() {
    EstadoTransition = new Transition();
    EstadoCarga1 -> transitionCargado();
    EstadoInGame = new InGame();
    EstadoCarga1 -> ingameCargado();
    
    EstadoTransition -> EstadoActivo = true;
    estadoTransition = true;
    EstadoCarga1 -> EstadoActivo = false;
    EstadoMenu->musicaFondo->stop();
    EstadoTransition->musica->play();
}

void Game::handlePlayerInput2(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Return && estadoPause == true && EstadoPause->EstadoActivo) {
        if (EstadoPause->getSetectedItemIndexPause() == 2) {
            EstadoPause->EstadoActivo = false;
            EstadoMenu->SetSetectedItemIndex(0);
            EstadoMenu->EstadoActivo = true;
        }
    }
}

void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (estadoTransition == true && EstadoTransition->preguntaContestada == true) {
        
        EstadoCarga2 = new Carga2();
        EstadoCarga2 -> EstadoActivo = true;
        estadoCarga2 = true;
        


        
        if(EstadoTransition->level==2){
            if(EstadoTransition->getIzqODer()==1){
            EstadoInGame->mapa->leerMapa(EstadoTransition->level,1);
        }
        
        if(EstadoTransition->getIzqODer()==2){
            EstadoInGame->mapa->leerMapa(EstadoTransition->level,2);
        }
        
        }else{
            EstadoInGame->mapa->leerMapa(EstadoTransition->level,0);
        }
        
        EstadoInGame->EstadoActivo = true;


        thread2->launch();

    }

}

void Game::cargarMapa() {
    EstadoTransition->EstadoActivo = false;
    EstadoTransition->preguntaContestada = false;

    EstadoInGame->mapa->~Map();

    EstadoInGame->mapa = new Map();
    //EstadoInGame->mapa->leerMapa(2);
    
    
    EstadoInGame->EstadoActivo = true;
    estadoInGame = true;
    EstadoCarga2->EstadoActivo = false;
    
    EstadoTransition->musica->pause();
    EstadoInGame->musica->play();
    
}
