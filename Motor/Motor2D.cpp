/* 
 * File:   Motor2D.cpp FEngine
 * Author: Paradox
 * 
 * Created on 5 de abril de 2016, 13:52
 */

#include "Motor2D.hpp"
#include "../States/InGame.hpp"
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
    
    mouseSprite = new Sprite();
    mouseSprite->setTexture("resources/Textures/mouse.png");
    mouseSprite->setSmooth(true);
    mouseSprite->setScale(0.2, 0.2);
    mouseSprite->setPosition(20, 20);
    mouseSprite->setOrigin(64, 64);
    
}

void Motor2D::inicializarVentana(std::string titulo, int ancho, int alto,Estilo::_styles estilo) {
    anchoVentana = ancho;
    altoVentana = alto;
    mWindow = new sf::RenderWindow();
    if(estilo == Estilo::DEFAULT){
        mWindow->create(sf::VideoMode(ancho, alto), titulo, sf::Style::Default);
        estiloActual="ventana";
    }else{
        mWindow->create(sf::VideoMode(ancho, alto), titulo, sf::Style::Fullscreen);
        estiloActual="pantalla completa";
    }
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

void Motor2D::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
    mWindow->draw(drawable, states);
}

void Motor2D::clear() {
    mWindow->clear();
}

void Motor2D::display() {
    mWindow->display();
}

std::string Motor2D::getEstilo() {
    return estiloActual;
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

sf::View Motor2D::getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight  ) {

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

void Motor2D::UpdateMouseAndView() {
    float playerPosX = InGame::Instance()->player->getPosition().x;
    float playerPosY = InGame::Instance()->player->getPosition().y;

    sf::FloatRect viewBounds(getCenterFromView(1) - getSizeFromView(1) / 2.f, getSizeFromView(1));

    sf::Vector2f position = getMousePosition();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);

    mouseSprite->setPosition(position.x, position.y);

    float camera_x = (position.x + (playerPosX * 6)) / 7; //Media dando prioridad al jugador
    float camera_y = (position.y + playerPosY * 6) / 7;
    float x = (getCenterFromView(1).x + 0.1 * (camera_x - getCenterFromView(1).x)); //Lo mismo que la funcion lerp
    float y = (getCenterFromView(1).y + 0.1 * (camera_y - getCenterFromView(1).y));
    setCenterForView(1, x, y);
    setSizeForView(1, 640, 480);
    SetView(1);
}

void Motor2D::UpdateMouse() {
    sf::FloatRect viewBounds(getCenterFromView(1) - getSizeFromView(1) / 2.f, getSizeFromView(1));
    sf::Vector2f position = getMousePosition();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);

    mouseSprite->setPosition(position.x, position.y);
}

void Motor2D::DrawMouse() {
    draw(mouseSprite);
}
Sprite* Motor2D::GetMouseSprite() {
    return mouseSprite;
}

