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
    motor = Motor2D::Instance();
    //Estado de Ingame
    EstadoActivo = false;
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


    player = new Player();
    player -> Inicializar(900.f, 850.f);

    motor->setZoomToView(0.5f, 1); //1=vista del mundo(nuestra pantalla)

    mapa = new Map();
}

InGame::InGame(const InGame& orig) {
}

InGame::~InGame() {
}

void InGame::Update(sf::Time elapsedTime) {

    if (!firstTime) {
        sf::Vector2f movement(0.f, 0.f);
        if (isMovingUp)
            movement.y -= player -> getVelocidad();
        if (isMovingDown)
            movement.y += player -> getVelocidad();
        if (isMovingLeft)
            movement.x -= player -> getVelocidad();
        if (isMovingRight)
            movement.x += player -> getVelocidad();

        player -> Update(movement, elapsedTime, mapa);

        if (player->hRayoBasico->tiempoCast.getTiempo() > player->hRayoBasico->getCast() && aux == true) {
            isShooting = false;
            player->hRayoBasico->primerCast = false;
        }

        if ((isShooting && player->hRayoBasico->tiempoCd.getTiempo() > player->hRayoBasico->getCD()) || (isShooting && player->hRayoBasico->primerCast == true)) {//Entra si dispara y el tiempo de enfriamiento ha pasado
            player->hRayoBasico->primerCast = false;
            if (aux == false) {//si es la primera vez que pulsa el boton
                player->hRayoBasico->tiempoCast.restart();

                aux = true; //no entra mas aqui para no hacer restart del cast
            }
            player->hRayoBasico->cast(sf::Vector2f(player->getPosition())); //siempre que entra aqui pintas

        } else {//entras si no disparas o si no ha pasado el tiempo de enfriamiento
            if (aux == true) {//entras si acabas de soltar el raton
                player->hRayoBasico->tiempoCd.restart();
                // std::cout<<"Inicio den CD"<<std::endl;
                aux = false; //no entra mas aqui para no hacer restart dl cd
            }
            player->hRayoBasico->draw = false;
        }
        //avanzado

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && player->hRayoAvanzado->tiempoCast.getTiempo() > player->hRayoBasico->getCast()) {
            player->hRayoAvanzado->draw = false;
            player->hRayoAvanzado->StopAnimation();
        }

    }

    firstTime = false;

}

