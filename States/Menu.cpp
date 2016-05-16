/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.cpp
 * Author: joselu
 * 
 * Created on 6 de abril de 2016, 9:37
 */

#include "Menu.hpp"
#include "StateStack.hpp"
#include "../Motor/SoundManager.hpp"
#include "../Motor/Music.hpp"
#include <iostream>
#include <string>


Menu::Menu() {
    
    motor = Motor2D::Instance();
    

    SoundManager::Instance()->load();

   
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

void Menu::Clear() {
    
        while (!menu->empty()) {
        delete menu->back(), menu->pop_back();
    }
        
    delete menu;
    
    delete spriteFondoMenu;
    spriteFondoMenu = nullptr;
    
    delete spriteFondo;
    spriteFondo = nullptr;
    
    delete spriteRelleno;
    spriteRelleno = nullptr;
    
    delete mouseSprite;
    mouseSprite = nullptr;
    
    delete titulo;
    titulo = nullptr;
    
    delete mancha;
    mancha = nullptr;
    
    delete textTitulo;
    textTitulo = nullptr;
    
    
    
    

}

void Menu::Inicializar() {
    
    spriteFondoMenu = new Sprite();
    spriteFondo = new Sprite();
    spriteRelleno = new Sprite();
    mouseSprite = new Sprite();
    titulo = new Sprite();
    mancha = new Sprite[10];
            menu = new std::vector<Text*>();
    for (int i = 0; i < 9; i++) {
        menu->push_back(new Text());
    }
    textTitulo = new Text();
        
        try {
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaFondo.loadFromFile("resources/Textures/fondo.png");
        texturaFondoMenu.loadFromFile("resources/Textures/Fondo-menu-principal.png");
        mouseTexture.loadFromFile("resources/Textures/mouse.png");
        texturaMancha.loadFromFile("resources/Textures/manchaSimple.png");
        texturaPersonaje.loadFromFile("resources/Textures/fondoPersonaje.png");
        font.loadFromFile("resources/Fonts/PressStart.ttf");
        fontTitulo.loadFromFile("resources/Fonts/Old Europe.ttf");
        texturaRelleno.loadFromFile("resources/Textures/background.png");
        texturaMancha.loadFromFile("resources/Textures/ManchaMenu.png");
        texturaTitulo.loadFromFile("resources/Textures/TituloBioshock.png");
        texturaTitulo.loadFromFile("resources/Textures/TituloBioshock.png");
    } catch (std::runtime_error& e) {
        std::cout << "Excepcion: " << e.what() << std::endl;
        exit(0);
    }
    
    
    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);

    srand(time(NULL));

    random = rand() % 3; // v1 in the range 0 to 99
    
    
    Music *music = Music::Instance();
    music->Stop();
    music->Load(MUSICA::ID::Menu);
    music->Play();
    
    cargarAnimacionesMenu();

   // EstadoActivo = true;


    spriteFondo->setTexture(texturaFondo);
    
    mouseSprite->setTexture(mouseTexture);
    mouseSprite->setScale(0.2, 0.2);
    mouseSprite->setPosition(20, 20);
    mouseSprite->setOrigin(64, 64);

   
    spriteFondoMenu->setTexture(texturaFondoMenu);
    spriteFondoMenu->setScale(1.4, 1);
    spriteFondoMenu->setPosition(0, 330);

    rectanguloFondo.setSize(sf::Vector2f(1000, 1000));
    rectanguloFondo.setFillColor(sf::Color::Black);
    rectanguloFondo.setPosition(-100.f, -100.f);

    spriteRelleno->setTexture(texturaRelleno);
    spriteRelleno->setTextRect(0, 0, 1024, 2048);
    spriteRelleno->setScale(1, 2);

    for (int i = 0; i < 7; i++) {
        mancha[i].setTexture(texturaMancha);
        mancha[i].setScale(0.3, 0.3);
    }

    titulo->setTexture(texturaTitulo);
    titulo->setPosition(250, 450);

    
   
    float width = 900;
    float height = 900;
    sf::Color color(112, 112, 112);

    titulo->setTexture(texturaTitulo);
    titulo->setPosition(190, 420);
    titulo->setScale(0.23, 0.23);

    menu->at(0)->setFont(font);
    menu->at(0)->setColor(sf::Color::White);
    menu->at(0)->setString("Jugar");
    menu->at(0)->setPosition(580, 410);
    mancha[0].setPosition(540, 370);
    menu->at(0)->setStyle(1);
    menu->at(0)->setScale(0.7, 0.7);

    menu->at(1)->setFont(font);
    menu->at(1)->setColor(color);
    menu->at(1)->setString("Opciones");
    menu->at(1)->setPosition(580, 490);
    mancha[1].setScale(0.4, 0.3);
    mancha[1].setPosition(540, 450);
    menu->at(1)->setStyle(1);
    menu->at(1)->setScale(0.7, 0.7);

    menu->at(2)->setFont(font);
    menu->at(2)->setColor(color);
    menu->at(2)->setString("Salir");
    menu->at(2)->setPosition(580, 585);
    mancha[2].setPosition(540, 540);

    menu->at(2)->setStyle(1);
    menu->at(2)->setScale(0.7, 0.7);

    menu->at(3)->setFont(font);
    menu->at(3)->setColor(sf::Color::White);
    menu->at(3)->setString("OPCIONES");
    menu->at(3)->setPosition(width / 2 + 100, height / (MAX_NUMBER_OF_ITEMS + 1) *1.5);
    menu->at(3)->setStyle(1);
    menu->at(3)->setScale(0.7, 0.7);
    
    
    menu->at(4)->setFont(font);
    menu->at(4)->setColor(sf::Color::White);
    menu->at(4)->setString("Audio");
    menu->at(4)->setPosition(580, 400);
    menu->at(4)->setScale(0.6, 0.6);

    mancha[3].setScale(0.4, 0.3);
    mancha[3].setPosition(540, 350);

    
        
    menu->at(5)->setFont(font);
    menu->at(5)->setColor(color);
    menu->at(5)->setString("Video");
    menu->at(5)->setPosition(580, 550);
    menu->at(5)->setScale(0.6, 0.6);

    mancha[4].setScale(0.4, 0.3);
    mancha[4].setPosition(540, 500);
    
           
    mancha[5].setScale(0.4, 0.3);
    mancha[5].setPosition(540, 350);
    
    mancha[6].setScale(0.4, 0.3);
    mancha[6].setPosition(540, 500);
    
    menu->at(6)->setFont(font);
    menu->at(6)->setColor(sf::Color::White);
    menu->at(6)->setString("Música");
    menu->at(6)->setPosition(580, 400);
    menu->at(6)->setScale(0.6, 0.6);
    
    
    menu->at(7)->setFont(font);
    menu->at(7)->setColor(color);
    menu->at(7)->setString("Sonidos");
    menu->at(7)->setPosition(580, 550);
    menu->at(7)->setScale(0.6, 0.6);
    
    menu->at(8)->setFont(font);
    menu->at(8)->setColor(sf::Color::White);
    menu->at(8)->setString("Cambiar modo");
    menu->at(8)->setPosition(580, 400);
    menu->at(8)->setScale(0.5, 0.5);
    
    audioMusica.setFont(font);
    audioMusica.setColor(color);
    audioMusica.setString(NumberToString(volumenMusica));
    audioMusica.setPosition(620, 470);
    
    audioSonido.setFont(font);
    audioSonido.setColor(color);
    audioSonido.setString(NumberToString(volumenSonidos));
    audioSonido.setPosition(620, 620);
    
    modoVideo.setFont(font);
    modoVideo.setColor(color);
    modoVideo.setString("Salir de modo "+motor->getEstilo());
    modoVideo.setPosition(540, 500);
    modoVideo.setScale(0.3, 0.3);
    
    textTitulo->setFont(fontTitulo);
    textTitulo->setColor(sf::Color::Black);
    textTitulo->setString("Elemental\n Revenge");
    textTitulo->setScale(1.5, 1.5);
    textTitulo->setPosition(width / 2 - 250, height / (MAX_NUMBER_OF_ITEMS + 1) *1.8);
    textTitulo->setStyle(1);

    selectedItemIndex = 0;
}

