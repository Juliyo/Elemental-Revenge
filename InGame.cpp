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
#include "Window.hpp"
//SOLO EN WINDOWS


InGame::InGame() {
    
    //Estado de Ingame
    EstadoActivo=false;
    try {
        texturaFondo.loadFromFile("resources/Textures/grasstext.png");
        contFonts.loadFromFile("resources/Fonts/Sansation.ttf");
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(true);
    spriteFondo.setTexture(texturaFondo);

    texturaRelleno.setSmooth(true);
    texturaRelleno.setRepeated(1);
    spriteRelleno.setTexture(texturaRelleno);
    spriteRelleno.setTextureRect(sf::IntRect(0, 0, 1024, 2048));
    spriteRelleno.setScale(1, 2);
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 2000, 2000));

    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setScale(0.2, 0.2);
    mouseSprite.setPosition(20, 20);
    mouseSprite.setOrigin(64, 64);
    
    player = new Player();
    player -> Inicializar(900.f, 850.f);
    
    mWindow = ref.GetWindow();
    
    mWorldView = mWindow->getDefaultView();


    mapa = new Map();
    //mapa->leerMapa(1);
}

InGame::InGame(const InGame& orig) {
}

InGame::~InGame() {
}




void InGame::Update(sf::Time elapsedTime){
    
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

        if (player->hRayoBasico->tiempoCast.getElapsedTime().asSeconds() > player->hRayoBasico->getCast() && aux == true) {
            isShooting = false;
            player->hRayoBasico->primerCast = false;
        }

        if ((isShooting && player->hRayoBasico->tiempoCd.getElapsedTime().asSeconds() > player->hRayoBasico->getCD()) || (isShooting && player->hRayoBasico->primerCast == true)) {//Entra si dispara y el tiempo de enfriamiento ha pasado
            player->hRayoBasico->primerCast = false;
            if (aux == false) {//si es la primera vez que pulsa el boton
                player->hRayoBasico->tiempoCast.restart();

                aux = true; //no entra mas aqui para no hacer restart del cast
            }
            player->hRayoBasico->cast(sf::Vector2f(player->getPosition()), mWindow); //siempre que entra aqui pintas

        } else {//entras si no disparas o si no ha pasado el tiempo de enfriamiento
            if (aux == true) {//entras si acabas de soltar el raton
                player->hRayoBasico->tiempoCd.restart();
                // std::cout<<"Inicio den CD"<<std::endl;
                aux = false; //no entra mas aqui para no hacer restart dl cd
            }
            player->hRayoBasico->draw = false;
        }
        //avanzado

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && player->hRayoAvanzado->tiempoCast.getElapsedTime().asSeconds() > player->hRayoBasico->getCast()) {
            player->hRayoAvanzado->draw = false;
            player->hRayoAvanzado->StopAnimation();
        }

    }

    firstTime = false;
    
}

