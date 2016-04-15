/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InGame.cpp
 * Author: joselu
 * 
 * Created on 26 de marzo de 2016, 19:49
 */

#include "InGame.hpp"

//SOLO EN WINDOWS

InGame::InGame() {
    player = Player::Instance();
    motor = Motor2D::Instance();
    //Estado de Ingame
    EstadoActivo = true;

    hActivo = 0;


    try {
        spriteFondo.setTexture("resources/Textures/grasstext.png");
        spriteFondo.setSmooth(true);
        spriteFondo.setTextRect(0, 0, 2000, 2000);
        spriteFondo.setRepeated(true);

        spriteRelleno.setTexture("resources/Textures/background.png");
        spriteRelleno.setTextRect(0, 0, 1024, 2048);
        spriteRelleno.setRepeated(true);
        spriteRelleno.setSmooth(true);
        spriteRelleno.setScale(1, 2);

        mouseSprite.setTexture("resources/Textures/mouse.png");
        mouseSprite.setSmooth(true);
        mouseSprite.setScale(0.2, 0.2);
        mouseSprite.setPosition(20, 20);
        mouseSprite.setOrigin(64, 64);

        contFonts.loadFromFile("resources/Fonts/Sansation.ttf");

    } catch (std::runtime_error& e) {

        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    player -> Inicializar(200.f, 250.f);
    motor->setZoomToView(0.5f, 1); //1=vista del mundo(nuestra pantalla)
    video = new Video("resources/Videos/arbol/tree", 410);
}

InGame::InGame(const InGame& orig) {
}

InGame::~InGame() {
}

void InGame::Update(sf::Time elapsedTime) {

    //*********************PLAYER***********************
    
 
    sf::Vector2f movement(0.f, 0.f);
    if (!firstTime) {
        if (isMovingUp)
            movement.y -= player -> getVelocidad();
        else if (isMovingDown)
            movement.y += player -> getVelocidad();
        else if (isMovingLeft)
            movement.x -= player -> getVelocidad();
        else if (isMovingRight)
            movement.x += player -> getVelocidad();
        player -> Update(movement, elapsedTime);
    } else {
        hActivo = 0;
    }
    firstTime = false;
    //**************************RAYO**********************
    if (hActivo == 1) {
        player->updateRayo(isShooting);
    }
    //*****************************FUEGO**********************************************  
    player->updateFuego(fuegoBasicCast, fuegoAdvancedCast, elapsedTime);
    //********************************AGUA*****************************************
    player->updateAgua(aguaBasicCast, aguaAdvancedCast, elapsedTime, movement);
    //*********************HEAL**********************************

    if (isHealing) {
        player->heal();
    } else {
        if (hActivo == 3) {
            printf("Desactivo Heal \n paso a anterior:%d\n", anterior);
            hActivo = anterior;
        }


    }
    //******************************FLASH********************************************** 
    if (hActivo == 4)
        player->updateFlash();
    if (hActivo == 4 && !player->isFlashing) {
        printf("Desactivo Flash \n paso a anterior:%d\n", anterior);
        hActivo = anterior;
    }

}

void InGame::render(float interpolation, sf::Time elapsedTime) {
    motor->clear();
    motor->SetView(0); //bordes
    motor->draw(spriteRelleno);
    motor->SetView(1);
    updateView();
    motor->draw(spriteFondo);
    //****************************ANIMACION PLAYER************************************
    int x = motor->getMousePosition().x - player -> getPosition().x;
    int y = motor->getMousePosition().y - player -> getPosition().y;
    player ->UpdatePlayerAnimation(x, y);

    //****************************RAYO************************************
    player->renderRayo( elapsedTime, interpolation);
    //****************************FUEGO************************************
    player->renderFuego( elapsedTime, interpolation);
    //****************************AGUA************************************
    player->renderAgua( elapsedTime, interpolation);
    //*********************HEAL**********************************
    player->renderHeal( elapsedTime, interpolation);
    //****************************RENDER PLAYER************************************
    player -> PlayAnimation(*player -> currentAnimation);
    if (!isMovingDown && !isMovingLeft && !isMovingRight && !isMovingUp && player->castFire.getTiempo() > 0.45f && player->castFire2.getTiempo() > 0.4f) {
        player -> StopAnimation();
    }
    player -> UpdateAnimation(elapsedTime);
    //**************************************FLASH**************************
    player->renderFlash( elapsedTime, interpolation);
    /////////////////////////////////


    motor->draw(enemigo[0].getSprite());
    motor->draw(enemigo[1].getSprite());
    //video->PlayVideo();
    motor->SetView(2); //vista del HUD
    
    player -> hud->renderHud();
    
    motor->SetView(1); //vista del juego
    motor->draw(mouseSprite);
    motor->display();
}

void InGame::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        isMovingUp = isPressed;
    } else if (key == sf::Keyboard::S) {
        isMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::D) {
        isMovingRight = isPressed;
    } else if ((key == sf::Keyboard::C) || (key == sf::Keyboard::Num1) && !isPressed) {
        printf("Fuego activo \n");
        hActivo = 0;
        anterior = hActivo;
    } else if (key == sf::Keyboard::V) {
        printf("Rayo activo \n");
        hActivo = 1;
        anterior = hActivo;
    } else if (key == sf::Keyboard::B) {
        printf("Agua activo \n");
        hActivo = 2;
        anterior = hActivo;
    } else if (key == sf::Keyboard::E) {
        printf("Flash activo \n");
        hActivo = 4;
        player->isFlashing = isPressed;
    }
    else if (key == sf::Keyboard::R) {
        printf("Heal activo \n");
        hActivo = 3;
        isHealing = isPressed;
    } else if (key == sf::Keyboard::T) {//  QUITAR - SOLO PARA DEBUG
        player->restaVida(1); //QUITAR - SOLO PARA DEBUG
    } else if (key == sf::Keyboard::F && isPressed) {
        player->hRayoBasico->aumentaLVL();
    } else if (key == sf::Keyboard::G && isPressed) {
        player->hRayoAvanzado->aumentaLVL();
    }else if(key == sf::Keyboard::Space && !isPressed){
        hActivo++;
        anterior = hActivo;
        if(hActivo == 3){
            hActivo = 0;
            anterior = hActivo;
        }
        player->hud->cambiaHechizo(hActivo+1);
    }
}

