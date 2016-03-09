#include "../Headers/Game.hpp"
#include "hWaterBasic.hpp"
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
: mWindow(sf::VideoMode(ancho, alto, 24), "Hito 1 - Hechizo Agua - Rama: HechizoAgua", sf::Style::Close)
, mWorldView(mWindow.getDefaultView())
, contFonts()
, texturaFondo()
, spriteFondo()
, mStatisticsText()
, player()
 ,enemigo()
, isMovingUp(false)
, isMovingDown(false)
, isMovingRight(false)
, isMovingLeft(false)
, firstTime(true)
, isInterpolating(false) {
    mWindow.setFramerateLimit(60); //Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    mWindow.setVerticalSyncEnabled(true);
    mWorldView.zoom(0.5f);
    // Cargamos RECURSOS. Utilizamos los contenedores genericos
    try {
        texturaFondo.loadFromFile("resources/Textures/grasstext.png");
        contFonts.loadFromFile("resources/Fonts/Sansation.ttf");
    } catch (std::runtime_error& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        exit(0);
    }
    texturaFondo.setRepeated(true);
    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 2000, 2000));
#ifdef _WIN32
    HWND handler = mWindow.getSystemHandle();
    RECT rWindow;
    GetWindowRect(handler, &rWindow);
    ClipCursor(&rWindow);
#endif
    //Configuramos Items
    player.Inicializar(200.f, 250.f);
    
    enemigo[0].Inicializar(300.f, 350.f);
    enemigo[1].Inicializar(350.f, 450.f);

    mStatisticsText.setFont(contFonts);
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(13);
    mStatisticsText.setColor(sf::Color::Black);
    mStatisticsText.setString("Interpolacion Desactivada (X)");
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
    if(player.hAguaBasico.hSprite.getGlobalBounds().intersects(enemigo[0].getSprite().getGlobalBounds())){
        enemigo[0].empujado=true;
        enemigo[0].tiempoempujado.restart();
        /* sf::Vector2f movement(0.f, 0.f);
        movement.x=(200 * cos(player.hAguaBasico.angleshot2) * 1.0f);
        movement.y=(200 * sin(player.hAguaBasico.angleshot2) * 1.0f);
        enemigo.Update(movement,elapsedTime);*/
    }
    
    if(enemigo[0].empujado==true){
        sf::Vector2f movement(0.f, 0.f);
        movement.x=300*(cos(player.hAguaBasico.angleshot2) * 1.0f);
        movement.y=300*(sin(player.hAguaBasico.angleshot2) * 1.0f);
        enemigo[0].Update(movement,elapsedTime);
    }
    
    if( enemigo[0].tiempoempujado.getElapsedTime().asSeconds()>0.5){
        enemigo[0].empujado=false;
    }
    
        if(player.hAguaBasico.hSprite.getGlobalBounds().intersects(enemigo[1].getSprite().getGlobalBounds())){
        enemigo[1].empujado=true;
        enemigo[1].tiempoempujado.restart();
        /* sf::Vector2f movement(0.f, 0.f);
        movement.x=(200 * cos(player.hAguaBasico.angleshot2) * 1.0f);
        movement.y=(200 * sin(player.hAguaBasico.angleshot2) * 1.0f);
        enemigo.Update(movement,elapsedTime);*/
    }
    
    if(enemigo[1].empujado==true){
        sf::Vector2f movement(0.f, 0.f);
        movement.x=300*(cos(player.hAguaBasico.angleshot2) * 1.0f);
        movement.y=300*(sin(player.hAguaBasico.angleshot2) * 1.0f);
        enemigo[1].Update(movement,elapsedTime);
    }
    
    if( enemigo[1].tiempoempujado.getElapsedTime().asSeconds()>0.5){
        enemigo[1].empujado=false;
    }
    
    firstTime = false;
}

void Game::updateView() {
    sf::Vector2f mousePosition = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
    float camera_x = (mousePosition.x + (player.getPosition().x * 6)) / 7; //Media dando prioridad al jugador
    float camera_y = (mousePosition.y + player.getPosition().y * 6) / 7;
    float x = (mWorldView.getCenter().x + 0.1 * (camera_x - mWorldView.getCenter().x)); //Lo mismo que la funcion lerp
    float y = (mWorldView.getCenter().y + 0.1 * (camera_y - mWorldView.getCenter().y));
    mWorldView.setCenter(x, y);
    mWindow.setView(mWorldView);
    mStatisticsText.setPosition(mWindow.getPosition().x, mWindow.getPosition().y);
}

void Game::render(float interpolation) //Dibuja
{

    mWindow.clear();
    updateView();
    mWindow.draw(spriteFondo);
    
    
    
    if (player.hAguaBasico.dibujar == true) {
        if (player.hAguaBasico.tiempoCast.getElapsedTime().asSeconds() < 0.5) {
            player.hAguaBasico.hSprite.setPosition(player.getPosition().x+20,player.getPosition().y+35);
            mWindow.draw(player.hAguaBasico.hSprite);
        } else {
            player.hAguaBasico.setDibujar(false);
        }
    }

    //LLAMAR AL DRAW DEL PLAYER
    if (isInterpolating)
        player.DrawWithInterpolation(mWindow, interpolation);
    else
        player.Draw(mWindow);
    
    enemigo[0].Draw(mWindow);
    enemigo[1].Draw(mWindow);

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
                //sf::Vector2f mousePosition = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
                // sf::Vector2f playerposition = player.getPosition();
                
                player.hAguaBasico.cast(sf::Vector2f(player.getPosition()), &mWindow);


                break;

            case sf::Event::Closed:
                mWindow.close();
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