sf::Vector2f Menu::getPosition() {
    return GetSpriteAnimated().getPosition();
}

void Menu::Update(sf::Time elapsedTime) {
    sf::Color color(112, 112, 112);
    if (selectedItemIndex < 3) {
        if (mouseSprite->getGlobalBounds().intersects(menu->at(0)->getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menu->at(0)->setColor(sf::Color::White);
                menu->at(1)->setColor(color);
                menu->at(2)->setColor(color);
                selectedItemIndex = 0;
            } else {
                tecladoActivo = false;
            }
        } else if (mouseSprite->getGlobalBounds().intersects(menu->at(1)->getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menu->at(0)->setColor(color);
                menu->at(1)->setColor(sf::Color::White);
                menu->at(2)->setColor(color);
                selectedItemIndex = 1;
            } else {
                tecladoActivo = false;
            }
        } else if (mouseSprite->getGlobalBounds().intersects(menu->at(2)->getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menu->at(0)->setColor(color);
                menu->at(1)->setColor(color);
                menu->at(2)->setColor(sf::Color::White);

                selectedItemIndex = 2;
            } else {
                tecladoActivo = false;
            }
        } else {
            ratonSelecciona = false;
            if (!tecladoActivo) {
                menu->at(0)->setColor(color);
                menu->at(1)->setColor(color);
                menu->at(2)->setColor(color);
            }
        }
    }
    else{
        if (selectedItemIndex >= 3 && selectedItemIndex<=5) {
        if (mouseSprite->getGlobalBounds().intersects(menu->at(4)->getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menu->at(4)->setColor(sf::Color::White);
                menu->at(5)->setColor(color);
                selectedItemIndex = 4;
            } else {
                tecladoActivo = false;
            }
        }
        else if (mouseSprite->getGlobalBounds().intersects(menu->at(5)->getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menu->at(4)->setColor(color);
                menu->at(5)->setColor(sf::Color::White);
                selectedItemIndex = 5;
            } else {
                tecladoActivo = false;
            }
        }
        else{
            ratonSelecciona = false;
            if (!tecladoActivo) {
                menu->at(4)->setColor(color);
                menu->at(5)->setColor(color);
            }
        }
    }
        else{
        if (selectedItemIndex >= 6 && selectedItemIndex<=7) {
            ratonSelecciona=false;
        }
        else{
            if (selectedItemIndex ==8) {
                if (mouseSprite->getGlobalBounds().intersects(modoVideo.getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                modoVideo.setColor(sf::Color::White);
            } else {
                tecladoActivo = false;
            }
        }
                        else{
            ratonSelecciona = false;
            if (!tecladoActivo) {
                modoVideo.setColor(color);
            }
        }
            }
        }
    }
    }
}

