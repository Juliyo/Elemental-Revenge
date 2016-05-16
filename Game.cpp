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
    motor = Motor2D::Instance();
    motor->Inicializar();
    motor->inicializarVentana("Hito 3 - Final", 1280, 720,Estilo::FULLSCREEN);

    stateStack = StateStack::Instance();

#ifdef _WIN32
    HWND handler = motor->getSystemHandle();
    RECT rWindow;
    GetWindowRect(handler, &rWindow);
    ClipCursor(&rWindow);
#endif

}

Game::~Game() {
    
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
}

void Game::render(float interpolation, sf::Time elapsedTime) //Dibuja
{
    if(stateStack->currentState == States::ID::Pause || stateStack->currentState == States::ID::Muerte){ //Si estamos en pause renderizamos tambien InGame
        stateStack->GetState(States::ID::InGame)->Render(interpolation,elapsedTime);
    }
    stateStack->GetCurrentState()->Render(interpolation,elapsedTime);
}

/************** EVENTOS ****************/

void Game::processEvents() //Captura y procesa eventos
{
    sf::Event event;
    while (motor->pollEvent(event)) {
        stateStack->GetCurrentState()->HandleEvents(event);
        if (event.type == sf::Event::Closed){
            //delete stateStack;
            motor->closeWindow();
            //delete motor;
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
    }
}
