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
#include "../Motor/SoundManager.hpp"

InGame* InGame::mInstance = 0;

InGame* InGame::Instance() {
    if (mInstance == 0) {
        mInstance = new InGame();
    }

    return mInstance;
}

InGame::InGame() {
    motor = Motor2D::Instance();
    music = Music::Instance();
    music->Load(MUSICA::ID::Mapa1);
    music->Play();

    pathfingind = new PathFinding();
    SoundManager::Instance()->load();
    /* pause = Pause::Instance();
     muerte = Muerte::Instance();*/


    /* sf::ContextSettings settings;
     settings.antialiasingLevel = 8;*/


    //player->SetScale(0.7,0.7);
    // motor->setZoom(0.3f); //1=vista del mundo(nuestra pantalla)

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
    //physicWorld->SetContactFilter(ct);

}

InGame::InGame(const InGame& orig) {
}

InGame::~InGame() {
}

void InGame::Inicializar() {
    player = new Player();
    player -> Inicializar(1000.f, -1000.f);
    player->SetRectangleColision(14, 12, 36, 52);
    player->CreateBody();
    player->SetEstado(Estado::ID::Vivo);
    melee = new std::vector<Melee*>();
    meleeShapes = new std::vector<sf::CircleShape*>();
    /*melee->reserve(30);
    for (int i = 0; i < 30; i++) {

        melee->push_back(new Melee());
        melee->at(i)->Inicializar(1000.f + i * 20, -1000.f + i * 20, Tipo::ID::Rata);
        melee->at(i)->SetRectangleColision(0, 0, 37, 39);
        melee->at(i)->CreateBody();
    }*/


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

        contFonts.loadFromFile("resources/Fonts/Sansation.ttf");


    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    level->LoadMap(Niveles::ID::Level1);
    level->map->CreateMelees();
    video->Inicializar();
}

void InGame::Update(sf::Time elapsedTime) {

    if (!firstTime) {

        physicWorld->Step(elapsedTime.asSeconds(), 8, 4);

        player -> Update(elapsedTime);

        //**************************ENEMIGOS**********************//
        for (std::vector<Melee*>::iterator it = melee->begin();it != melee->end(); ++it) {
            int x3 = player->getPosition().x - (*it)->getPosition().x;
            int y3 = player->getPosition().y - (*it)->getPosition().y;
            if ((*it)->GetEstado() == Estado::ID::Vivo) {
                (*it)->Update(elapsedTime, x3, y3, 1);
            }else if((*it)->GetEstado() == Estado::ID::Muriendo){
                //Si acaba de morir lo borramos del mundo y lo matamos
                (*it)->body->GetWorld()->DestroyBody((*it)->body);
                (*it)->SetEstado(Estado::ID::Muerto);
            }
        }
        for(int i=0; i<meleeShapes->size();i++){
            meleeShapes->at(i)->setPosition(tmx::BoxToSfVec(melee->at(i)->body->GetPosition()));
        }

        //**************************RAYO**********************
        if (hActivo == 1) {
            player->updateRayo(isShooting);
        }
        //*****************************FUEGO**********************************************  
        player->updateFuego(fuegoBasicCast, fuegoAdvancedCast, elapsedTime, cdFuegoAvanzadoPausa);
        if ((player->hFuegoAvanzado->clockCd.getTiempo()+cdFuegoAvanzadoPausa) > player->hFuegoAvanzado->getCD() && fuegoAdvancedCast) {
            player->hFuegoAvanzado->clockCd.restart();
            player->hud->resetFuego2();
            if(cdFuegoAvanzadoPausa>0){
            cdFuegoAvanzadoPausa=0;
            }
        }
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

    } else {
        hActivo = 0;
    }

    firstTime = false;

    if (player->GetVida() == 0) {
        StateStack::Instance()->SetCurrentState(States::ID::Muerte);
    }

}