void InGame::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    switch (hActivo) {
        case 1:
        {
            //hacemos false el resto de casteos por si cambias mientras estabas pulsando
            fuegoBasicCast = false;
            fuegoAdvancedCast = false;
            aguaBasicCast = false;
            aguaAdvancedCast = false;
            if (button == sf::Mouse::Button::Left) {
                printf("Rayo basico \n");
                isShooting = isPressed;
            }
            if (button == sf::Mouse::Button::Right && isPressed == false) {
                printf("Rayo avanzado \n");
                player->hRayoAvanzado->cast(sf::Vector2f(player->getPosition()),player->hud);
            }
            break;
        }
        case 0:
        {
            //hacemos false el resto de casteos por si cambias mientras estabas pulsando
            isShooting = false;
            aguaBasicCast = false;
            aguaAdvancedCast = false;
            if (button == sf::Mouse::Left) {//Traslaciones
                printf("fuego basico \n");
                fuegoBasicCast = isPressed;
            }
            if (button == sf::Mouse::Right) { //Traslaciones
                printf("fuego avanzado \n");
                fuegoAdvancedCast = isPressed;
            }
            break;
        }
        case 2:
        {
            //hacemos false el resto de casteos por si cambias mientras estabas pulsando
            isShooting = false;
            fuegoBasicCast = false;
            fuegoAdvancedCast = false;
            if (button == sf::Mouse::Left) {//Traslaciones
                printf("Agua basico \n");
                aguaBasicCast = isPressed;
            }
            if (button == sf::Mouse::Right) { //Traslaciones
                printf("Agua avanzado \n");
                aguaAdvancedCast = isPressed;
            }
            break;
        }
    }
}

void InGame::updateView() {

    sf::FloatRect viewBounds(motor->getCenterFromView(1) - motor->getSizeFromView(1) / 2.f, motor->getSizeFromView(1));

    sf::Vector2f position = motor->getMousePosition();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);

    mouseSprite.setPosition(position.x, position.y);

    float camera_x = (position.x + (player -> getPosition().x * 6)) / 7; //Media dando prioridad al jugador
    float camera_y = (position.y + player -> getPosition().y * 6) / 7;
    float x = (motor->getCenterFromView(1).x + 0.1 * (camera_x - motor->getCenterFromView(1).x)); //Lo mismo que la funcion lerp
    float y = (motor->getCenterFromView(1).y + 0.1 * (camera_y - motor->getCenterFromView(1).y));
    motor->setCenterForView(1, x, y);
    motor->setSizeForView(1, 640, 480);
    motor->SetView(1);
}