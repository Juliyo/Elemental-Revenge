#include "Game.hpp"
#include <cmath>
//SOLO EN WINDOWS
#ifdef _WIN32
#include <Windows.h>
#endif

/************ VARIABLES GLOBALES ************/
const sf::Time Game::timePerFrame = sf::seconds(1.f / 15.f);
const int ancho = 1280, alto = 720;
const float segStatistics = 0.5f; //segundos de refresco de las estadisticas

/************ CONSTRUCTOR **************/
Game::Game()
: mWindow(sf::VideoMode(ancho, alto), "Hito 1 - Interpolacion y camara - LETTERBOX", sf::Style::Default)
, mWorldView(mWindow.getDefaultView())
, contFonts()
, texturaFondo()
, spriteFondo()
, mStatisticsText()
, player()
, isMovingUp(false)
, isMovingDown(false)
, isMovingRight(false)
, isMovingLeft(false)
, firstTime(true)
, isInterpolating(false) {
    mWindow.setFramerateLimit(60); //Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    mWindow.setVerticalSyncEnabled(true);
    //mWindow.setMouseCursorVisible(false);

    mWorldView.zoom(0.5f);
    // Cargamos RECURSOS. Utilizamos los contenedores genericos
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
    spriteRelleno.setTextureRect(sf::IntRect(0,0,1024,2048));
    spriteRelleno.setScale(1,2);
    spriteFondo.setTextureRect(sf::IntRect(0,0,2000,2000));
    
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setScale(0.2,0.2);
    mouseSprite.setPosition(20,20);
#ifdef _WIN32
    HWND handler = mWindow.getSystemHandle();
    RECT rWindow;
    GetWindowRect(handler, &rWindow);
    ClipCursor(&rWindow);
#endif
    //Configuramos Items
    player.Inicializar(200.f, 250.f);

    mStatisticsText.setFont(contFonts);
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(13);
    mStatisticsText.setColor(sf::Color::Black);
    mStatisticsText.setString("Interpolacion Desactivada (X)");
    
    //sf::View letterBox = getLetterboxView(mWindow.getView(),ancho,alto);
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

        render(interpolation);
    }
}

/***************  METODOS DE FISICA Y DISPLAY  *************/

void Game::update(sf::Time elapsedTime) //Actualiza la fisica
{
    
    if (!firstTime) {
        sf::Vector2f movement(0.f, 0.f);
        if (isMovingUp)
            movement.y -= player.getVelocidad();
        if (isMovingDown)
            movement.y += player.getVelocidad();
        if (isMovingLeft)
            movement.x -= player.getVelocidad();
        if (isMovingRight)
            movement.x += player.getVelocidad();
        
        player.Update(movement, elapsedTime);
        
    }

    firstTime = false;
}
void Game::updateView(){
    sf::Vector2f mousePosition = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
    float camera_x = (mousePosition.x + (player.getPosition().x*6))/7;//Media dando prioridad al jugador
    float camera_y = (mousePosition.y + player.getPosition().y*6)/7;
    float x = (mWorldView.getCenter().x+0.1*(camera_x-mWorldView.getCenter().x));//Lo mismo que la funcion lerp
    float y = (mWorldView.getCenter().y+0.1*(camera_y-mWorldView.getCenter().y));
    mWorldView.setCenter(x, y);
    mWorldView.setSize(640, 480);
    
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

    sf::Vector2f position = mousePosition;
    position.x = std::max(position.x, 0.125f * viewBounds.left);
    position.x = std::min(position.x, 0.875f * viewBounds.left + viewBounds.width);
    position.y = std::max(position.y, 0.f );
    position.y = std::min(position.y, (float)alto);
    
    mouseSprite.setPosition(position);
    
    
    
    mStatisticsText.setPosition(mWindow.getPosition().x,mWindow.getPosition().y);
    mWindow.setView(getLetterboxView(mWorldView,ancho,alto));
}
void Game::render(float interpolation) //Dibuja
{
    mWindow.clear();
    
    //Pillamos la view anterior, activamos la del fondo, dibujamos el fondo y volvemos al estado anterior
    sf::View previa = mWindow.getView();
    mWindow.setView(mBackgroundView);
    mWindow.draw(spriteRelleno);
    mWindow.setView(previa);
    
    updateView();
    mWindow.draw(spriteFondo);
    
    //LLAMAR AL DRAW DEL PLAYER
    if (isInterpolating)
        player.DrawWithInterpolation(mWindow, interpolation);
    else
        player.Draw(mWindow);
    
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
                    break;
        }
        
    }
}

// Realiza las operaciones correspondientes a cada Evento

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) //Traslaciones
        isMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        isMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        isMovingRight = isPressed;


    else if (key == sf::Keyboard::X && isPressed) {
        isInterpolating = !isInterpolating;

        if (isInterpolating)
            mStatisticsText.setString("Interpolacion Activada (X)");
        else
            mStatisticsText.setString("Interpolacion Desactivada (X)");
    }
}

sf::View Game::getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
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

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
    std::cout<<"PosX: "<<posX<<std::endl;
    std::cout<<"PosY: "<<posY<<std::endl;
    std::cout<<"SizeX: "<<sizeX<<std::endl;
    std::cout<<"SizeY: "<<sizeY<<std::endl;
    std::cout<<std::endl;
    return view;
}
