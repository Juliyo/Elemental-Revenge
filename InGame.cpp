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
    hActivo=0;

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
    
    printf("hActivo es: %d \n",hActivo);
    
    if(firstTimeRayo && firstTimeFuego && firstTimeAgua){
         hActivo=0;
         
    }
   
    //**************************RAYO**********************

        if (!firstTimeRayo) {
            
            if(hActivo==1){
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
            }


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
    
//*****************************FUEGO**********************************************
        if (!firstTimeFuego) {
            if(hActivo==0){
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

    //********************************AGUA*****************************************
         sf::Vector2f movement3(0.f, 0.f);
    if (!firstTimeAgua) {
        
            
            if (isMovingUp) {
            movement3.y -= player -> getVelocidad();
            //noKeyWasPressed = false;
        }
        if (isMovingDown) {
            movement3.y += player -> getVelocidad();
            //noKeyWasPressed = false;
        }
        if (isMovingLeft) {
            movement3.x -= player -> getVelocidad();
        }
        if (isMovingRight) {
            movement3.x += player -> getVelocidad();
            // noKeyWasPressed = false;
        }
        if(hActivo==2){
        player -> Update(movement3, elapsedTime); 
        }


    }
    if (aguaBasicCast) {
        player->hAguaBasico->cast(sf::Vector2f(player->getPosition()));
    }
    if (player -> hAguaBasico->tiempoCast.getTiempo() < 0.5f && player -> hAguaBasico->dibujar == true) {
        player -> hAguaBasico->Update(movement3, elapsedTime,player->getVelocidad());

        if (player->hAguaBasico->GetGlobalBounds().intersects(enemigo[0].getSprite().getGlobalBounds())) {
            enemigo[0].empujado = true;
            enemigo[0].tiempoempujado.restart();
        }

        if (enemigo[0].empujado == true) {
            sf::Vector2f movement3(0.f, 0.f);
            movement3.x = 300 * (cos(player->hAguaBasico->angleshot2) * 1.0f);
            movement3.y = 300 * (sin(player->hAguaBasico->angleshot2) * 1.0f);
            enemigo[0].Update(movement3, elapsedTime);
        }

        if (enemigo[0].tiempoempujado.getTiempo() > 0.5) {
            enemigo[0].empujado = false;
        }

        if (player->hAguaBasico->GetGlobalBounds().intersects(enemigo[1].getSprite().getGlobalBounds())) {
            enemigo[1].empujado = true;
            enemigo[1].tiempoempujado.restart();
        }

        if (enemigo[1].empujado == true) {
            sf::Vector2f movement3(0.f, 0.f);
            movement3.x = 300 * (cos(player->hAguaBasico->angleshot2) * 1.0f);
            movement3.y = 300 * (sin(player->hAguaBasico->angleshot2) * 1.0f);
            enemigo[1].Update(movement3, elapsedTime);
        }

        if (enemigo[1].tiempoempujado.getTiempo() > 0.5) {
            enemigo[1].empujado = false;
        }

    }

    sf::Vector2f movement4(0.f, 0.f);
    if (aguaAdvancedCast) { //onMouseButtonRealeased
        player -> hAguaAvanzado->cast(sf::Vector2f(player -> getPosition()));
    }
    if (player -> hAguaAvanzado->tiempoCast.getTiempo() < 2.5 && player -> hAguaAvanzado->dibujar == true) {
        movement4.x = (40 * cos(player -> hAguaAvanzado->angleshot2) * 11.0f);
        movement4.y = (40 * sin(player -> hAguaAvanzado->angleshot2) * 11.0f);
        player -> hAguaAvanzado->UpdateHechizo(movement4, elapsedTime);

        if (player->hAguaAvanzado->GetGlobalBounds().intersects(enemigo[0].getSprite().getGlobalBounds())) {
            enemigo[0].empujado2 = true;
            enemigo[0].tiempoempujado.restart();
        }

        if (enemigo[0].empujado2 == true) {
            sf::Vector2f movement4(0.f, 0.f);
            movement4.x = 300 * (cos(player->hAguaAvanzado->angleshot2) * 1.0f);
            movement4.y = 300 * (sin(player->hAguaAvanzado->angleshot2) * 1.0f);
            enemigo[0].Update(movement4, elapsedTime);
        }

        if (enemigo[0].tiempoempujado.getTiempo() > 0.5) {
            enemigo[0].empujado2 = false;
        }
    }


    firstTimeAgua = false;
    
    //*********************HEAL**********************************
    
    
    
        if (!firstTimeHeal) {
            if(hActivo==3){
                        sf::Vector2f movement6(0.f, 0.f);
        if (!cantMove) { //Si algo nos lo impide no nos movemos
            if (isMovingUp) {
                movement6.y -= player -> getVelocidad();
                //noKeyWasPressed = false;
            }
            if (isMovingDown) {
                movement6.y += player -> getVelocidad();
                //noKeyWasPressed = false;
            }
            if (isMovingLeft) {
                movement6.x -= player -> getVelocidad();
            }
            if (isMovingRight) {
                movement6.x += player -> getVelocidad();
                // noKeyWasPressed = false;
            }
        }
        player -> Update(movement6, elapsedTime);
            }

        


    }
    if(isHealing){
        player->heal();
    }else{
                if(hActivo==3){
            printf("Desactivo Heal \n paso a anterior:%d\n",anterior);
            hActivo=anterior;
        }
    
    }
    


    firstTimeHeal = false;
    
}

void InGame::render(float interpolation, sf::Time elapsedTime) {
    motor->clear();

    //Pillamos la view anterior, activamos la del fondo, dibujamos el fondo y volvemos al estado anterior
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
         player -> hRayoAvanzado->PlayAnimation(*player -> hRayoAvanzado-> currentAnimation); //Current animation es un puntero a puntero
        if (player -> hRayoAvanzado->draw == true) {

           
            if (player -> hRayoAvanzado->tiempoCast.getTiempo() < player->hRayoAvanzado->getCast()) {
                //switch
                switch (player->cuadrante) {
                    case 1:
                        player->currentAnimation = &player->castingAnimationUpRayo;
                        break;
                    case 2:
                        player->currentAnimation = &player->castingAnimationDownRayo;
                        break;
                    case 3:
                        player->currentAnimation = &player->castingAnimationRightRayo;
                        break;
                    case 4:
                        player->currentAnimation = &player->castingAnimationLeftRayo;
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
                    player->currentAnimation = &player->castingAnimationUpRayo;
                    break;
                case 2:
                    player->currentAnimation = &player->castingAnimationDownRayo;
                    break;
                case 3:
                    player->currentAnimation = &player->castingAnimationRightRayo;
                    break;
                case 4:
                    player->currentAnimation = &player->castingAnimationLeftRayo;
                    break;
            }


            player -> hRayoBasico -> UpdateAnimation(elapsedTime);
            if (player->hRayoBasico->tiempoCast.getTiempo() < player->hRayoBasico->getCast()) {
                
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

  //****************************FUEGO************************************

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
        //switch
        switch (player->cuadrante) {
            case 1:
                player->currentAnimation = &player->fuegoAnimationUp;
                break;
            case 2:
                player->currentAnimation = &player->fuegoAnimationDown;
                break;
            case 3:
                player->currentAnimation = &player->fuegoAnimationRight;
                break;
            case 4:
                player->currentAnimation = &player->fuegoAnimationLeft;
                break;
        }
    } else {
        player->SetFrameTime(sf::seconds(0.075f));
    }


        if (player->castFire2.getTiempo() < 0.4f) {
            player->SetFrameTime(sf::seconds(0.05f));
            player->hFuegoAvanzado->SetScale(player->hFuegoAvanzado->actualSize.x * 1.1, player->hFuegoAvanzado->actualSize.y * 1.1);
            player->hFuegoAvanzado->actualSize.x *= 1.05;
            player->hFuegoAvanzado->actualSize.y *= 1.05;
        //switch
        switch (player->cuadrante) {
            case 1:
                player->currentAnimation = &player->fuego2AnimationUp;
                break;
            case 2:
                player->currentAnimation = &player->fuego2AnimationDown;
                break;
            case 3:
                player->currentAnimation = &player->fuego2AnimationRight;
                break;
            case 4:
                player->currentAnimation = &player->fuego2AnimationLeft;
                break;
        }
        } else {
            player->SetFrameTime(sf::seconds(0.075f));
        }

        
        //****************************AGUA************************************
        
        player -> hAguaAvanzado->PlayAnimation(*player -> hAguaAvanzado-> currentAnimation); //Current animation es un puntero a puntero
    if (player -> hAguaAvanzado->dibujar == true) {
        player->SetFrame(sf::seconds(0.125f));
        //switch
        switch(player->cuadrante){
            case 1:
                player->currentAnimation=&player->castingAnimationUpAgua;
                break;
                case 2:
                player->currentAnimation=&player->castingAnimationDownAgua;
                break;
                case 3:
                player->currentAnimation=&player->castingAnimationRightAgua;
                break;
                case 4:
                player->currentAnimation=&player->castingAnimationLeftAgua;
                break;
        }
        
        
        
        player -> hAguaAvanzado -> UpdateAnimation(elapsedTime);
        if (player -> hAguaAvanzado->tiempoCast.getTiempo() < 2.5) {
            player -> hAguaAvanzado->DrawWithInterpolation( interpolation);
        } else {
            player -> hAguaAvanzado->setDibujar(false);
        }
    }
    player->hAguaBasico->PlayAnimation(player->hAguaBasico->animation);
    if (player->hAguaBasico->dibujar == true) {
        player->SetFrame(sf::seconds(0.125f));
        //switch
        switch(player->cuadrante){
            case 1:
                player->currentAnimation=&player->castingAnimationUpAgua;
                break;
                case 2:
                player->currentAnimation=&player->castingAnimationDownAgua;
                break;
                case 3:
                player->currentAnimation=&player->castingAnimationRightAgua;
                break;
                case 4:
                player->currentAnimation=&player->castingAnimationLeftAgua;
                break;
        }
        player -> hAguaBasico -> UpdateAnimation(elapsedTime);
        if (player->hAguaBasico->tiempoCast.getTiempo() < 0.5f) {
            player->hAguaBasico->DrawWithInterpolation( interpolation);
        } else {
            player->hAguaBasico->setDibujar(false);
        }

    } else {
        player->SetFrame(sf::seconds(0.075f));
        player->hAguaBasico->StopAnimation();
    }
        
        //*********************HEAL**********************************
    
    
player->hHeal->PlayAnimation(player->hHeal->animacion);
    
    if(player->hHeal->dibujar == true){
        //Bloqueamos la movilidad mientras se castea
        cantMove = true;
        //Cambiamos el frameTime de la animacion
        player->SetFrameTime(sf::seconds(0.125f));
        //Vemos en que cuadrante estamos
        switch(player->cuadrante){
            case 1:
                player -> currentAnimation = &player -> healingAnimationUp;
                break;
            case 2:
                player -> currentAnimation = &player -> healingAnimationDown;
                break;
            case 3:
                player -> currentAnimation = &player -> healingAnimationRight;
                break;
            case 4:
                player -> currentAnimation = &player -> healingAnimationLeft;
                break;
        }
        player->hHeal->UpdateAnimation(elapsedTime);
        if(player->hHeal->tiempoCast.getTiempo() < 1.f){
            sf::Vector2f zizu(33.f, 35.f);
            player->hHeal->DrawWithInterpolation(interpolation,(player->GetPreviousPosition()-zizu),(player->GetPosition()-zizu));
        }else{
            player->hHeal->dibujar=false;
        }
    }else{
        //UpdatePlayerAnimation();  //Puede ser necesario llamar a esto
        //Devolvemos el Frametime al original
        player->SetFrameTime(sf::seconds(0.075f));
        //Volvemos a permitir el movimiento
        cantMove = false;
        player->hHeal->StopAnimation();
    }
    
        
        //****************************RENDER PLAYER************************************
        player -> PlayAnimation(*player -> currentAnimation);


        if (!isMovingDown && !isMovingLeft && !isMovingRight && !isMovingUp && player->castFire.getTiempo() > 0.45f && player->castFire2.getTiempo() > 0.4f) {
            player -> StopAnimation();
        }
        player -> UpdateAnimation(elapsedTime);


        player -> DrawWithInterpolation(interpolation);
    
    motor->draw(enemigo[0].getSprite());
    motor->draw(enemigo[1].getSprite());

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
    } else if (key == sf::Keyboard::C) {
        printf("Fuego activo \n");
        hActivo=0;
        anterior=hActivo;
    } else if (key == sf::Keyboard::V) {
printf("Rayo activo \n");
        hActivo=1;
        anterior=hActivo;
    } else if (key == sf::Keyboard::B) {
printf("Agua activo \n");
        hActivo=2;
        anterior=hActivo;
    }else if (key == sf::Keyboard::R){
        printf("Heal activo \n");
        
        hActivo=3;
        isHealing = isPressed;
    }else if (key == sf::Keyboard::T){//  QUITAR - SOLO PARA DEBUG
        player->restaVida(1);         //QUITAR - SOLO PARA DEBUG
    }else if (key == sf::Keyboard::F && isPressed) {
        player->hRayoBasico->aumentaLVL();
    } else if (key == sf::Keyboard::G && isPressed) {
        player->hRayoAvanzado->aumentaLVL();
    } else if (key == sf::Keyboard::X && isPressed) {
        isInterpolating = !isInterpolating;
    }
}

void InGame::handleMouseInput(sf::Mouse::Button button, bool isPressed) {

    switch(hActivo){
        case 1:{
        //hacemos false el resto de casteos por si cambias mientras estabas pulsando
        fuegoBasicCast=false;
        fuegoAdvancedCast=false;
        aguaBasicCast = false; 
        aguaAdvancedCast = false;
        if (button == sf::Mouse::Button::Left) {
            printf("Rayo basico \n");
            isShooting = isPressed;
        }
        if (button == sf::Mouse::Button::Right && isPressed == false) {
            printf("Rayo avanzado \n");
            player->hRayoAvanzado->cast(sf::Vector2f(player->getPosition()));
        }
        break;
        }
        case 0:{
        //hacemos false el resto de casteos por si cambias mientras estabas pulsando
        isShooting=false;
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
        case 2:{
        //hacemos false el resto de casteos por si cambias mientras estabas pulsando
        isShooting=false;
        fuegoBasicCast=false;
        fuegoAdvancedCast=false;
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
    // mWindow->setView(getLetterboxView(mWorldView, ref.ancho, ref.alto, 640, 480));
}