void InGame::Render(float interpolation, sf::Time elapsedTime) {

    motor->clear();
    motor->SetView(0); //bordes
    motor->draw(spriteRelleno);
    motor->SetView(1);
    if (StateStack::Instance()->currentState != States::ID::Pause && StateStack::Instance()->currentState != States::ID::Muerte) {
        //Si no esta Pause activo updateamos la vista normal
        motor->UpdateMouseAndView();
    } else {
        //Si esta Pause activo no centramos la vista
        motor->UpdateMouse();
    }

    motor->draw(spriteFondo);

    //Updatea el sprite del jugador en funcino del cuadrante del Mouse 
    if (StateStack::Instance()->currentState != States::ID::Pause && StateStack::Instance()->currentState != States::ID::Muerte) {
        player ->UpdatePlayerAnimation();
    }

    //Renderiza el mapa
    level->render();

    //****************************RENDER ENEMIGOS************************************//
    for (int i = 0; i < melee->size(); i++) {
        melee->at(i)->PlayAnimation(*melee->at(i)->currentAnimation);
        melee->at(i)->UpdateAnimation(elapsedTime);
        //Si estamos en Pause o Muerte render con interpolacion
        if (StateStack::Instance()->currentState != States::ID::Pause && StateStack::Instance()->currentState != States::ID::Muerte) {
            if (melee->at(i)->GetEstado() != Estado::ID::Muerto) {
                int x2 = player->getPosition().x - melee->at(i)->getPosition().x;
                int y2 = player->getPosition().y - melee->at(i)->getPosition().y;
                //if (melee->at(i)->GetEstado() == Estado::ID::Vivo){
                melee->at(i)->UpdateEnemyAnimation(x2, y2);
                //}
                melee->at(i)->DrawWithInterpolation(interpolation);
            } else {
                melee->at(i)->DrawAnimationWithOut(melee->at(i)->GetRenderPosition());
            }
        } else {    //Si no renderizamos sin interpolacion
            melee->at(i)->DrawAnimationWithOut(melee->at(i)->GetRenderPosition());
            if (StateStack::Instance()->currentState == States::ID::Pause) {
                melee->at(i)->StopAnimation();
            }
        }
    }
   /* for(int i=0;i < meleeShapes->size();i++){
        motor->draw(*meleeShapes->at(i));
    }*/
    

    
    if (StateStack::Instance()->currentState == States::ID::InGame && cambioInGame2Pausa==false) {
        cambioInGame2Pausa=true;
        player->hFuegoAvanzado->clockCd.restart();
    }

    
    if (StateStack::Instance()->currentState == States::ID::Pause && cambioInGame2Pausa==true) {
    cdFuegoAvanzadoPausa=player->hFuegoAvanzado->clockCd.getTiempo();
    printf("CD ACTUAL FUEGO AVANZADO: %f\n", cdFuegoAvanzadoPausa);
    cambioInGame2Pausa=false;
    }
    
    //****************************RAYO************************************
    player->renderRayo(elapsedTime, interpolation);
    //****************************FUEGO************************************
    player->renderFuego(elapsedTime, interpolation);
    //****************************AGUA************************************
    player->renderAgua(elapsedTime, interpolation);
    //*********************HEAL**********************************
    player->renderHeal(elapsedTime, interpolation);

    //****************************RENDER PLAYER************************************//
    player -> PlayAnimation(*player -> currentAnimation);
    if ((!player->isMovingDown && !player->isMovingLeft && !player->isMovingRight && !player->isMovingUp) && player->castFire.getTiempo() > 0.45f && player->castFire2.getTiempo() > 0.4f) {
        player -> StopAnimation();
    }
    player -> UpdateAnimation(elapsedTime);
    if (StateStack::Instance()->currentState != States::ID::Pause && StateStack::Instance()->currentState != States::ID::Muerte) {
        player -> DrawWithInterpolation(interpolation);
    } else {
        player -> DrawAnimationWithOut(player -> GetRenderPosition());
        if (StateStack::Instance()->currentState == States::ID::Pause) {

            player -> StopAnimation();

        }
    }

    //**************************************FLASH**************************
    player->renderFlash(elapsedTime, interpolation);

    
    /////////////////////////////////
    motor->SetView(2); //vista del HUD
        if (StateStack::Instance()->currentState == States::ID::Pause) {
             player -> hud->renderHud(elapsedTime,true);
        }
        else{
            player -> hud->renderHud(elapsedTime,false);
        }
    if (!video -> getLooped()) {
        video -> PlayVideo();
    }
    //Si el Pause está activo es el Pause el que hace el Display
    if (StateStack::Instance()->currentState != States::ID::Pause && StateStack::Instance()->currentState != States::ID::Muerte) {
        motor->SetView(1); //vista del juego

        motor->DrawMouse();

        motor->display();
    }

    if (player->relojMuriendo.getTiempo() > 0.7f && player->GetEstado() == Estado::ID::Muriendo) {

        player->SetEstado(Estado::ID::Muerto);
        player->currentAnimation = &player->Muerto;
    }

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
    } else if (key == sf::Keyboard::P) {
        StateStack::Instance()->SetCurrentState(States::ID::Pause);

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
