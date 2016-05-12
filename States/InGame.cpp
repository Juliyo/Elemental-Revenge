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
}

InGame::InGame(const InGame& orig) {
}

InGame::~InGame() {


}

void InGame::Clear() {
    while (!caster->empty()) {
        delete caster->back(), caster->pop_back();
    }
    delete caster;

    while (!melee->empty()) {
        delete melee->back(), melee->pop_back();
    }
    delete melee;

    colaEnemigos->clear();
    delete colaEnemigos;

    delete ct;
    delete level;

    delete pathfingind;
    delete physicWorld;

    delete player;
    delete video;
}

void InGame::Inicializar() {
    printf("-------------------OSTIA PUTA YA INICIALIZO INGAME----------------------\n");
    pathfingind = new PathFinding();

    colaEnemigos = new std::deque<Enemigo*>();

    level = new Level();

    video = new Video("resources/Videos/nubes/nube", 30, 495, 500, 0, sf::Vector2f(0.8, 1.4), true, sf::Vector2f(1280, 720));
    physicWorld = new b2World(tmx::SfToBoxVec(sf::Vector2f(0.f, 0.f)));
    physicWorld->SetAllowSleeping(false);
    ct = new ContactListener();
    physicWorld->SetContactListener(ct);

    player = new Player();
    melee = new std::vector<Melee*>();
    caster = new std::vector<Caster*>();

    //Inicializar del boss
    boss = new Boss();
    /*VectorBools = new std::vector<bool>();
    VectorBools->reserve(1);*/



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

    //  std::cout<<"AQUI LLEGO "<<std::endl;
    // level->LoadMap(Niveles::ID::Level1);
    //std::cout<<"HIJO "<<std::endl;
    //level->map->CreateMelees();
    // std::cout<<"DE LA GRAN"<<std::endl;
    // level->map->CreateCasters();
    // std::cout<<"PUTAA "<<std::endl;
    // level->map->CreatePlayer();
    //  std::cout<<"HOSTIA YA "<<std::endl;

    video->Inicializar();
}

