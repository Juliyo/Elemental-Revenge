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
#include "../Otros/tmxHelper.hpp"
#include "Pause.hpp"
#include "Muerte.hpp"
#include "StateStack.hpp"

InGame* InGame::mInstance = 0;

InGame* InGame::Instance() {
    if (mInstance == 0) {
        mInstance = new InGame();
    }

    return mInstance;
}

InGame::InGame() {
    motor = Motor2D::Instance();
    /* pause = Pause::Instance();
     muerte = Muerte::Instance();*/


    /* sf::ContextSettings settings;
     settings.antialiasingLevel = 8;*/


    //player->SetScale(0.7,0.7);
    motor->setZoom(0.3f); //1=vista del mundo(nuestra pantalla)

    //updateView();

    //mapa = new Map();
    /*motor->setCenterForView(1, 900,850);
    motor->SetView(1);*/
    level = new Level();

    video = new Video("resources/Videos/nubes/nube", 30, 495, 500, 0, sf::Vector2f(0.8, 1.4), true, sf::Vector2f(1280, 720));
    /*musica = new sf::Music();
    musica->openFromFile("resources/Sounds/InGame.ogg");
    musica->setVolume(50);
        
    musica2 = new sf::Music();
    musica2->openFromFile("resources/Sounds/Magicka2.ogg");
    musica2->setVolume(50);*/
    //Inicializar();
    physicWorld = new b2World(tmx::SfToBoxVec(sf::Vector2f(0.f, 0.f)));
    ct = new ContactListener();
    physicWorld->SetContactListener(ct);
    physicWorld->SetContactFilter(ct);
   
}

InGame::InGame(const InGame& orig) {
}

InGame::~InGame() {
}

void InGame::Inicializar() {
    player = new Player();
    player->SetRectangleColision(14, 12, 36, 52);
    player -> Inicializar(-100.f, -100.f);
    player->CreateBody();
    melee = new std::vector<Melee*>();
    VectorBools = new std::vector<bool>();
    VectorBools->reserve(30);
    melee->reserve(30);
    
    for(int i=0;i<30;i++){

        melee->push_back(new Melee());
        melee->at(i)->Inicializar(1000.f + i * 20, -1000.f + i * 20, Tipo::ID::Rata);
        melee->at(i)->SetRectangleColision(0, 0, 37, 39);
        melee->at(i)->CreateBody();
        bool a=false;
        VectorBools->push_back(a);
    }

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
    updateView();
    level->LoadMap(Niveles::ID::Level1);
    video->Inicializar();

}

void InGame::Update(sf::Time elapsedTime) {

    if (!firstTime) {

        physicWorld->Step(elapsedTime.asSeconds(), 6, 2);

        player -> Update(elapsedTime);

        for (int i = 0; i < melee->size(); i++) {
            
           VectorBools->at(i)= melee->at(i)->HandleMapCollisions(elapsedTime);
            
            
            
        }

        

        for (int i = 0; i < melee->size(); i++) {
            
            if(VectorBools->at(i)==false){
            int x3 = player->getPosition().x - melee->at(i)->getPosition().x;
            int y3 = player->getPosition().y - melee->at(i)->getPosition().y;
            melee->at(i)->Update(elapsedTime,x3,y3,1);
            }
            else{

            int x3;
            int y3;
                srand(time(NULL));

                int random = rand() % 4; // v1 in the range 0 to 99
    
                if(random==0){
                    x3=5000;
                    y3=5000;
                }
                 
                if(random==1){
                     x3=-5000;
                    y3=5000;
                }
                if(random==2){
                     x3=-5000;
                    y3=-5000;
                }
                if(random==3){
                     x3=5000;
                    y3=-5000;
                }
            melee->at(i)->Update(elapsedTime,x3,y3,2);
            }

        }
        

        //**************************RAYO**********************
        if (hActivo == 1) {
            player->updateRayo(isShooting);
        }
        //*****************************FUEGO**********************************************  
        player->updateFuego(fuegoBasicCast, fuegoAdvancedCast, elapsedTime);
        //********************************AGUA*****************************************
        player->updateAgua(aguaBasicCast, aguaAdvancedCast, elapsedTime);
        //********************************HUD*****************************************
        //player->hud->Update();
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

        if (!video -> getLooped()) {
            video->setDibujar(true);
        }

    }else{
        hActivo = 0;
    }

    firstTime = false;

}

