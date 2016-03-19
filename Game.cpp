#include "Game.hpp"
#include <cmath>
#include <math.h>
//SOLO EN WINDOWS
#ifdef _WIN32
#include <Windows.h>
#endif
#define M_PI          3.141592653589793238462643383279502884 /* pi */
/************ VARIABLES GLOBALES ************/
const sf::Time Game::timePerFrame = sf::seconds(1.f / 15.f);
int ancho = 1280, alto = 720;
const float segStatistics = 0.5f; //segundos de refresco de las estadisticas

/************ CONSTRUCTOR **************/
Game::Game()
: mWindow(sf::VideoMode(ancho, alto), "Hito 1 - Interpolacion y camara - LETTERBOX", sf::Style::Default)
, mWorldView(mWindow.getDefaultView())
, contFonts()
, texturaFondo()
, spriteFondo()
, mStatisticsText()
, isMovingUp(false)
, isMovingDown(false)
, isMovingRight(false)
, isMovingLeft(false)
, firstTime(true)
, isInterpolating(false) {
    mWindow.setFramerateLimit(60); //Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    mWindow.setVerticalSyncEnabled(true);

    mWorldView.zoom(0.5f);
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
#ifdef _WIN32
    HWND handler = mWindow.getSystemHandle();
    RECT rWindow;
    GetWindowRect(handler, &rWindow);
    ClipCursor(&rWindow);
#endif
    //Configuramos Items
    player = new Player();
    player -> Inicializar(200.f, 250.f);


}

/**************  METODOS PRINCIPALES **************/

void Game::run() //Metodo principal
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; //Tiempo desde el ultimo cambio de frame

    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart(); //Actualizamos variables de tiempo
        timeSinceLastUpdate += elapsedTime;
        processEvents();
        //Llevamos control en las actualizaciones por frame
        while (timeSinceLastUpdate > timePerFrame) // 15 veces/segundo
        {
            timeSinceLastUpdate -= timePerFrame;
            //Realizamos actualizaciones
            update(timePerFrame);

        }

        interpolation = (float) std::min(1.f, timeSinceLastUpdate.asSeconds() / timePerFrame.asSeconds());
        render(interpolation, elapsedTime);
    }
}

/***************  METODOS DE FISICA Y DISPLAY  *************/

