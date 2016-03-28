#include "Game.hpp"

#include "SFML/System.hpp"
#include "Window.hpp"

#include <cmath>
#include <math.h>

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
    
    mWindow = ref.GetWindow();
    
    mWindow->setFramerateLimit(60); //Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    mWindow->setVerticalSyncEnabled(true);
    mWindow->setMouseCursorVisible(false);
   
    
    EstadoInGame=new InGame();   
    EstadoTransition=new Transition();
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
        //EstadoTransition->render(interpolation, elapsedTime);
    }
}

/************** EVENTOS ****************/

void Game::processEvents() //Captura y procesa eventos
{
    sf::Event event;
    while (mWindow->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow->close();
                break;
        }
        if(EstadoInGame->EstadoActivo){
            EstadoInGame->processEvents(event);
        
        }
        if(EstadoTransition->EstadoActivo){
            //EstadoTransition->
        }
    }
    
    
}
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::M) { //Esto lo hago para que cuando no estes presionando cambia a false
        EstadoInGame->EstadoActivo=false;
    } else if(key == sf::Keyboard::N){
        EstadoInGame->EstadoActivo=true;
    }
}