void InGame::renderForMuerte(float interpolation, sf::Time elapsedTime) {
    motor->clear();
    motor->SetView(0); //bordes
    motor->draw(spriteRelleno);
    motor->SetView(1);

    updateViewForPause();


    motor->draw(spriteFondo);

    /**********************ARREGLAR***************************/
    /*if (mapa->getMapaActual() == 1) {
        mapa->dibujaMapa1();

    }
    if (mapa->getMapaActual() == 2) {
        mapa->dibujaMapa2();

    }
    if (mapa->getMapaActual() == 3) {
        mapa->dibujaMapa3();
    }
    /*********************************************************/
    player -> DrawAnimationWithOut(player->GetSpriteAnimated().getPosition());

    /* if (mapa->getMapaActual() == 1) {
         mapa->dibuja2Mapa1();
     }
     if (mapa->getMapaActual() == 2) {
         mapa->dibuja2Mapa2();

     }
     if (mapa->getMapaActual() == 3) {
         mapa->dibuja2Mapa3();
     }
     */

    motor->SetView(2); //vista del HUD
    player -> hud->renderHud(elapsedTime);
    if (!video -> getLooped()) {
        video -> PlayVideo();
    }
    //    muerte->render(interpolation, elapsedTime);
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

    /*if (mapa->getMapaActual() == 1) {
        mapa->dibujaMapa1();
    }
    if (mapa->getMapaActual() == 2) {
        mapa->dibujaMapa2();
    }
    if (mapa->getMapaActual() == 3) {
        mapa->dibujaMapa3();
    }*/

    player -> DrawAnimationWithOut(player->GetSpriteAnimated().getPosition());

    /*if (mapa->getMapaActual() == 1) {
        mapa->dibuja2Mapa1();
    }
    if (mapa->getMapaActual() == 2) {
        mapa->dibuja2Mapa2();

    }
    if (mapa->getMapaActual() == 3) {
        mapa->dibuja2Mapa3();
    }*/


    motor->SetView(2); //vista del HUD
    player -> hud->renderHud(elapsedTime);
    if (!video -> getLooped()) {
        video -> PlayVideo();
    }
    //    pause->render(interpolation, elapsedTime);
    motor->SetView(1); //vista del juego

    motor->draw(mouseSprite);

    motor->display();
}

void InGame::Render(float interpolation, sf::Time elapsedTime) {

    motor->clear();
    motor->SetView(0); //bordes
    motor->draw(spriteRelleno);
    motor->SetView(1);

    updateView();


    motor->draw(spriteFondo);
    int x = motor->getMousePosition().x - player -> getPosition().x;
    int y = motor->getMousePosition().y - player -> getPosition().y;
    player ->UpdatePlayerAnimation(x, y);

    level->render();
    
    for (int i = 0; i < melee->size(); i++) {
        if (melee->at(i)->getSpeed().x == 0 && melee->at(i)->getSpeed().y == 0) {
            switch (melee->at(i)->cuadrante) {
                case 1:
                    // melee[i].currentAnimation = &melee->idleAnimationRight;
                    break;
                case 2:
                    //player->currentAnimation = &player->idleAnimationLeft;
                    break;
                case 3:
                    //player->currentAnimation = &player->idleAnimationRight;
                    break;
                case 4:
                    //player->currentAnimation = &player->idleAnimationLeft;
                    break;
            }
        }
        melee->at(i)->PlayAnimation(*melee->at(i)->currentAnimation);
        melee->at(i)->UpdateAnimation(elapsedTime);
        melee->at(i)->DrawWithInterpolation(interpolation);

    }
    //****************************RAYO************************************
    player->renderRayo(elapsedTime, interpolation);
    //****************************FUEGO************************************
    player->renderFuego(elapsedTime, interpolation);
    //****************************AGUA************************************
    player->renderAgua(elapsedTime, interpolation);
    //*********************HEAL**********************************
    player->renderHeal(elapsedTime, interpolation);
    //****************************RENDER PLAYER************************************
    

    player -> PlayAnimation(*player -> currentAnimation);

    /* for(int i=0;i<player->shapes.size();i++){
         motor->draw(player->shapes.at(i));
     }*/

    
    if ((!player->isMovingDown && !player->isMovingLeft && !player->isMovingRight && !player->isMovingUp) && player->castFire.getTiempo() > 0.45f && player->castFire2.getTiempo() > 0.4f) {
        player -> StopAnimation();
    }
    player -> UpdateAnimation(elapsedTime);

    //**************************************FLASH**************************
    player->renderFlash(elapsedTime, interpolation);
    /////////////////////////////////
    player -> DrawWithInterpolation(interpolation);

    for (int i = 0; i < melee->size(); i++) {
        int x2 = player->getPosition().x - melee->at(i)->getPosition().x;
        int y2 = player->getPosition().y - melee->at(i)->getPosition().y;
        melee->at(i)->UpdateEnemyAnimation(x2, y2);
    }

    motor->SetView(2); //vista del HUD
    player -> hud->renderHud(elapsedTime);
    if (!video -> getLooped()) {
        video -> PlayVideo();
    }
    motor->SetView(1); //vista del juego

    motor->draw(mouseSprite);

    motor->display();
}