void InGame::render(float interpolation, sf::Time elapsedTime) {


    motor->clear();
    motor->SetView(0); //bordes
    motor->draw(spriteRelleno);
    motor->SetView(1);

    updateView();
    motor->draw(spriteFondo);

    /**********************ARREGLAR***************************/
    if (mapa->getMapaActual() == 1) {
        mapa->dibujaMapa1();
    }
    if (mapa->getMapaActual() == 2) {
        mapa->dibujaMapa2();
    }
    if (mapa->getMapaActual() == 3) {
        mapa->dibujaMapa2();
    }
    /*********************************************************/

    int x = motor->getMousePosition().x - player -> getPosition().x;
    int y = motor->getMousePosition().y - player -> getPosition().y;
    player ->UpdatePlayerAnimation(x, y);
    player -> hRayoAvanzado->PlayAnimation(*player -> hRayoAvanzado-> currentAnimation); //Current animation es un puntero a puntero
    if (player -> hRayoAvanzado->draw == true) {

        //player->SetFrame(sf::seconds(0.3f));
        if (player -> hRayoAvanzado->tiempoCast.getTiempo() < player->hRayoAvanzado->getCast()) {
            //switch
            switch (player->cuadrante) {
                case 1:
                    player->currentAnimation = &player->castingAnimationUp;
                    break;
                case 2:
                    player->currentAnimation = &player->castingAnimationDown;
                    break;
                case 3:
                    player->currentAnimation = &player->castingAnimationRight;
                    break;
                case 4:
                    player->currentAnimation = &player->castingAnimationLeft;
                    break;
            }
        }
        player -> hRayoAvanzado -> UpdateAnimation(elapsedTime);
        if (player -> hRayoAvanzado->tiempoCast.getTiempo() < player -> hRayoAvanzado->getCast()) {
            player -> hRayoAvanzado->DrawWithOutInterpolation();

        }
    } else {
        player->hRayoAvanzado->StopAnimation();
    }
    player->hRayoBasico->PlayAnimation(*player->hRayoBasico->currentAnimation);
    if (player->hRayoBasico->draw == true) {
        player->SetFrame(sf::seconds(0.125f));
        //switch
        switch (player->cuadrante) {
            case 1:
                player->currentAnimation = &player->castingAnimationUp;
                break;
            case 2:
                player->currentAnimation = &player->castingAnimationDown;
                break;
            case 3:
                player->currentAnimation = &player->castingAnimationRight;
                break;
            case 4:
                player->currentAnimation = &player->castingAnimationLeft;
                break;
        }


        player -> hRayoBasico -> UpdateAnimation(elapsedTime);
        if (player->hRayoBasico->tiempoCast.getTiempo() < player->hRayoBasico->getCast()) {
            //printf("Posicion del animation:%f-%f\n",player->getPhysics()->GetPosition().x,player->getPhysics()->GetPosition().y);
            player->hRayoBasico->SetFrame(sf::seconds(0.075f));
            player->hRayoBasico->currentAnimation = &player->hRayoBasico->animationDurante;

            if (player->hRayoBasico->tiempoCast.getTiempo() < 1.0f) {


                player->hRayoBasico->SetFrame(sf::seconds(0.125f));
                player->hRayoBasico->currentAnimation = &player->hRayoBasico->PrimeraAnimacion;

            }


            player->hRayoBasico->DrawWithInterpolation(interpolation, player->GetPreviousPosition(), player->GetPosition());
        } else {

            player->hRayoBasico->draw = false;
        }

    } else {
        player->SetFrame(sf::seconds(0.075f));
        player->hRayoBasico->StopAnimation();
    }
    //printf("%f",player->hRayoBasico->tiempoCast.getTiempo());

    player -> PlayAnimation(*player -> currentAnimation);


    if ((!isMovingDown && !isMovingLeft && !isMovingRight && !isMovingUp) || player->hRayoBasico->draw == true) {
        player -> StopAnimation();
    }
    player -> UpdateAnimation(elapsedTime);

    player -> DrawWithInterpolation(interpolation);

    if (mapa->getMapaActual() == 1) {
        mapa->dibuja2Mapa1();
    }
    if (mapa->getMapaActual() == 2) {
        mapa->dibuja2Mapa2();

    }
    if (mapa->getMapaActual() == 3) {
        mapa->dibuja2Mapa3();
    }

    motor->SetView(2); //vista del HUD
    player -> hud->renderHud();

    motor->SetView(1); //vista del juego

    motor->draw(mouseSprite);

    motor->display();
}

void InGame::renderForPause(float interpolation, sf::Time elapsedTime) {
    motor->clear();
    motor->SetView(0); //bordes
    motor->draw(spriteRelleno);
    motor->SetView(1);
    
    updateViewForPause();
    motor->draw(spriteFondo);

    if (mapa->getMapaActual() == 1) {
        mapa->dibujaMapa1();
    }
    if (mapa->getMapaActual() == 2) {
        mapa->dibujaMapa2();

    }
    if (mapa->getMapaActual() == 3) {
        mapa->dibujaMapa2();
    }

    player->Draw();
    motor->draw(player->GetSpriteAnimated());

    if (mapa->getMapaActual() == 1) {
        mapa->dibujaMapa1();
    }
    if (mapa->getMapaActual() == 2) {
        mapa->dibujaMapa2();

    }
    if (mapa->getMapaActual() == 3) {
        mapa->dibujaMapa2();
    }
    
    motor->SetView(2); //vista del HUD
    player -> hud->renderHud();

    motor->SetView(1); //vista del juego


    //motor->display();
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
    } else if (key == sf::Keyboard::R && isPressed) {
        player->hRayoBasico->aumentaLVL();
    } else if (key == sf::Keyboard::T && isPressed) {
        player->hRayoAvanzado->aumentaLVL();
    } else if (key == sf::Keyboard::X && isPressed) {
        isInterpolating = !isInterpolating;
    }
}

void InGame::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left) {
        isShooting = isPressed;
    }
    if (button == sf::Mouse::Button::Right && isPressed == false) {
        player->hRayoAvanzado->cast(sf::Vector2f(player->getPosition()));
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
    // mWindow->setView(getLetterboxView(mWorldView, ref.ancho, ref.alto, 640, 480));
}

void InGame::updateViewForPause() {
    motor->setCenterForView(1, motor->getCenterFromView(1).x, motor->getCenterFromView(1).y);
    motor->setSizeForView(1, 640, 480);
    motor->SetView(1);
}