void Menu::Render(float interpolation, sf::Time elapsedTime) {
    sf::Time t1 = sf::seconds(0.5f);

    motor->clear();
    motor->SetView(0); //bordes;
    motor->draw(spriteRelleno);
    motor->SetView(3);

    updateView();
    //motor->UpdateMouseAndView();
    
    motor->draw(rectanguloFondo);
    motor->draw(spriteFondo);

    if (random == 0) {
        PlayAnimation(animationMenu);
        Render::UpdateAnimation(t1);

        sf::Vector2f v1(100.f, 330.f);
        DrawAnimationWithOut(v1);
    }
    if (random == 1) {
        PlayAnimation(animationMenuFuego);
        Render::UpdateAnimation(t1);

        sf::Vector2f v1(180.f, 290.f);
        DrawAnimationWithOut(v1);
    }
    if (random == 2) {
        PlayAnimation(animationMenuRayo);
        Render::UpdateAnimation(t1);

        sf::Vector2f v1(100.f, 330.f);
        DrawAnimationWithOut(v1);
    }

    motor->draw(titulo);

    if (selectedItemIndex < 3) {
        motor->draw(mancha[0]);
        motor->draw(mancha[1]);
        motor->draw(mancha[2]);

    }
    if (selectedItemIndex < 3) {
        for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
            motor->draw(*menu->at(i));
        }
    } else {
        if(selectedItemIndex<6){
        motor->draw(mancha[4]);
        motor->draw(mancha[3]);
        motor->draw(*menu->at(3));
        motor->draw(*menu->at(4));
        motor->draw(*menu->at(5));
        }
        else{
            if(selectedItemIndex==6 || selectedItemIndex==7){
            motor->draw(mancha[5]);
            motor->draw(mancha[6]);
            menu->at(3)->setString("AUDIO");
            motor->draw(*menu->at(3));
            motor->draw(*menu->at(6));
            motor->draw(*menu->at(7));
            motor->draw(audioMusica);
            motor->draw(audioSonido);
            }
            else{
            if(selectedItemIndex==8){
            motor->draw(mancha[5]);
            menu->at(3)->setString("Video");
            motor->draw(*menu->at(3));
            motor->draw(*menu->at(8));
            motor->draw(modoVideo);
            }
            }
        }
    }
   // motor->SetView(2);
   // motor->SetView(3);
    motor->draw(mouseSprite);
    motor->DrawMouse();
    motor->display();
}

