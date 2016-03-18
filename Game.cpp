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
    mWindow.setMouseCursorVisible(false);
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

    enemigo[0].Inicializar(300.f, 350.f);
    enemigo[1].Inicializar(350.f, 450.f);
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
        if (isMovingUp)
            movement.y -= player -> getVelocidad();
        if (isMovingDown)
            movement.y += player -> getVelocidad();
        if (isMovingLeft)
            movement.x -= player -> getVelocidad();
        if (isMovingRight)
            movement.x += player -> getVelocidad();
        
        player -> Update(movement, elapsedTime);
        
        if(player->hRayoBasico->tiempoCast.getElapsedTime().asSeconds()>2.0f && aux==true){
            isShooting=false;
            player->hRayoBasico->primerCast=false;
        }

        if((isShooting  && player->hRayoBasico->tiempoCd.getElapsedTime().asSeconds()>4.0f)|| (isShooting && player->hRayoBasico->primerCast==true)){//Entra si dispara y el tiempo de enfriamiento ha pasado
            
            if(aux==false){//si es la primera vez que pulsa el boton
                player->hRayoBasico->tiempoCast.restart();
                 std::cout<<"Inicio de Casteo"<<std::endl;
                aux=true;//no entra mas aqui para no hacer restart del cast
            }
            player->hRayoBasico->cast(sf::Vector2f(player->getPosition()),&mWindow);//siempre que entra aqui pintas
           
        }else{//entras si no disparas o si no ha pasado el tiempo de enfriamiento
            if(aux==true ){//entras si acabas de soltar el raton
                player->hRayoBasico->tiempoCd.restart();
                std::cout<<"Inicio den CD"<<std::endl;
                aux=false;//no entra mas aqui para no hacer restart dl cd
            }
            player->hRayoBasico->draw=false;
        }
        //avanzado
        
            if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)&& player->hRayoAvanzado->tiempoCast.getElapsedTime().asSeconds()>1){
player->hRayoAvanzado->draw=false;
    }
        
    }

    firstTime = false;
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

    
    int x = mouseSprite.getPosition().x - player -> getPosition().x;
    int y = mouseSprite.getPosition().y - player -> getPosition().y;
    player ->UpdatePlayerAnimation(x,y);
    player -> hRayoAvanzado->PlayAnimation(*player -> hRayoAvanzado-> currentAnimation); //Current animation es un puntero a puntero
    if (player -> hRayoAvanzado->draw == true) {
        player->SetFrame(sf::seconds(0.125f));
        //switch
        switch(player->cuadrante){
            case 1:
                player->currentAnimation=&player->castingAnimationUp;
                break;
                case 2:
                player->currentAnimation=&player->castingAnimationDown;
                break;
                case 3:
                player->currentAnimation=&player->castingAnimationRight;
                break;
                case 4:
                player->currentAnimation=&player->castingAnimationLeft;
                break;
        }
        
        
        
        player -> hRayoAvanzado -> UpdateAnimation(elapsedTime);
        if (player -> hRayoAvanzado->tiempoCast.getElapsedTime().asSeconds() < 3) {
            player -> hRayoAvanzado->DrawWithOutInterpolation(mWindow);
        } else {
            player -> hRayoAvanzado->draw=false;
        }
    }
    player->hRayoBasico->PlayAnimation(*player->hRayoBasico->currentAnimation);
    if (player->hRayoBasico->draw == true) {
        player->SetFrame(sf::seconds(0.125f));
        //switch
        switch(player->cuadrante){
            case 1:
                player->currentAnimation=&player->castingAnimationUp;
                break;
                case 2:
                player->currentAnimation=&player->castingAnimationDown;
                break;
                case 3:
                player->currentAnimation=&player->castingAnimationRight;
                break;
                case 4:
                player->currentAnimation=&player->castingAnimationLeft;
                break;
        }
        
        
        player -> hRayoBasico -> UpdateAnimation(elapsedTime);
        if (player->hRayoBasico->tiempoCast.getElapsedTime().asSeconds() < 3.0f) {
            player->hRayoBasico->DrawWithInterpolation(mWindow, interpolation,player->getPhysics());
        } else {
            player->hRayoBasico->draw=false;
        }

    } else {
        player->SetFrame(sf::seconds(0.075f));
        player->hRayoBasico->StopAnimation();
    }

    player -> PlayAnimation(*player -> currentAnimation);


    if (!isMovingDown && !isMovingLeft && !isMovingRight && !isMovingUp) {
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
            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;
            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
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

    /*Capturamos eventos del teclado directamente*//*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player -> currentAnimation = &player -> walkingAnimationUp;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player -> currentAnimation = &player -> walkingAnimationDown;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player -> currentAnimation = &player -> walkingAnimationLeft;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player -> currentAnimation = &player -> walkingAnimationRight;
        noKeyWasPressed = false;
    }*/

}




// Realiza las operaciones correspondientes a cada Evento

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    /*if(key == sf::Keyboard::W && isPressed) {
        player -> currentAnimation = &player -> walkingAnimationUp;
        isMovingUp = isPressed;
    } else if(key == sf::Keyboard::S && isPressed) {
        player -> currentAnimation = &player -> walkingAnimationDown;
        isMovingDown = isPressed;
    } else if(key == sf::Keyboard::A && isPressed) {
        player -> currentAnimation = &player -> walkingAnimationLeft;
        isMovingLeft = isPressed;
    } else if(key == sf::Keyboard::D && isPressed) {
        player -> currentAnimation = &player -> walkingAnimationRight;
        isMovingRight = isPressed;
    } else */if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        isMovingUp = isPressed;
    } else if (key == sf::Keyboard::S) {
        isMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::D) {
        isMovingRight = isPressed;
    } else if (key == sf::Keyboard::X && isPressed) {
        isInterpolating = !isInterpolating;
    }
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
    if(button == sf::Mouse::Button::Left){
        isShooting = isPressed;
    }
    if(button == sf::Mouse::Button::Right && isPressed==false){
        player->hRayoAvanzado->cast(sf::Vector2f(player->getPosition()),&mWindow);
        
    }

}