void InGame::HandleEvents(sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::MouseButtonPressed:
            handleMouseInput(event.mouseButton.button, true);
            break;
        case sf::Event::MouseButtonReleased:
            handleMouseInput(event.mouseButton.button, false);
            break;
    }
}

void InGame::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        player->isMovingUp = isPressed;
    } else if (key == sf::Keyboard::S) {
        player->isMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        player->isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::D) {
        player->isMovingRight = isPressed;
    } else if (key == sf::Keyboard::G && isPressed) {
        player->hRayoBasico->aumentaLVL();
    } else if (key == sf::Keyboard::H && isPressed) {
        player->hRayoAvanzado->aumentaLVL();
    } else if (key == sf::Keyboard::X && isPressed) {
        player->SetPosition(1420, 1230);
    } else if (key == sf::Keyboard::M) {
        //Si pulsamos la M pasamos de nivel
        StateStack::Instance()->SetCurrentState(States::ID::Transition);
        player->isMovingDown = false;
        player->isMovingLeft = false;
        player->isMovingRight = false;
        player->isMovingUp = false;
    } else if ((key == sf::Keyboard::C) || (key == sf::Keyboard::Num1) && !isPressed) {

        hActivo = 0;
        anterior = hActivo;
    } else if (key == sf::Keyboard::V) {

        hActivo = 1;
        anterior = hActivo;
    } else if (key == sf::Keyboard::B) {

        hActivo = 2;
        anterior = hActivo;
    } else if (key == sf::Keyboard::E) {

        hActivo = 4;
        player->isFlashing = isPressed;
    } else if (key == sf::Keyboard::R) {
        hActivo = 3;
        isHealing = isPressed;
    } else if (key == sf::Keyboard::T) {//  QUITAR - SOLO PARA DEBUG
        player->restaVida(1); //QUITAR - SOLO PARA DEBUG
    } else if (key == sf::Keyboard::F && isPressed) {
        player->hRayoBasico->aumentaLVL();
    } else if (key == sf::Keyboard::G && isPressed) {
        player->hRayoAvanzado->aumentaLVL();
    } else if (key == sf::Keyboard::Space && !isPressed) {
        hActivo++;
        anterior = hActivo;
        if (hActivo == 3) {
            hActivo = 0;
            anterior = hActivo;
        }
        player->hud->cambiaHechizo(hActivo + 1);
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
                player->hRayoAvanzado->cast(sf::Vector2f(player->getPosition()), player->hud);
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

void InGame::updateViewForPause() {
    sf::FloatRect viewBounds(motor->getCenterFromView(1) - motor->getSizeFromView(1) / 2.f, motor->getSizeFromView(1));

    sf::Vector2f position = motor->getMousePosition();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);

    mouseSprite.setPosition(position.x, position.y);

}

void InGame::SetPlayer(float x, float y) {
    player->SetPosition(x, y);

}