void Game::update(sf::Time elapsedTime) //Actualiza la fisica
{
    if (!firstTime) {
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
    firstTime = false;

    sf::Vector2f movement2(0.f, 0.f);
    if (fuegoBasicCast) {
        if (player->contFuego == 49) {
            player->contFuego = 0;
        }
        if (player->clockCDFire.getElapsedTime().asSeconds() > player->CDFire || player->primercastFuego == true) {
            player->primercastFuego = false;
            player->clockCDFire.restart();
            player->hFuegoBasico[player->contFuego].cast(sf::Vector2f(player->getPosition()), &mWindow);
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
        if (player->hFuegoAvanzado->clockCd.getElapsedTime().asSeconds() > player->hFuegoAvanzado->getCD() || player->hFuegoAvanzado->primerCast == true) {
            player->hFuegoAvanzado->primerCast = false;
            player->hFuegoAvanzado->tiempoCast.restart();
            player->hFuegoAvanzado->clockCd.restart();
            player->hFuegoAvanzado->lanzado = true;
            player->castFire2.restart();

            player->hFuegoAvanzado->actualSize.x = 0.3;
            player->hFuegoAvanzado->actualSize.y = 0.3;
            player->hFuegoAvanzado->SetScale(0.3,0.3);
            player->hFuegoAvanzado->cast(sf::Vector2f(player->getPosition()), &mWindow);
        }
    }
    if (player->hFuegoAvanzado->lanzado == true) {
        player->hFuegoAvanzado->cast(sf::Vector2f(player->getPosition()), &mWindow);
    }

}

void Game::updateView() {

    sf::Vector2f mousePosition = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
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

    mWindow.setView(getLetterboxView(mWorldView, ancho, alto, 640, 480));
}

void Game::render(float interpolation, sf::Time elapsedTime) //Dibuja
{
    mWindow.clear();

    //Pillamos la view anterior, activamos la del fondo, dibujamos el fondo y volvemos al estado anterior
    sf::View previa = mWindow.getView();
    mWindow.setView(mBackgroundView);
    mWindow.draw(spriteRelleno);
    mWindow.setView(previa);

    updateView();
    mWindow.draw(spriteFondo);

    UpdatePlayerAnimation();


    if (player->hFuegoAvanzado->tiempoCast.getElapsedTime().asSeconds() < player->hFuegoAvanzado->getCast() && player->hFuegoAvanzado->lanzado == true) {
        if (player->hFuegoAvanzado->tiempoCast.getElapsedTime().asSeconds() > 0.4) {
            player->hFuegoAvanzado->SetScale(player->hFuegoAvanzado->actualSize.x, player->hFuegoAvanzado->actualSize.y);

        }
        player->hFuegoAvanzado->DrawWithInterpolation(mWindow, interpolation, player->GetPreviousPosition(), player->GetPosition());
    }
    for (int aux = 0; aux <= 49; aux++) {
        player->hFuegoBasico[aux].PlayAnimation(player->hFuegoBasico[aux].animationInicio);
        player->hFuegoBasico[aux].UpdateAnimation(elapsedTime);
        player->hFuegoBasico[aux].DrawAnimation(mWindow, player->hFuegoBasico[aux].GetPreviousPosition(), player->hFuegoBasico[aux].GetPosition(), interpolation);

    }

    if (player->castFire.getElapsedTime().asSeconds() < 0.45f) {
        player->SetFrameTime(sf::seconds(0.075f));
        //switch
        switch (cuadrante) {
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

    if (player->castFire2.getElapsedTime().asSeconds() < 0.4f) {
        player->SetFrameTime(sf::seconds(0.05f));
        player->hFuegoAvanzado->SetScale(player->hFuegoAvanzado->actualSize.x * 1.1, player->hFuegoAvanzado->actualSize.y * 1.1);
        player->hFuegoAvanzado->actualSize.x *= 1.05;
        player->hFuegoAvanzado->actualSize.y *= 1.05;
        //switch
        switch (cuadrante) {
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

    player -> PlayAnimation(*player -> currentAnimation);


    if (!isMovingDown && !isMovingLeft && !isMovingRight && !isMovingUp && player->castFire.getElapsedTime().asSeconds() > 0.45f && player->castFire2.getElapsedTime().asSeconds() > 0.4f) {
        player -> StopAnimation();
    }
    player -> UpdateAnimation(elapsedTime);


    player -> DrawWithInterpolation(mWindow, interpolation);

    previa = mWindow.getView();

    mWindow.setView(getLetterboxView(mHud, ancho, alto, 640, 480));
    player -> hud->renderHud(&mWindow);
    mWindow.setView(previa);


    mWindow.draw(mouseSprite);
    // mWindow.draw(mStatisticsText);
    mWindow.display();
}

/************** EVENTOS ****************/

void Game::processEvents() //Captura y procesa eventos
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;
            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;

            case sf::Event::Resized:
#ifdef _WIN32
                HWND handler = mWindow.getSystemHandle();
                RECT rWindow;
                GetWindowRect(handler, &rWindow);
                ClipCursor(&rWindow);
#endif
                mWindow.setView(getLetterboxView(mWorldView, event.size.width, event.size.height, 640, 480));
                ancho = event.size.width;
                alto = event.size.height;
                break;
        }

    }

}

void Game::UpdatePlayerAnimation() {
    //sf::Vector2f distancia(mouseSprite.getPosition().y - player -> GetRenderPosition().y, mouseSprite.getPosition().x - player -> GetRenderPosition().x);
    cuadrante = 1;
    // 1 -> Arriba
    // 2 -> Abajo
    // 3 -> Derecha
    // 4 -> Izquierda
    int x = mouseSprite.getPosition().x - player -> getPosition().x;
    int y = mouseSprite.getPosition().y - player -> getPosition().y;

    if (abs(y) > abs(x) && y <= 0) {
        cuadrante = 1;
        player -> currentAnimation = &player -> walkingAnimationUp;
    } else if (abs(y) > abs(x) && y > 0) {
        player -> currentAnimation = &player -> walkingAnimationDown;
        cuadrante = 2;
    } else if (abs(x) > abs(y) && x > 0) {
        player -> currentAnimation = &player -> walkingAnimationRight;
        cuadrante = 3;
    } else {
        player -> currentAnimation = &player -> walkingAnimationLeft;
        cuadrante = 4;
    }
}


// Realiza las operaciones correspondientes a cada Evento

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        isMovingUp = isPressed;
    } else if (key == sf::Keyboard::S) {
        isMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::D) {
        isMovingRight = isPressed;
    } else if (key == sf::Keyboard::X && isPressed) {
        isInterpolating = !isInterpolating;
    } else if (key == sf::Keyboard::R)
        isHealing = isPressed;
    else if (key == sf::Keyboard::T)//  QUITAR - SOLO PARA DEBUG
        player->restaVida(1); //        QUITAR - SOLO PARA DEBUG
}

sf::View Game::getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight) {

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

void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Left) {//Traslaciones
        fuegoBasicCast = isPressed;
    }
    if (button == sf::Mouse::Right) { //Traslaciones
        fuegoAdvancedCast = isPressed;
    }
}