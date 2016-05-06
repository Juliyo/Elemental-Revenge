#include "Game.hpp"
#include <SFML/System.hpp>
#include "../Motor/Mapa.hpp"

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
    motor->inicializarVentana("Hito 2 - HUD", 1280, 720);

    
    stateStack = StateStack::Instance();
    /* EstadoInGame = new InGame();
     EstadoTransition = new Transition();
     EstadoPause = new Pause();
     EstadoMuerte = new Muerte();*/
    /*EstadoPause = Pause::Instance();
    EstadoMuerte = Muerte::Instance();
    EstadoMenu = new Menu2();
    estadoMenu = true;*/

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
    stateStack->GetCurrentState()->Update(elapsedTime);
   /* if (estadoInGame == true && EstadoInGame->EstadoActivo) {
        //Si estado pause esta activo no hacemos el de in game
        if (!EstadoPause->EstadoActivo && !EstadoMuerte->EstadoActivo) {
            EstadoInGame->Update(elapsedTime);
        }
    }
    if (estadoTransition == true && EstadoTransition->EstadoActivo) {
        EstadoTransition->Update(elapsedTime);
    }
    if (estadoCarga1 == true && EstadoCarga1->EstadoActivo) {
        EstadoCarga1->Update(elapsedTime);
    }
    if (estadoCarga2 == true && EstadoCarga2->EstadoActivo) {
        EstadoCarga2->Update(elapsedTime);
    }
    if (estadoMenu == true && EstadoMenu->EstadoActivo) {
        EstadoMenu->Update(elapsedTime);
    }
*/
}

void Game::render(float interpolation, sf::Time elapsedTime) //Dibuja
{
    if(stateStack->currentState == States::ID::Pause || stateStack->currentState == States::ID::Muerte){ //Si estamos en pause renderizamos tambien InGame
        stateStack->GetState(States::ID::InGame)->Render(interpolation,elapsedTime);
    }
    stateStack->GetCurrentState()->Render(interpolation,elapsedTime);
 /*   if (estadoInGame == true && EstadoInGame->EstadoActivo) {
        if (!EstadoPause->EstadoActivo && !EstadoMuerte->EstadoActivo) { //No esta ni muerte ni pause activo
            EstadoInGame->render(interpolation, elapsedTime);
        } else if (EstadoPause->EstadoActivo) {
            EstadoInGame->renderForPause(interpolation, elapsedTime); //Pause está activo
        } else {
            EstadoInGame->renderForMuerte(interpolation, elapsedTime);
        }
    }
    if (estadoTransition == true && EstadoTransition->EstadoActivo) {
        EstadoTransition->render(interpolation, elapsedTime);
    }

    if (estadoMenu == true && EstadoMenu->EstadoActivo) {

        motor->clear();

        EstadoMenu->render();

        motor->display();
    }
    if (estadoCarga1 == true && EstadoCarga1->EstadoActivo) {
        EstadoCarga1->render(interpolation, elapsedTime);
    }
    if (estadoCarga2 == true && EstadoCarga2->EstadoActivo) {
        EstadoCarga2->render(interpolation, elapsedTime);
    }*/
}

/************** EVENTOS ****************/