void Menu::MoveRight() {

    if (selectedItemIndex == 6) {
        if (volumenMusica < 10) {
            volumenMusica++;
            audioMusica.setString(NumberToString(volumenMusica));
            Music::Instance()->SetVolume(volumenMusica*10);
        }
    }
    
    if (selectedItemIndex == 7) {
        if (volumenSonidos < 10) {
            volumenSonidos++;
            audioSonido.setString(NumberToString(volumenSonidos));
            SoundManager::Instance()->VolumenMenu(volumenSonidos*10);
        }
    }
}

void Menu::MoveLeft() {

    if (selectedItemIndex == 6) {
        if (volumenMusica > 0) {
            volumenMusica--;
            audioMusica.setString(NumberToString(volumenMusica));
            Music::Instance()->SetVolume(volumenMusica*10);
        }
    }
    if (selectedItemIndex == 7) {
        if (volumenSonidos > 0) {
            volumenSonidos--;
            audioSonido.setString(NumberToString(volumenSonidos));
            SoundManager::Instance()->VolumenMenu(volumenSonidos*10);

        }
    }
}


void Menu::MoveUp() {

    sf::Color color(112, 112, 112);

    if (selectedItemIndex < 3) {

        if (selectedItemIndex - 1 >= 0) {

            menu->at(selectedItemIndex)->setColor(color);
            selectedItemIndex--;
            menu->at(selectedItemIndex)->setColor(sf::Color::White);

        }
    }
    else{
                if (selectedItemIndex == 4) {

            menu->at(4)->setColor(color);
            selectedItemIndex++;
            menu->at(5)->setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 5) {

            menu->at(5)->setColor(color);
            selectedItemIndex--;
            menu->at(4)->setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 6) {

                    menu->at(6)->setColor(color);
            selectedItemIndex++;
            audioSonido.setColor(sf::Color::White);
            audioMusica.setColor(color);
            menu->at(7)->setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 7) {

                    audioMusica.setColor(sf::Color::White);
            audioSonido.setColor(color);
                menu->at(7)->setColor(color);
            selectedItemIndex--;
            menu->at(6)->setColor(sf::Color::White);
                }
                else if (selectedItemIndex == 8) {

            modoVideo.setColor(color);
            modoVideo.setColor(sf::Color::White);
                }
    }
}

void Menu::MoveDown() {

    sf::Color color(112, 112, 112);

    if (selectedItemIndex < 3) {

        if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {

            menu->at(selectedItemIndex)->setColor(color);
            selectedItemIndex++;
            menu->at(selectedItemIndex)->setColor(sf::Color::White);

        }
    }
else{
                if (selectedItemIndex == 4) {

                    
            menu->at(4)->setColor(color);
            selectedItemIndex++;
            menu->at(5)->setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 5) {

                menu->at(5)->setColor(color);
            selectedItemIndex--;
            menu->at(4)->setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 6) {

                menu->at(6)->setColor(color);
            audioSonido.setColor(sf::Color::White);
            audioMusica.setColor(color);
            selectedItemIndex++;
            menu->at(7)->setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 7) {

                menu->at(7)->setColor(color);
            audioMusica.setColor(sf::Color::White);
            audioSonido.setColor(color);
            selectedItemIndex--;
            menu->at(6)->setColor(sf::Color::White);
                }
              else if (selectedItemIndex == 8) {
            
            modoVideo.setColor(color);
            modoVideo.setColor(sf::Color::White);
                }
    }
}

void Menu::HandleEvents(sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code,true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code,false);
            break;
        case sf::Event::MouseButtonPressed:
            handleMouseInput(event.mouseButton.button,true);
            break;
        case sf::Event::MouseButtonReleased:
            handleMouseInput(event.mouseButton.button,false);
            break;
    }
}