void InGame::render(float interpolation, sf::Time elapsedTime){
    
    mWindow->clear();

    //Pillamos la view anterior, activamos la del fondo, dibujamos el fondo y volvemos al estado anterior
    sf::View previa = mWindow->getView();
    mWindow->setView(mBackgroundView);
    mWindow->draw(spriteRelleno);
    mWindow->setView(previa);

    updateView();
    mWindow->draw(spriteFondo);
    mapa->dibuja(*mWindow);
    mapa->dibuja2(*mWindow);


    int x = mouseSprite.getPosition().x - player -> getPosition().x;
    int y = mouseSprite.getPosition().y - player -> getPosition().y;
    player ->UpdatePlayerAnimation(x, y);
    player -> hRayoAvanzado->PlayAnimation(*player -> hRayoAvanzado-> currentAnimation); //Current animation es un puntero a puntero
    if (player -> hRayoAvanzado->draw == true) {

        //player->SetFrame(sf::seconds(0.3f));
        if (player -> hRayoAvanzado->tiempoCast.getElapsedTime().asSeconds() < player->hRayoAvanzado->getCast()) {
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
        if (player -> hRayoAvanzado->tiempoCast.getElapsedTime().asSeconds() < player -> hRayoAvanzado->getCast()) {
            player -> hRayoAvanzado->DrawWithOutInterpolation(*mWindow);

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
        if (player->hRayoBasico->tiempoCast.getElapsedTime().asSeconds() < player->hRayoBasico->getCast()) {
            //printf("Posicion del animation:%f-%f\n",player->getPhysics()->GetPosition().x,player->getPhysics()->GetPosition().y);
            player->hRayoBasico->SetFrame(sf::seconds(0.075f));
            player->hRayoBasico->currentAnimation = &player->hRayoBasico->animationDurante;

            if (player->hRayoBasico->tiempoCast.getElapsedTime().asSeconds() < 1.0f) {


                player->hRayoBasico->SetFrame(sf::seconds(0.125f));
                player->hRayoBasico->currentAnimation = &player->hRayoBasico->PrimeraAnimacion;

            }


            player->hRayoBasico->DrawWithInterpolation(*mWindow, interpolation, player->GetPreviousPosition(), player->GetPosition());
        } else {

            player->hRayoBasico->draw = false;
        }

    } else {
        player->SetFrame(sf::seconds(0.075f));
        player->hRayoBasico->StopAnimation();
    }
    //printf("%f",player->hRayoBasico->tiempoCast.getElapsedTime().asSeconds());

    player -> PlayAnimation(*player -> currentAnimation);


    if ((!isMovingDown && !isMovingLeft && !isMovingRight && !isMovingUp) || player->hRayoBasico->draw == true) {
        player -> StopAnimation();
    }
    player -> UpdateAnimation(elapsedTime);


    player -> DrawWithInterpolation(*mWindow, interpolation);



    
    previa = mWindow->getView();

    mWindow->setView(getLetterboxView(mHud, ref.ancho, ref.alto, 640, 480));
    player -> hud->renderHud(mWindow);
    mWindow->setView(previa);


    mWindow->draw(mouseSprite);

    // mWindow.draw(mStatisticsText);
    mWindow->display();
}

void InGame::renderForPause(float interpolation, sf::Time elapsedTime){
    sf::View previa = mWindow->getView();
    mWindow->setView(mBackgroundView);
    mWindow->draw(spriteRelleno);
    mWindow->setView(previa);
    updateViewForPause();
    previa = mWindow->getView();
   
    mWindow->draw(spriteFondo);
     player->Draw(*mWindow);
     mWindow->draw(player->GetSpriteAnimated());
    
    mWindow->setView(getLetterboxView(mHud, ref.ancho, ref.alto, 640, 480));
    player -> hud->renderHud(mWindow);
    mWindow->setView(previa);
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
    }
    else if (key == sf::Keyboard::R && isPressed) {
        player->hRayoBasico->aumentaLVL();
    }
    else if (key == sf::Keyboard::T && isPressed) {
        player->hRayoAvanzado->aumentaLVL();
    }
    else if (key == sf::Keyboard::X && isPressed) {
        isInterpolating = !isInterpolating;
    }
}

/************** EVENTOS ****************/
/*
void InGame::processEvents() //Captura y procesa eventos
{
    sf::Event event;
    while (mWindow->pollEvent(event)) {
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

            case sf::Event::Closed:
                mWindow->close();
                break;

            case sf::Event::Resized:
#ifdef _WIN32
                HWND handler = mWindow->getSystemHandle();
                RECT rWindow;
                GetWindowRect(handler, &rWindow);
                ClipCursor(&rWindow);
#endif
                mWindow->setView(getLetterboxView( mWorldView, event.size.width, event.size.height, 640, 480));
                ref.ancho = event.size.width;
                ref.alto = event.size.height;
                break;
        }

    }

}*/


void InGame::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left) {
        isShooting = isPressed;
    }
    if (button == sf::Mouse::Button::Right && isPressed == false) {

        player->hRayoAvanzado->cast(sf::Vector2f(player->getPosition()), mWindow);

    }

}

sf::View InGame::getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = viewRatioWidth / (float) viewRatioHeight;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

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

void InGame::updateView() {

    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

    sf::Vector2f position = mousePosition;
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);

    mouseSprite.setPosition(position);

    float camera_x = (mouseSprite.getPosition().x + (player -> getPosition().x * 6)) / 7; //Media dando prioridad al jugador
    float camera_y = (mouseSprite.getPosition().y + player -> getPosition().y * 6) / 7;
    float x = (mWorldView.getCenter().x + 0.1 * (camera_x - mWorldView.getCenter().x)); //Lo mismo que la funcion lerp
    float y = (mWorldView.getCenter().y + 0.1 * (camera_y - mWorldView.getCenter().y));
    mWorldView.setCenter(x, y);
    mWorldView.setSize(640, 480);

    mWindow->setView(getLetterboxView(mWorldView, ref.ancho, ref.alto, 640, 480));
}
void InGame::updateViewForPause() {

    float x = mWorldView.getCenter().x ; //Lo mismo que la funcion lerp
    float y = mWorldView.getCenter().y ;
    mWorldView.setCenter(x, y);
    mWorldView.setSize(640, 480);
    mWindow->setView(getLetterboxView(mWorldView, ref.ancho, ref.alto, 640, 480));
    
}