void Game::processEvents() //Captura y procesa eventos
{
    sf::Event event;
    while (motor->pollEvent(event)) {
        stateStack->GetCurrentState()->HandleEvents(event);
        if (event.type == sf::Event::Closed){
            motor->closeWindow();
        }
        if(event.type == sf::Event::Resized){
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
        }
			
      /*  switch (event.type) {
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
                    EstadoPause->handlePlayerInput(event.key.code, true);
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
        }*/
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    /*if (key == sf::Keyboard::M) { //Para pasar de nivel
        if (estadoInGame == true) {
            EstadoInGame->EstadoActivo = false;
        }
        if (estadoTransition == true) {
            EstadoTransition->EstadoActivo = true;
            EstadoInGame->musica->stop();
            EstadoInGame->musica2->stop();
            Motor2D::Instance() -> setZoom(1.f);
            EstadoTransition->musica->play();
        }
        if (estadoPause == true) {
            EstadoPause->EstadoActivo = false;
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
            // EstadoInGame->EstadoActivo = true;
        }
        if (EstadoPause->getSetectedItemIndexPause() == 2) {
            /*EstadoPause->EstadoActivo = false;


            delete EstadoTransition;
            //EstadoTransition = new Transition();
            delete EstadoInGame;
            //EstadoInGame = new InGame();
            EstadoMenu = new Menu2();
            
            EstadoTransition->EstadoActivo = false;
            EstadoMenu->EstadoActivo = true;
            EstadoInGame->EstadoActivo = false;
            exit(0);
            //////////////////AQUI VAN LOS SETS
        }
    } else if (key == sf::Keyboard::P && estadoInGame == true && EstadoInGame->EstadoActivo) {
        EstadoTransition->EstadoActivo = false;
        EstadoPause->SetSetectedItemIndexPause(0);
        EstadoPause->EstadoActivo = true;
    } else if (key == sf::Keyboard::O && estadoInGame == true && EstadoInGame->EstadoActivo) {
        if (!EstadoMuerte->EstadoActivo) {
            EstadoTransition->EstadoActivo = false;
            EstadoMuerte->relojMuerte.restart();
            EstadoMuerte->EstadoActivo = true;
        } else {
            EstadoTransition->EstadoActivo = false;
            EstadoMuerte->SetEscala();
            EstadoMuerte->EstadoActivo = false;
        }
    }*/
    
}

void Game::handlePlayerInput2(sf::Keyboard::Key key, bool isPressed) {
    /*if (key == sf::Keyboard::Return && estadoPause == true && EstadoPause->EstadoActivo) {
        if (EstadoPause->getSetectedItemIndexPause() == 2) {
            EstadoPause->EstadoActivo = false;
            EstadoMenu->SetSetectedItemIndex(0);
            EstadoMenu->EstadoActivo = true;
        }
    }*/
}

void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
  /*  if (estadoTransition == true && EstadoTransition->preguntaContestada == true) {

        EstadoCarga2 = new Carga2();
        EstadoCarga2 -> EstadoActivo = true;
        estadoCarga2 = true;
        
        // EstadoInGame->EstadoActivo = true;


        thread2->launch();

    }*/

}

void Game::cargarInGameTransition() {
    /*EstadoTransition = new Transition();
    EstadoCarga1 -> transitionCargado();
    EstadoInGame = new InGame();
    EstadoPause -> EstadoActivo = false;
    EstadoMuerte -> EstadoActivo = false;
    estadoMuerte = true;
    estadoPause = true;

    EstadoTransition -> EstadoActivo = true;
    estadoTransition = true;
    EstadoCarga1 -> EstadoActivo = false;
    EstadoMenu->musicaFondo->stop();
    EstadoTransition->musica->play();*/
}

void Game::cargarMapa() {
    /*EstadoTransition->EstadoActivo = false;
    EstadoTransition->preguntaContestada = false;

    EstadoInGame->mapa->~Map();

        if (EstadoTransition->level == 1) {
            
            EstadoInGame->musica->openFromFile("resources/Sounds/Bosque.ogg");
            EstadoInGame->musica->setVolume(10);
            EstadoInGame->musica2->play();

        }

        if (EstadoTransition->level == 3) {
            
                 EstadoInGame->musica->openFromFile("resources/Sounds/history.ogg");
            EstadoInGame->musica->setVolume(10);
            EstadoInGame->SetPlayer(2000.f,800.f);

        }
    
    EstadoInGame->mapa = new Map();
    //EstadoInGame->mapa->leerMapa(2,0);
    if (EstadoTransition->level == 2) {
        if (EstadoTransition->getIzqODer() == 1) {
            EstadoInGame->mapa->leerMapa(EstadoTransition->level, 1);
            EstadoInGame->SetPlayer(2000.f,800.f);
        }

        if (EstadoTransition->getIzqODer() == 2) {
            EstadoInGame->mapa->leerMapa(EstadoTransition->level, 2);
            EstadoInGame->SetPlayer(2000.f,800.f);

        }
        EstadoInGame->musica->openFromFile("resources/Sounds/Creepy.ogg");
            EstadoInGame->musica->setVolume(10);

    } else {
        EstadoInGame->mapa->leerMapa(EstadoTransition->level, 0);
    }
    EstadoInGame->video ->setLooped(false);
    EstadoInGame->EstadoActivo = true;
    estadoInGame = true;
    //sf::sleep(sf::seconds(10));
    EstadoCarga2->EstadoActivo = false;

    EstadoTransition->musica->pause();
    EstadoInGame->musica->play();
    //Motor2D::Instance() -> setZoom(0.7f);*/
}