void Menu::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Button::Left && isPressed == false) {

        if (selectedItemIndex == 0) {
            //selectedItemIndex = 3;
            //Si estamos en el Menu lanzamos el estado ingame
           // StateStack::Instance()->GetState(States::ID::Carga)->Inicializar();
            SoundManager *sonido = SoundManager::Instance();
            if(random==0)
            sonido->stop("resources/Sounds/Cascada.ogg");
            
            if(random==1)
            sonido->stop("resources/Sounds/CasaFuego.ogg");
            
            if(random==2)
            sonido->stop("resources/Sounds/Truenos.ogg");
            
            StateStack::Instance()->SetCurrentState(States::ID::Carga);
            StateStack::Instance()->GetState(States::ID::Carga)->Inicializar();
        }
                else if (selectedItemIndex == 1) {
            selectedItemIndex = 4;
        }
        
        else if (selectedItemIndex == 2) {
            motor->closeWindow();
        }
        else if (selectedItemIndex == 4) {
            menu->at(6)->setColor(sf::Color::White);
            audioMusica.setColor(sf::Color::White);
            selectedItemIndex = 6;
        }
        else if (selectedItemIndex == 5) {
            selectedItemIndex = 8;
        }
        else if (selectedItemIndex == 8) {
            
            if(isPressed==false){
   
        if(motor->getEstilo()=="ventana"){
                motor->cambiarEstilo(1);
                modoVideo.setString("Salir de modo "+motor->getEstilo());
                modoVideo.setScale(0.3,0.3);
                
        }else{
        if(motor->getEstilo()=="pantalla completa"){
                motor->cambiarEstilo(0);
                modoVideo.setString("Salir de modo "+motor->getEstilo());
                modoVideo.setScale(0.4,0.4);
        }
    }
            }
        }
        if (selectedItemIndex == 2) {
            motor->closeWindow();
        }
    }
}

void Menu::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

    
    if(isPressed==false){
    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        if (!ratonSelecciona) {
            tecladoActivo = true;
            MoveUp();
        }
    } else if (key == sf::Keyboard::S) {
        if (!ratonSelecciona) {
            tecladoActivo = true;
            MoveDown();
        }

    }else if (key == sf::Keyboard::D) {
            tecladoActivo = true;
            MoveRight();

    }else if (key == sf::Keyboard::A) {
            tecladoActivo = true;
            MoveLeft();


    } else if (key == sf::Keyboard::Return) {
        
        if (selectedItemIndex == 0) {
                        SoundManager *sonido = SoundManager::Instance();
            if(random==0)
            sonido->stop("resources/Sounds/Cascada.ogg");
            
            if(random==1)
            sonido->stop("resources/Sounds/CasaFuego.ogg");
            
            if(random==2)
            sonido->stop("resources/Sounds/Truenos.ogg");
            
            StateStack::Instance()->SetCurrentState(States::ID::Carga);
            StateStack::Instance()->GetState(States::ID::Carga)->level=0;
            StateStack::Instance()->GetState(States::ID::Carga)->Inicializar();
            
        }
        
        else if (selectedItemIndex == 1) {
            selectedItemIndex = 4;
        }
        
        else if (selectedItemIndex == 2) {
            motor->closeWindow();
        }
        else if (selectedItemIndex == 4) {
            menu->at(6)->setColor(sf::Color::White);
            audioMusica.setColor(sf::Color::White);
            selectedItemIndex = 6;
        }
        else if (selectedItemIndex == 5) {
            selectedItemIndex = 8;
        }
        else if (selectedItemIndex == 8) {
            
            if(isPressed==false){
   
        if(motor->getEstilo()=="ventana"){
                motor->cambiarEstilo(1);
                modoVideo.setString("Salir de modo "+motor->getEstilo());
                modoVideo.setScale(0.3,0.3);
                
        }else{
        if(motor->getEstilo()=="pantalla completa"){
                motor->cambiarEstilo(0);
                modoVideo.setString("Salir de modo "+motor->getEstilo());
                modoVideo.setScale(0.4,0.4);
        }
    }
            }
        }
    } else if (key == sf::Keyboard::Escape) {
            menu->at(3)->setString("OPCIONES");

        if (selectedItemIndex < 3) {
            // mWindow->close();
        } else {
            selectedItemIndex = 1;
        }
    }
    }
}

void Menu::updateView() {
    sf::FloatRect viewBounds(motor->getCenterFromView(1) - motor->getSizeFromView(1) / 2.f, motor->getSizeFromView(1));

    sf::Vector2f position = motor->getMousePosition();

    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);
    mouseSprite->setPosition(position.x, position.y);
    //printf("Posicion del raton %f,%f\n",position.x,position.y);

    motor->setSizeForView(3, 640, 480);
    motor->SetView(3);
}


