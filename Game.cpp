#include "Game.hpp"

#include "SFML/System.hpp"
#include "Window.hpp"

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
Game::Game(){
    
    Window *p1 = Window::Instance();    //Singleton
    Window *p2 = p1->Instance();
    Window &ref = * Window::Instance(); //Asi coges la referencia a la Window

    
    EstadoInGame=new InGame();   
    EstadoTransition=new Transition();
    
    #ifdef _WIN32
    HWND handler = mWindow->getSystemHandle();
    RECT rWindow;
    GetWindowRect(handler, &rWindow);
    ClipCursor(&rWindow);
#endif
}

/**************  METODOS PRINCIPALES **************/

void Game::run() //Metodo principal
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; //Tiempo desde el ultimo cambio de frame

    while (mWindow->isOpen()) {
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
    if(EstadoInGame->EstadoActivo){
        EstadoInGame->Update(elapsedTime);
    }
    
    if(EstadoTransition->EstadoActivo){
        EstadoTransition->Update(elapsedTime);
    }

}


void Game::render(float interpolation, sf::Time elapsedTime) //Dibuja
{
    if(EstadoInGame->EstadoActivo){
        EstadoInGame->render(interpolation, elapsedTime);
    }
    if(EstadoTransition->EstadoActivo){
        EstadoTransition->render(interpolation, elapsedTime);
    }
}

/************** EVENTOS ****************/

void Game::processEvents() //Captura y procesa eventos
{
   
    sf::Event event;
    while (mWindow->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                EstadoInGame->handlePlayerInput(event.key.code, true);
                
                break;

            case sf::Event::KeyReleased:
                    EstadoInGame->handlePlayerInput(event.key.code, false);

                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::MouseButtonPressed:
                    EstadoInGame->handleMouseInput(event.mouseButton.button, true);
                    EstadoTransition->handleMouseInput(event.mouseButton.button, true);


                break;
            case sf::Event::MouseButtonReleased:
                    EstadoInGame->handleMouseInput(event.mouseButton.button, false);
                    EstadoTransition->handleMouseInput(event.mouseButton.button, false);


                break;

            case sf::Event::Closed:
                mWindow->close();
                break;

            case sf::Event::Resized:
#ifdef _WIN32
                HWND handler = mWindow->getSystemHandle();
                RECT rWindow;
                GetWindowRect(handler, &rWindow);
                ClipCursor(&rWindow);
#endif
                mWindow->setView(EstadoInGame->getLetterboxView( EstadoInGame->mWorldView, event.size.width, event.size.height, 640, 480));
                EstadoInGame->ref.ancho = event.size.width;
                EstadoInGame->ref.alto = event.size.height;
                break;
        }

    }

    
    
}
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::M) { //Esto lo hago para que cuando no estes presionando cambia a false
        EstadoInGame->EstadoActivo=false;
        EstadoTransition->EstadoActivo=true;
    } else if(key == sf::Keyboard::N){
        EstadoTransition->EstadoActivo=false;
        EstadoInGame->EstadoActivo=true;
    }
    
    
}

