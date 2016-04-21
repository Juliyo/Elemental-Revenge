/* 
 * File:   Motor2D.cpp FEngine
 * Author: Paradox
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
    auxiliar = new sf::View();
    transicion = new sf::View();
}

void Motor2D::inicializarVentana(std::string titulo, int ancho, int alto) {
    anchoVentana = ancho;
    altoVentana = alto;
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
        {
            mWindow->setView(getLetterboxView(*pantalla, anchoVentana, altoVentana, 640, 480));
            break;
        }
        case 2:
        {
            mWindow->setView(getLetterboxView(*HUD, anchoVentana, altoVentana, 640, 480));
            break;
        }
        case 3:
        {
            mWindow->setView(getLetterboxView(*auxiliar, anchoVentana, altoVentana, 640, 480));
            break;
        }
        case 4:
            mWindow->setView(getLetterboxView(*transicion, anchoVentana, altoVentana, 640, 480));
            break;
    }
}

void Motor2D::draw(Sprite *sp) {
    mWindow->draw(*sp);
}

void Motor2D::draw(Sprite** sp) {
    draw(*sp);
}

void Motor2D::draw(const sf::Drawable& drawable) {
    mWindow->draw(drawable);
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

sf::View Motor2D::getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight) {

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = viewRatioWidth / (float) viewRatioHeight;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;

        posX = (1 - sizeX) / 2.0;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.0;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    view.zoom(zoomLevel);
    return view;
}

void Motor2D::setAnchoVentana(int ancho) {
    anchoVentana = ancho;
}

void Motor2D::setAltoVentana(int alto) {
    altoVentana = alto;
}

int Motor2D::getAnchoVentana() {
    return anchoVentana;
}

int Motor2D::getAltoVentana() {
    return altoVentana;
}
#ifdef _WIN32

HWND Motor2D::getSystemHandle() {
    return mWindow->getSystemHandle();
}
#endif

bool Motor2D::pollEvent(sf::Event& event) {
    return mWindow->pollEvent(event);
}

void Motor2D::setZoom(float zoom) {
    zoomLevel=zoom;
}

sf::Vector2f Motor2D::getSizeFromView(int view) {
    switch (view) {
        case 0:
            return fondo->getSize();
            break;
        case 1:
        {
            return pantalla->getSize();
            break;
        }
        case 2:
        {
            return HUD->getSize();
            break;
        }
        case 3:
        {
            return auxiliar->getSize();
            break;
        }
        case 4:
        {
            return transicion->getSize();
            break;
        }
    }
}

sf::Vector2f Motor2D::getCenterFromView(int view) {
    switch (view) {
        case 0:
            return fondo->getCenter();
            break;
        case 1:
        {
            return pantalla->getCenter();
            break;
        }
        case 2:
        {
            return HUD->getCenter();
            break;
        }
        case 3:
        {
            return auxiliar->getCenter();
            break;
        }
        case 4:
        {
            return transicion->getCenter();
            break;
        }
    }
}

void Motor2D::setSizeForView(int view, int x, int y) {
    switch (view) {
        case 0:
            fondo->setSize(x, y);
            break;
        case 1:
        {
            pantalla->setSize(x, y);
            break;
        }
        case 2:
        {
            HUD->setSize(x, y);
            break;
        }
        case 3:{
            auxiliar->setSize(x,y);
            break;
        }
        case 4:
        {
            transicion->setSize(x,y);
        }
    }
}

void Motor2D::setCenterForView(int view, int x, int y) {
    switch (view) {
        case 0:
            fondo->setCenter(x, y);
            break;
        case 1:
        {
            pantalla->setCenter(x, y);
            break;
        }
        case 2:
        {
            HUD->setCenter(x, y);
            break;
        }
        case 3:
        {
            auxiliar->setCenter(x,y);
            break;
        }
        case 4:
        {
            transicion->setCenter(x,y);
            break;
        }
    }
}