void Menu::cargarAnimacionesMenu() {
    if (random == 0) {
        SoundManager *sonido = SoundManager::Instance();
       // sonido->setVolumen("resources/Sounds/Cascada.ogg",SoundManager::Instance()->volumen);
        sonido->play("resources/Sounds/Cascada.ogg");
        if (!texturaAnimation.loadFromFile("resources/MenuInicio/SpritesheetMenu.png")) {
            std::cout << "Error cargando la textura: " << "resources/MenuInicio/SpritesheetMenu.png" << std::endl;
            exit(0);
        }
        animationMenu = new Animation();

        texturaAnimation.setSmooth(true);

        animationMenu->setSpriteSheet("resources/MenuInicio/SpritesheetMenu.png");
        animationMenu->addFrame(sf::IntRect(0, 0, 800, 336));
        animationMenu->addFrame(sf::IntRect(800, 0, 800, 336));
        animationMenu->addFrame(sf::IntRect(0, 336, 800, 336));
        animationMenu->addFrame(sf::IntRect(799, 336, 800, 336));
        animationMenu->addFrame(sf::IntRect(0, 672, 800, 336));
        animationMenu->addFrame(sf::IntRect(799, 672, 800, 336));
        animationMenu->addFrame(sf::IntRect(-1, 1008, 800, 336));
        animationMenu->addFrame(sf::IntRect(799, 1008, 800, 336));
        InicializarAnimatedSprite(sf::seconds(3.f), true, false);

    }

    if (random == 1) {
            SoundManager *sonido = SoundManager::Instance();
            //sonido->setVolumen("resources/Sounds/CasaFuego.ogg",SoundManager::Instance()->volumen);
             sonido->play("resources/Sounds/CasaFuego.ogg");


//        EstadoActivo = true;
        tecladoActivo = false;
        ratonSelecciona = false;

        animationMenuFuego = new Animation();

        if (!texturaAnimationFuego.loadFromFile("resources/MenuInicio/fuego.png")) {
            std::cout << "Error cargando la textura: " << "resources/MenuInicio/fuego.png" << std::endl;
            exit(0);
        }
        texturaAnimationFuego.setSmooth(true);

        animationMenuFuego->setSpriteSheet("resources/MenuInicio/fuego.png");
        animationMenuFuego->addFrame(sf::IntRect(0, 0, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(800, 0, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(1600, 0, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(2400, 0, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(3200, 0, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(4000, 0, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(0, 600, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(800, 600, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(1600, 600, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(2400, 600, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(3200, 600, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(4000, 600, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(0, 1200, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(800, 1200, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(1600, 1200, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(2400, 1200, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(3200, 1200, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(4000, 1200, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(0, 1800, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(800, 1800, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(1600, 1800, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(2400, 1800, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(3200, 1800, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(4000, 1800, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(0, 2400, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(800, 2400, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(1600, 2400, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(2400, 2400, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(3200, 2400, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(4000, 2400, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(0, 3000, 800, 600));
        animationMenuFuego->addFrame(sf::IntRect(800, 3000, 800, 600));

        InicializarAnimatedSprite(sf::seconds(3.f), true, false);

        SetScaleAnimation(0.85, 0.7);
    }

    if (random == 2) {
              SoundManager *sonido = SoundManager::Instance();
              //sonido->setVolumen("resources/Sounds/Truenos.ogg",SoundManager::Instance()->volumen);
             sonido->play("resources/Sounds/Truenos.ogg");

             //        EstadoActivo = true;
        tecladoActivo = false;
        ratonSelecciona = false;


        animationMenuRayo = new Animation();

        if (!texturaAnimationRayo.loadFromFile("resources/MenuInicio/rayo.png")) {
            std::cout << "Error cargando la textura: " << "resources/MenuInicio/rayo.png" << std::endl;
            exit(0);
        }
        texturaAnimationRayo.setSmooth(true);

        animationMenuRayo->setSpriteSheet("resources/MenuInicio/rayo.png");
        animationMenuRayo->addFrame(sf::IntRect(0, 0, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(800, 0, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(1600, 0, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(0, 336, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(800, 336, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(1600, 336, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(0, 672, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(800, 672, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(1600, 672, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(0, 1008, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(800, 1008, 800, 336));
        animationMenuRayo->addFrame(sf::IntRect(1600, 1008, 800, 336));

        InicializarAnimatedSprite(sf::seconds(3.f), true, false);

    }
}

template<typename T>
std::string Menu::NumberToString(T pNumber) {
    std::ostringstream oOStrStream;
    oOStrStream << pNumber;
    return oOStrStream.str();
}
