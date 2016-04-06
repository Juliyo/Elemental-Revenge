/* 
 * File:   Motor2D.cpp
 * Author: Usuario
 * 
 * Created on 5 de abril de 2016, 13:52
 */

#include "Motor2D.hpp"
Motor2D* Motor2D::mInstance = 0;

Motor2D* Motor2D::Instance() {
    if (mInstance == 0) {
        mInstance = new Motor2D;
    }
    return mInstance;
}

void Motor2D::Inicializar() {
    raton = new sf::Vector2f();
    fondo = new sf::View();
    pantalla = new sf::View();
    HUD = new sf::View();
}

void Motor2D::inicializarVentana(std::string titulo, int ancho, int alto) {
    mWindow = new sf::RenderWindow();
    mWindow->create(sf::VideoMode(ancho, alto), titulo, sf::Style::Default);
    mWindow->setFramerateLimit(60); //Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    mWindow->setVerticalSyncEnabled(true);
    mWindow->setMouseCursorVisible(false);
}


Motor2D::Motor2D() {
    Inicializar();
}

Motor2D::Motor2D(const Motor2D& orig) {
}

Motor2D::~Motor2D() {
}

void Motor2D::SetView(int v) {
    switch (v) {
        case 0:
            mWindow->setView(*fondo);

            break;
        case 1:
            mWindow->setView(*pantalla);
            break;
        case 2:
            mWindow->setView(*HUD);
            break;
    }
}

void Motor2D::draw(Sprite *sp) {
    mWindow->draw(*sp);
}

void Motor2D::draw(Sprite** sp) {
    draw(*sp);
}

void Motor2D::clear() {
    mWindow->clear();
}

void Motor2D::display() {
    mWindow->display();
}

sf::Vector2f Motor2D::getMousePosition() {
    return mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
}

float Motor2D::getAngleShot(sf::Vector2f posicion) {
    sf::Vector2f mousePosition = getMousePosition();
    return atan2(mousePosition.y - posicion.y, mousePosition.x - posicion.x);
}

void Motor2D::closeWindow() {
    mWindow->close();
}

bool Motor2D::isWindowOpen() {
    return mWindow->isOpen();
}
