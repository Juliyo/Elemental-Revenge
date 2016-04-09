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
    EstadoActivo = true;
    rayo = true;

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
    player -> Inicializar(200.f, 250.f);

    motor->setZoomToView(0.5f, 1); //1=vista del mundo(nuestra pantalla)


}

InGame::InGame(const InGame& orig) {
}

InGame::~InGame() {
}

void InGame::Update(sf::Time elapsedTime) {

    if (rayo) {
        if (!firstTimeRayo) {
            sf::Vector2f movement(0.f, 0.f);
            if (isMovingUp)
                movement.y -= player -> getVelocidad();
            if (isMovingDown)
                movement.y += player -> getVelocidad();
            if (isMovingLeft)
                movement.x -= player -> getVelocidad();
            if (isMovingRight)
                movement.x += player -> getVelocidad();

            player -> Update(movement, elapsedTime);

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
        firstTimeRayo = false;
    } else {

        if (!firstTimeFuego) {

            sf::Vector2f movement(0.f, 0.f);
            if (isMovingUp) {
                movement.y -= player -> getVelocidad();
                //noKeyWasPressed = false;
            }
            if (isMovingDown) {
                movement.y += player -> getVelocidad();
                //noKeyWasPressed = false;
            }
            if (isMovingLeft) {
                movement.x -= player -> getVelocidad();
            }
            if (isMovingRight) {
                movement.x += player -> getVelocidad();
                // noKeyWasPressed = false;
            }
            player -> Update(movement, elapsedTime);
        }
        firstTimeFuego = false;
        sf::Vector2f movement2(0.f, 0.f);
        if (fuegoBasicCast) {
            if (player->contFuego == 49) {
                player->contFuego = 0;
            }
            if (player->clockCDFire.getTiempo() > player->CDFire || player->primercastFuego == true) {
                player->primercastFuego = false;
                player->clockCDFire.restart();
                player->hFuegoBasico[player->contFuego].cast(sf::Vector2f(player->getPosition()));
                player->castFire.restart();
            }
            player->contFuego++;
        }
        for (int aux = 0; aux <= 49; aux++) {
            movement2.x = (40 * cos(player->hFuegoBasico[aux].angleshot2) * 10.0f);
            movement2.y = (40 * sin(player->hFuegoBasico[aux].angleshot2) * 10.0f);
            player->hFuegoBasico[aux].Update2(movement2, elapsedTime);
        }
        if (fuegoAdvancedCast) {

            if (player->hFuegoAvanzado->clockCd.getTiempo() > player->hFuegoAvanzado->getCD() || player->hFuegoAvanzado->primerCast == true) {

                player->hFuegoAvanzado->primerCast = false;
                player->hFuegoAvanzado->tiempoCast.restart();
                player->hFuegoAvanzado->clockCd.restart();
                player->hFuegoAvanzado->lanzado = true;
                player->castFire2.restart();

                player->hFuegoAvanzado->actualSize.x = 0.3;
                player->hFuegoAvanzado->actualSize.y = 0.3;
                player->hFuegoAvanzado->SetScale(0.3, 0.3);
                player->hFuegoAvanzado->cast(sf::Vector2f(player->getPosition()));
            }
        }

        if (player->hFuegoAvanzado->lanzado == true) {

            player->hFuegoAvanzado->cast(sf::Vector2f(player->getPosition()));
        }

    }
}

void InGame::render(float interpolation, sf::Time elapsedTime) {
    motor->clear();

    //Pillamos la view anterior, activamos la del fondo, dibujamos el fondo y volvemos al estado anterior
    //sf::View previa = mWindow->getView();
    motor->SetView(0); //bordes
    //mWindow->setView(mBackgroundView);
    motor->draw(spriteRelleno);
    //mWindow->setView(previa);
    motor->SetView(1);

    updateView();
    motor->draw(spriteFondo);
    if (rayo) {
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
    } else {
        //switch
        int x = motor->getMousePosition().x - player -> getPosition().x;
        int y = motor->getMousePosition().y - player -> getPosition().y;
        player ->UpdatePlayerAnimation(x, y);

        if (player->hFuegoAvanzado->tiempoCast.getTiempo() < player->hFuegoAvanzado->getCast() && player->hFuegoAvanzado->lanzado == true) {
            if (player->hFuegoAvanzado->tiempoCast.getTiempo() > 0.4) {
                player->hFuegoAvanzado->SetScale(player->hFuegoAvanzado->actualSize.x, player->hFuegoAvanzado->actualSize.y);

            }
            player->hFuegoAvanzado->DrawWithInterpolation(interpolation, player->GetPreviousPosition(), player->GetPosition());
        }
        for (int aux = 0; aux <= 49; aux++) {
            player->hFuegoBasico[aux].PlayAnimation(player->hFuegoBasico[aux].animationInicio);
            player->hFuegoBasico[aux].UpdateAnimation(elapsedTime);
            player->hFuegoBasico[aux].DrawAnimation(player->hFuegoBasico[aux].GetPreviousPosition(), player->hFuegoBasico[aux].GetPosition(), interpolation);

        }

        if (player->castFire.getTiempo() < 0.45f) {
            player->SetFrameTime(sf::seconds(0.075f));

        } else {
            player->SetFrameTime(sf::seconds(0.075f));
        }

        if (player->castFire2.getTiempo() < 0.4f) {
            player->SetFrameTime(sf::seconds(0.05f));
            player->hFuegoAvanzado->SetScale(player->hFuegoAvanzado->actualSize.x * 1.1, player->hFuegoAvanzado->actualSize.y * 1.1);
            player->hFuegoAvanzado->actualSize.x *= 1.05;
            player->hFuegoAvanzado->actualSize.y *= 1.05;

        } else {
            player->SetFrameTime(sf::seconds(0.075f));
        }

        player -> PlayAnimation(*player -> currentAnimation);


        if (!isMovingDown && !isMovingLeft && !isMovingRight && !isMovingUp && player->castFire.getTiempo() > 0.45f && player->castFire2.getTiempo() > 0.4f) {
            player -> StopAnimation();
        }
        player -> UpdateAnimation(elapsedTime);


        player -> DrawWithInterpolation(interpolation);
    }



    // previa = mWindow->getView();

    //mWindow->setView(getLetterboxView(mHud, ref.ancho, ref.alto, 640, 480));
    motor->SetView(2); //vista del HUD
    player -> hud->renderHud();
    // mWindow->setView(previa);

    //prueba
    motor->SetView(1); //vista del juego
    //mWindow->draw(mouseSprite);
    motor->draw(mouseSprite);
    // mWindow.draw(mStatisticsText);
    //mWindow->display();
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
    } else if (key == sf::Keyboard::C) {

        rayo = true;
    } else if (key == sf::Keyboard::V) {

        rayo = false;
    } else if (key == sf::Keyboard::R && isPressed) {
        player->hRayoBasico->aumentaLVL();
    } else if (key == sf::Keyboard::T && isPressed) {
        player->hRayoAvanzado->aumentaLVL();
    } else if (key == sf::Keyboard::X && isPressed) {
        isInterpolating = !isInterpolating;
    }
}

void InGame::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (rayo) {
        if (button == sf::Mouse::Button::Left) {
            isShooting = isPressed;
        }
        if (button == sf::Mouse::Button::Right && isPressed == false) {
            player->hRayoAvanzado->cast(sf::Vector2f(player->getPosition()));
        }
    } else {
        if (button == sf::Mouse::Left) {//Traslaciones
            fuegoBasicCast = isPressed;
        }
        if (button == sf::Mouse::Right) { //Traslaciones
            fuegoAdvancedCast = isPressed;
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
    // mWindow->setView(getLetterboxView(mWorldView, ref.ancho, ref.alto, 640, 480));
}