void InGame::Update(sf::Time elapsedTime) {
    if (!firstTime) {

        physicWorld->Step(elapsedTime.asSeconds(), 8, 4);

        player -> Update(elapsedTime);

        primerosDeLaCola();

        //**************************ENEMIGOS MELEES**********************//

        for (std::vector<Melee*>::iterator it = melee->begin(); it != melee->end(); ++it) {

            if ((*it)->GetEstado() == Estado::ID::Vivo || (*it)->GetEstado() == Estado::ID::Damaged) {
                (*it)->Update(elapsedTime);
            } else if ((*it)->GetEstado() == Estado::ID::Muriendo) {
                //Si acaba de morir lo borramos del mundo y lo matamos
                (*it)->body->GetWorld()->DestroyBody((*it)->body);
                (*it)->SetEstado(Estado::ID::Muerto);
            }
        }
        //**************************ENEMIGOS CASTER**********************//

        for (std::vector<Caster*>::iterator it = caster->begin(); it != caster->end(); ++it) {
            int x3 = player->getPosition().x - (*it)->getPosition().x;
            int y3 = player->getPosition().y - (*it)->getPosition().y;

            if ((*it)->GetEstado() == Estado::ID::Vivo || (*it)->GetEstado() == Estado::ID::Damaged) {
                if (sqrt(pow(x3, 2) + pow(y3, 2)) < 250) {
                    (*it)->updateDisparoEnemigo(true, elapsedTime, player->getPosition().x, player->getPosition().y);
                } else {
                    (*it)->updateDisparoEnemigo(false, elapsedTime, player->getPosition().x, player->getPosition().y);
                }
                (*it)->Update(elapsedTime, x3, y3, 1);
            } else if ((*it)->GetEstado() == Estado::ID::Muriendo) {
                //Si acaba de morir lo borramos del mundo y lo matamos
                (*it)->body->GetWorld()->DestroyBody((*it)->body);
                (*it)->SetEstado(Estado::ID::Muerto);
            }
        }
        
        //**************************BOSS **********************//
        if (level->map->numEnemigos == 1) {
            if (boss->GetEstado() == Estado::ID::Vivo || boss->GetEstado() == Estado::ID::Damaged) {
                boss->updateAtaqueBossA(true, elapsedTime, player->getPosition().x, player->getPosition().y);
                boss->updateAtaqueBossB(true, elapsedTime, player->getPosition().x, player->getPosition().y);
                boss->updateAtaqueBossC(true, elapsedTime, player->getPosition().x, player->getPosition().y);
                boss->Update(elapsedTime);
            } else if (boss->GetEstado() == Estado::ID::Muriendo) {
                //Si acaba de morir lo borramos del mundo y lo matamos
                boss->body->GetWorld()->DestroyBody(boss->body);
                boss->SetEstado(Estado::ID::Muerto);
            }
        }

        ///

        //**************************RAYO**********************
        bool k = false;
        if (hActivo == 1) {
            k = player->updateRayo(isShooting, rayoAdvancedCast, cdRayoBasicoPausa, cdRayoAvanzadoPausa);
        }

        if ((player->hRayoAvanzado->clockCd.getTiempo() + cdRayoAvanzadoPausa) > player->hRayoAvanzado->getCD() && rayoAdvancedCast) {

            player->hRayoAvanzado->clockCd.restart();
            player->hud->resetRayo2();
            if (cdRayoAvanzadoPausa > 0) {
                cdRayoAvanzadoPausa = 0;
            }
        }

        if ((player->hRayoBasico->clockCd.getTiempo() + cdRayoBasicoPausa) > player->hRayoBasico->getCD() && k) {

            player->hRayoBasico->clockCd.restart();
            player->hud->resetRayo1();
            player->hRayoBasico->primeraVez = true;
            player->hRayoBasico->stopSound();
            player->hRayoBasico->body->SetActive(false);
            if (cdRayoBasicoPausa > 0) {
                cdRayoBasicoPausa = 0;
            }
        }

        //*****************************FUEGO**********************************************  
        player->updateFuego(fuegoBasicCast, fuegoAdvancedCast, elapsedTime, cdFuegoAvanzadoPausa, cdFuegoBasicoPausa);
        if ((player->hFuegoAvanzado->clockCd.getTiempo() + cdFuegoAvanzadoPausa) > player->hFuegoAvanzado->getCD() && fuegoAdvancedCast) {
            player->hFuegoAvanzado->clockCd.restart();
            player->hud->resetFuego2();
            if (cdFuegoAvanzadoPausa > 0) {
                cdFuegoAvanzadoPausa = 0;
            }
        }
        if ((player->clockCDFire.getTiempo() + cdFuegoBasicoPausa) > player->CDFire && fuegoBasicCast) {
            player->clockCDFire.restart();
            player->hud->resetFuego1();
            if (cdFuegoBasicoPausa > 0) {
                cdFuegoBasicoPausa = 0;
            }
        }
        //********************************AGUA*****************************************
        player->updateAgua(aguaBasicCast, aguaAdvancedCast, elapsedTime, cdAguaBasicoPausa, cdAguaAvanzadoPausa);
        if ((player->hAguaBasico->clockCd.getTiempo() + cdAguaBasicoPausa) > player->hAguaBasico->getCD() && aguaBasicCast) {
            player->hAguaBasico->clockCd.restart();
            player->hud->resetAgua1();
            if (cdAguaBasicoPausa > 0) {
                cdAguaBasicoPausa = 0;
            }
        }
        if ((player->hAguaAvanzado->clockCd.getTiempo() + cdAguaAvanzadoPausa) > player->hAguaAvanzado->getCD() && aguaAdvancedCast) {
            player->hAguaAvanzado->clockCd.restart();
            player->hud->resetAgua2();
            if (cdAguaAvanzadoPausa > 0) {
                cdAguaAvanzadoPausa = 0;
            }
        }
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
            player->updateFlash(cdFlashPausa);
        if (hActivo == 4 && !player->isFlashing) {
            printf("Desactivo Flash \n paso a anterior:%d\n", anterior);
            hActivo = anterior;
        }
        if ((player->flash->clockCd.getTiempo() + cdFlashPausa) > player->flash->getCD() && hActivo == 4) {
            printf("CD Flash DESDE PAUSA: %f\n", cdFlashPausa);
            printf("CD Flash CD NUEVO: %f\n", player->flash->clockCd.getTiempo());
            player->flash->clockCd.restart();
            player->hud->resetFlash();
            if (cdFlashPausa > 0) {
                cdFlashPausa = 0;
            }
        }

        if (!video -> getLooped()) {
            video->setDibujar(true);
        }

    } else {
        hActivo = 0;
    }

    firstTime = false;

    if (player->GetVida() == 0) {
        SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/Muerte.wav");

        StateStack::Instance()->SetCurrentState(States::ID::Muerte);
    }
    //printf("Numero de enemigos: %d\n",level->map->numEnemigos);
    if (level->map->numEnemigos == 0) {
        Music *music = Music::Instance();
                music->Stop();
                music->Load(MUSICA::ID::Transiciones);
                music->Play();
        StateStack::Instance()->SetCurrentState(States::ID::Transition);
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
    player->renderFuegoAvanzado(elapsedTime, interpolation);
    //****************************RENDER ENEMIGOS MELEE************************************//
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
                melee->at(i)->CambiarVectorVelocidad();
                melee->at(i)->DrawWithInterpolation(interpolation);
            } else {
                melee->at(i)->DrawAnimationWithOut(melee->at(i)->GetRenderPosition());
                melee->at(i)->currentAnimation = &melee->at(i)->animationMuerte;
            }
        } else { //Si no renderizamos sin interpolacion
            melee->at(i)->DrawAnimationWithOut(melee->at(i)->GetRenderPosition());
            if (StateStack::Instance()->currentState == States::ID::Pause) {
                melee->at(i)->StopAnimation();
            }
        }
    }
    //****************************RENDER DEL BOSS************************************//
    if (level->map->numEnemigos == 1) {
        boss->PlayAnimation(*boss->currentAnimation);
        boss->UpdateAnimation(elapsedTime);
        boss->renderAtaqueA(elapsedTime, interpolation);
        boss->renderAtaqueB(elapsedTime, interpolation);
        boss->renderAtaqueC(elapsedTime, interpolation);
        //Si estamos en Pause o Muerte render con interpolacion
        if (StateStack::Instance()->currentState != States::ID::Pause && StateStack::Instance()->currentState != States::ID::Muerte) {
            if (boss->GetEstado() != Estado::ID::Muerto) {
                int x2 = player->getPosition().x - boss->getPosition().x;
                int y2 = player->getPosition().y - boss->getPosition().y;
                boss->UpdateEnemyAnimation(x2, y2);
                boss->CambiarVectorVelocidad();
                boss->DrawWithInterpolation(interpolation);
            } else {
                boss->DrawAnimationWithOut(boss->GetRenderPosition());
                boss->currentAnimation = &boss->animationMuerte;
            }
        } else { //Si no renderizamos sin interpolacion
            boss->DrawAnimationWithOut(boss->GetRenderPosition());
            if (StateStack::Instance()->currentState == States::ID::Pause) {
                boss->StopAnimation();
            }
        }
    }


    //****************************RENDER ENEMIGOS CASTERS************************************//
    for (int i = 0; i < caster->size(); i++) {
        caster->at(i)->PlayAnimation(*caster->at(i)->currentAnimation);
        caster->at(i)->UpdateAnimation(elapsedTime);
        if (StateStack::Instance()->currentState != States::ID::Pause && StateStack::Instance()->currentState != States::ID::Muerte) {
            if (caster->at(i)->GetEstado() != Estado::ID::Muerto) {
                int x2 = player->getPosition().x - caster->at(i)->getPosition().x;
                int y2 = player->getPosition().y - caster->at(i)->getPosition().y;
                caster->at(i)->UpdateEnemyAnimation(x2, y2);
                caster->at(i)->CambiarVectorVelocidad();
                for (int j = 0; j < 2; j++) {
                    if (caster->at(i)->disparos->at(j)->GetEstado() == Estado::ID::Vivo) {
                        caster->at(i)->disparos->at(j)->PlayAnimation(*caster->at(i)->disparos->at(j)->currentAnimation);
                        caster->at(i)->disparos->at(j)->UpdateAnimation(elapsedTime);
                        caster->at(i)->disparos->at(j)->DrawAnimation(caster->at(i)->disparos->at(j)->GetPreviousPosition(), caster->at(i)->disparos->at(j)->GetPosition(), interpolation);
                    } else if (caster->at(i)->disparos->at(j)->GetEstado() == Estado::ID::Muriendo) {
                        caster->at(i)->disparos->at(j)->PlayAnimation(*caster->at(i)->disparos->at(j)->currentAnimation);
                        caster->at(i)->disparos->at(j)->UpdateAnimation(elapsedTime);
                        caster->at(i)->disparos->at(j)->DrawAnimationWithOut(caster->at(i)->disparos->at(j)->GetRenderPosition());
                    } else {
                        caster->at(i)->disparos->at(j)->StopAnimation();
                    }
                }
                caster->at(i)->DrawWithInterpolation(interpolation);
            } else {
                caster->at(i)->DrawAnimationWithOut(caster->at(i)->GetRenderPosition());
                caster->at(i)->currentAnimation = &caster->at(i)->animationMuerte;
            }
        } else { //Si no renderizamos sin interpolacion
            caster->at(i)->DrawAnimationWithOut(caster->at(i)->GetRenderPosition());
            if (StateStack::Instance()->currentState == States::ID::Pause) {
                caster->at(i)->StopAnimation();
            }
        }

    }

    player->renderFuegoBasico(elapsedTime, interpolation);

    if (StateStack::Instance()->currentState == States::ID::InGame && cambioInGame2Pausa == false) {
        cambioInGame2Pausa = true;
        player->hFuegoAvanzado->clockCd.restart();
        player->clockCDFire.restart();
        player->hAguaBasico->clockCd.restart();
        player->hAguaAvanzado->clockCd.restart();
        player->hRayoAvanzado->clockCd.restart();
        player->hRayoBasico->clockCd.restart();
        player->flash->clockCd.restart();
    }


    if (StateStack::Instance()->currentState == States::ID::Pause && cambioInGame2Pausa == true) {
        cdFuegoAvanzadoPausa += player->hFuegoAvanzado->clockCd.getTiempo();
        cdFuegoBasicoPausa += player->clockCDFire.getTiempo();
        cdAguaAvanzadoPausa += player->hAguaAvanzado->clockCd.getTiempo();
        cdAguaBasicoPausa += player->hAguaBasico->clockCd.getTiempo();
        cdRayoAvanzadoPausa += player->hRayoAvanzado->clockCd.getTiempo();
        cdRayoBasicoPausa += player->hRayoBasico->clockCd.getTiempo();
        cdFlashPausa += player->flash->clockCd.getTiempo();


        cambioInGame2Pausa = false;
    }

    //****************************RAYO************************************
    player->renderRayo(elapsedTime, interpolation);
    //****************************FUEGO************************************

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
        player -> hud->renderHud(elapsedTime, true);
    } else {
        player -> hud->renderHud(elapsedTime, false);
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
        Music *music = Music::Instance();
                music->Stop();
                music->Load(MUSICA::ID::Transiciones);
                music->Play();
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
        SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/Pausa.wav");
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
            if (button == sf::Mouse::Button::Right) {
                printf("Rayo avanzado \n");
                rayoAdvancedCast = isPressed;
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

                fuegoBasicCast = isPressed;
            }
            if (button == sf::Mouse::Right) { //Traslaciones

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

                aguaBasicCast = isPressed;
            }
            if (button == sf::Mouse::Right) { //Traslaciones

                aguaAdvancedCast = isPressed;
            }
            break;
        }

    }
}

