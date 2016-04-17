#include "Game.hpp"
#include "SFML/System.hpp"
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

    motor = Motor2D::Instance();
    motor->Inicializar();
    motor->inicializarVentana("Hito 2 - Intento Motor", 1280, 720);

    EstadoInGame = new InGame();
    EstadoTransition = new Transition();
    
    EstadoInGame = new InGame();
    EstadoTransition = new Transition();
    EstadoPause = new Pause();
    EstadoMuerte = new Muerte();
    EstadoMenu = new Menu2();

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
    if (EstadoInGame->EstadoActivo) {
        EstadoInGame->Update(elapsedTime);
    }
    if (EstadoTransition->EstadoActivo) {
        EstadoTransition->Update(elapsedTime);
    }
    if (EstadoPause->EstadoActivo) {
        EstadoPause->Update(elapsedTime);
    }
    if (EstadoMenu->EstadoActivo) {
        EstadoMenu->Update(elapsedTime);
    }

}

void Game::render(float interpolation, sf::Time elapsedTime) //Dibuja
{
    if (EstadoInGame->EstadoActivo) {
        EstadoInGame->render(interpolation, elapsedTime);
    }
    if (EstadoTransition->EstadoActivo) {
        EstadoTransition->render(interpolation, elapsedTime);
    }

    if (EstadoMenu->EstadoActivo) {

        mWindow->clear();

        EstadoMenu->render();

        mWindow->display();
    }
    if (EstadoPause->EstadoActivo) {
        EstadoInGame->renderForPause(interpolation, elapsedTime);
        EstadoPause->render(interpolation, elapsedTime);
    }
      if (EstadoMuerte->EstadoActivo) {
        EstadoInGame->renderForPause(interpolation, elapsedTime);
        EstadoMuerte->render(interpolation, elapsedTime);
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
                EstadoInGame->handlePlayerInput(event.key.code, true);
                EstadoMenu->handlePlayerInput(event.key.code, true);
                //EstadoPause->handlePlayerInput(event.key.code, true);
                break;
                
            case sf::Event::KeyReleased:
                EstadoInGame->handlePlayerInput(event.key.code, false);
                EstadoPause->handlePlayerInput2(event.key.code, true);
                handlePlayerInput(event.key.code, false);
                handlePlayerInput2(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                if (EstadoInGame->EstadoActivo) {
                    EstadoInGame->handleMouseInput(event.mouseButton.button, true);
                }
                if (EstadoTransition->EstadoActivo) {
                    EstadoTransition->handleMouseInput(event.mouseButton.button, true);
                }
                if (EstadoMenu->EstadoActivo) {
                    EstadoMenu->handleMouseInput(event.mouseButton.button, true);
                    if (EstadoMenu->getSetectedItemIndex() == 0) {
                        EstadoMenu->EstadoActivo = false;
                        EstadoTransition->EstadoActivo = true;
                    }
                }
                break;
                
            case sf::Event::MouseButtonReleased:
                EstadoInGame->handleMouseInput(event.mouseButton.button, false);
                EstadoTransition->handleMouseInput(event.mouseButton.button, false);
                EstadoMenu->handleMouseInput(event.mouseButton.button, false);
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
                motor->SetView(3);
                break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::M) { //Para pasar de nivel
        EstadoInGame->EstadoActivo = false;
        EstadoTransition->EstadoActivo = true;
        EstadoPause->EstadoActivo = false;
    } else if (key == sf::Keyboard::N) {
        EstadoTransition->EstadoActivo = false;
        EstadoInGame->EstadoActivo = true;
    } else if (key == sf::Keyboard::Return && EstadoMenu->EstadoActivo) {
        if (EstadoMenu->getSetectedItemIndex() == 0) {
            EstadoMenu->pararMusica();
            EstadoMenu->EstadoActivo = false;
            EstadoTransition->EstadoActivo = true;
        }
    } else if (key == sf::Keyboard::Return && EstadoPause->EstadoActivo) {
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
    } else if (key == sf::Keyboard::P && EstadoInGame->EstadoActivo) {
        EstadoTransition->EstadoActivo = false;
        EstadoInGame->EstadoActivo = false;
        EstadoPause->SetSetectedItemIndexPause(0);
        EstadoPause->EstadoActivo = true;
    }else if (key == sf::Keyboard::O && EstadoInGame->EstadoActivo) {
        EstadoTransition->EstadoActivo = false;
        EstadoInGame->EstadoActivo = false;
        EstadoMuerte->EstadoActivo = true;
    }else if (key == sf::Keyboard::O && EstadoMuerte->EstadoActivo) {
        EstadoTransition->EstadoActivo = false;
        EstadoInGame->EstadoActivo = true;
        EstadoMuerte->EstadoActivo = false;
    }

}

void Game::handlePlayerInput2(sf::Keyboard::Key key, bool isPressed) {


    if (key == sf::Keyboard::Return && EstadoPause->EstadoActivo) {

        if (EstadoPause->getSetectedItemIndexPause() == 2) {
            EstadoPause->EstadoActivo = false;
            

            EstadoMenu->SetSetectedItemIndex(0);
            EstadoMenu->EstadoActivo = true;
        }


    }
}

void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed) {


    if (EstadoTransition->preguntaContestada == true) {
        printf("preguntaContestada es true");
        EstadoTransition->EstadoActivo = false;
        EstadoTransition->preguntaContestada = false;
        
        delete EstadoInGame->mapa;
        
        EstadoInGame->mapa= new Map();
        
        EstadoInGame->mapa->leerMapa(EstadoTransition->level);
        EstadoInGame->EstadoActivo = true;

    }

}
