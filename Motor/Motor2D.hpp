/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor2D.hpp
 * Author: Usuario
 *
 * Created on 5 de abril de 2016, 13:52
 */

#ifndef MOTOR2D_HPP
#define MOTOR2D_HPP

#include "Sprite.hpp"
#include "Reloj.hpp"
#include "Textura.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#ifdef _WIN32
#include <windows.h>
#endif
#include <vector>


class Motor2D {
public:
    Motor2D();
    static Motor2D* Instance();
    Motor2D(const Motor2D& orig);
    virtual ~Motor2D();
    void SetView(int v);
    void setAnchoVentana(int ancho);
    void setAltoVentana(int alto);
    int getAnchoVentana();
    int getAltoVentana();
    void setZoom(float zoom);

    sf::Vector2f getCenterFromView(int view);
    sf::Vector2f getSizeFromView(int view);
    void setCenterForView(int view, int x, int y);
    void setSizeForView(int view, int x, int y);
#ifdef _WIN32
    HWND getSystemHandle();
#endif
    bool pollEvent(sf::Event& event);
    float getAngleShot(sf::Vector2f posicion);
    void Inicializar();

    void clear();
    void draw(Sprite *sp);
    void draw(Sprite **sp);
    void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
    void display();

    void inicializarVentana(std::string titulo, int ancho, int alto);

    bool isWindowOpen();
    void closeWindow();

    sf::Vector2f getMousePosition();
    sf::RenderWindow *mWindow;
    sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight);
    //Conetenedor de las texturas
    std::map<int, sf::Texture*> Textures;    
    int key = 0;
    
    //Updatea la vista de la camara usando la posicion del jugador
    void UpdateMouseAndView();
    void UpdateMouse();
    void DrawMouse();
private:
    int anchoVentana;
    int altoVentana;
    static Motor2D *mInstance;
    sf::View *fondo;
    sf::View *pantalla;
    sf::View *HUD;
    sf::View *auxiliar;
    sf::View *transicion;
    sf::Vector2f *raton;
    float zoomLevel =1.f;
    
    Sprite *mouseSprite;
};

#endif /* MOTOR2D_HPP */