void InGame::primerosDeLaCola() {
    int ite = 0;
    while (ite < 4) {
        if (colaEnemigos->size() > 0 && colaEnemigos->at(0) != NULL) {
            if ((colaEnemigos->at(0)->distancia < 500 && colaEnemigos->at(0)->getClassName() == "Melee")) {
                colaEnemigos->at(0)->posiblecamino = pathfingind->buscaCamino(colaEnemigos->at(0)->GetPosition(), player->GetPosition());
                if (colaEnemigos->at(0)->bueno) {
                    colaEnemigos->at(0)->camino = colaEnemigos->at(0)->posiblecamino;
                    colaEnemigos->at(0)->nodoactual = 0;
                }
                colaEnemigos->at(0)->bueno = !colaEnemigos->at(0)->bueno;
            } else if ((colaEnemigos->at(0)->distancia < 700 && colaEnemigos->at(0)->getClassName() == "Caster")) {
                //colaEnemigos->at(0)->posiblecamino = nullptr;
                colaEnemigos->at(0)->posiblecamino = pathfingind->buscaCamino2(colaEnemigos->at(0)->GetPosition(), player->GetPosition());
                if (colaEnemigos->at(0)->bueno) {
                    //colaEnemigos->at(0)->camino = nullptr;
                    colaEnemigos->at(0)->camino = colaEnemigos->at(0)->posiblecamino;
                    colaEnemigos->at(0)->nodoactual = 0;
                }


                colaEnemigos->at(0)->bueno = !colaEnemigos->at(0)->bueno;
                ite--;
            }

            colaEnemigos->at(0)->encola = false;
            colaEnemigos->pop_front();
            ite++;
        } else {
            break;
        }

    }

}