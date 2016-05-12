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


Menu::Menu() {
    
    motor = Motor2D::Instance();
    
    spriteFondoMenu = new Sprite();
    spriteFondo = new Sprite();
    spriteRelleno = new Sprite();
    mouseSprite = new Sprite();
    titulo = new Sprite();
    mancha = new Sprite[6];
    
    textTitulo = new Text();
    
   
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

void Menu::Clear() {
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
    
    srand(time(NULL));

    random = rand() % 3; // v1 in the range 0 to 99
    
    SoundManager::Instance()->load();
    Music *music = Music::Instance();
    music->Stop();
    music->Load(MUSICA::ID::Menu);
    music->Play();
    
    cargarAnimacionesMenu();

   // EstadoActivo = true;

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

    for (int i = 0; i < 5; i++) {
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


    menu[0].setFont(font);
    menu[0].setColor(sf::Color::White);
    menu[0].setString("Jugar");
    menu[0].setPosition(580, 410);
    mancha[0].setPosition(540, 370);
    menu[0].setStyle(1);
    menu[0].setScale(0.7, 0.7);

    menu[1].setFont(font);
    menu[1].setColor(color);
    menu[1].setString("Opciones");
    menu[1].setPosition(580, 490);
    mancha[1].setScale(0.4, 0.3);
    mancha[1].setPosition(540, 450);

    menu[1].setStyle(1);
    menu[1].setScale(0.7, 0.7);

    menu[2].setFont(font);
    menu[2].setColor(color);
    menu[2].setString("Salir");
    menu[2].setPosition(580, 570);
    mancha[2].setPosition(540, 540);

    menu[2].setStyle(1);
    menu[2].setScale(0.7, 0.7);

    menu[3].setFont(font);
    menu[3].setColor(sf::Color::White);
    menu[3].setString("OPCIONES");
    menu[3].setPosition(width / 2 + 100, height / (MAX_NUMBER_OF_ITEMS + 1) *1.5);
    menu[3].setStyle(1);
    menu[3].setScale(0.7, 0.7);
    
    
    menu[4].setFont(font);
    menu[4].setColor(sf::Color::White);
    menu[4].setString("Audio");
    menu[4].setPosition(580, 400);
    menu[4].setScale(0.6, 0.6);

    mancha[3].setScale(0.4, 0.3);
    mancha[3].setPosition(540, 350);

    
        
    menu[5].setFont(font);
    menu[5].setColor(color);
    menu[5].setString("Video");
    menu[5].setPosition(580, 550);
    menu[5].setScale(0.6, 0.6);

    mancha[4].setScale(0.4, 0.3);
    mancha[4].setPosition(540, 500);
    
            
    menu[6].setFont(font);
    menu[6].setColor(sf::Color::White);
    menu[6].setString("Música");
    menu[6].setPosition(580, 400);
    menu[6].setScale(0.6, 0.6);
    
    
    menu[7].setFont(font);
    menu[7].setColor(color);
    menu[7].setString("Sonidos");
    menu[7].setPosition(580, 550);
    menu[7].setScale(0.6, 0.6);
    
    audioMusica.setFont(font);
    audioMusica.setColor(color);
    audioMusica.setString(NumberToString(volumenMusica));
    audioMusica.setPosition(620, 470);
    
    audioSonido.setFont(font);
    audioSonido.setColor(color);
    audioSonido.setString(NumberToString(volumenSonidos));
    audioSonido.setPosition(620, 620);
    
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
    if (selectedItemIndex < 3) {
        sf::Color color(112, 112, 112);
        if (mouseSprite->getGlobalBounds().intersects(menu[0].getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menu[0].setColor(sf::Color::White);
                menu[1].setColor(color);
                menu[2].setColor(color);
                selectedItemIndex = 0;
            } else {
                tecladoActivo = false;
            }
        } else if (mouseSprite->getGlobalBounds().intersects(menu[1].getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menu[0].setColor(color);
                menu[1].setColor(sf::Color::White);
                menu[2].setColor(color);
                selectedItemIndex = 1;
            } else {
                tecladoActivo = false;
            }
        } else if (mouseSprite->getGlobalBounds().intersects(menu[2].getGlobalBounds())) {
            ratonSelecciona = true;
            if (!tecladoActivo) {
                menu[0].setColor(color);
                menu[1].setColor(color);
                menu[2].setColor(sf::Color::White);

                selectedItemIndex = 2;
            } else {
                tecladoActivo = false;
            }
        } else {
            ratonSelecciona = false;
            if (!tecladoActivo) {
                menu[0].setColor(color);
                menu[1].setColor(color);
                menu[2].setColor(color);
            }
        }
    }
    else{
        
    }
}

void Menu::Render(float interpolation, sf::Time elapsedTime) {
    sf::Time t1 = sf::seconds(0.5f);

    motor->clear();
    motor->SetView(0); //bordes;
    motor->draw(spriteRelleno);
    motor->SetView(3);

    
    updateView();
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
            motor->draw(menu[i]);
        }
    } else {
        if(selectedItemIndex<6){
        motor->draw(mancha[4]);
        motor->draw(mancha[3]);
        motor->draw(menu[3]);
        motor->draw(menu[4]);
        motor->draw(menu[5]);
        }
        else{
            if(selectedItemIndex==6 || selectedItemIndex==7){
            menu[3].setString("AUDIO");
            motor->draw(menu[3]);
            motor->draw(menu[6]);
            motor->draw(menu[7]);
            motor->draw(audioMusica);
            motor->draw(audioSonido);
            }

        }
    }
    motor->SetView(2);
    motor->SetView(3);
    motor->draw(mouseSprite);
    motor->display();
}

void Menu::MoveRight() {

    if (selectedItemIndex == 6) {
        if (volumenMusica < 10) {
            volumenMusica++;
            audioMusica.setString(NumberToString(volumenMusica));
        }
    }
    
    if (selectedItemIndex == 7) {
        if (volumenSonidos < 10) {
            volumenSonidos++;
            audioSonido.setString(NumberToString(volumenSonidos));
        }
    }
}

void Menu::MoveLeft() {

    if (selectedItemIndex == 6) {
        if (volumenMusica > 0) {
            volumenMusica--;
            audioMusica.setString(NumberToString(volumenMusica));
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

            menu[selectedItemIndex].setColor(color);
            selectedItemIndex--;
            menu[selectedItemIndex].setColor(sf::Color::White);

        }
    }
    else{
                if (selectedItemIndex == 4) {

            menu[4].setColor(color);
            selectedItemIndex++;
            menu[5].setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 5) {

            menu[5].setColor(color);
            selectedItemIndex--;
            menu[4].setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 6) {

                menu[6].setColor(color);
            selectedItemIndex++;
            menu[7].setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 7) {

                menu[7].setColor(color);
            selectedItemIndex--;
            menu[6].setColor(sf::Color::White);
                }
    }
}

void Menu::MoveDown() {

    sf::Color color(112, 112, 112);

    if (selectedItemIndex < 3) {

        if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {

            menu[selectedItemIndex].setColor(color);
            selectedItemIndex++;
            menu[selectedItemIndex].setColor(sf::Color::White);

        }
    }
else{
                if (selectedItemIndex == 4) {

                    
            menu[4].setColor(color);
            selectedItemIndex++;
            menu[5].setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 5) {

                menu[5].setColor(color);
            selectedItemIndex--;
            menu[4].setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 6) {

                menu[6].setColor(color);
            selectedItemIndex++;
            menu[7].setColor(sf::Color::White);
                }
                
                else if (selectedItemIndex == 7) {

                menu[7].setColor(color);
            selectedItemIndex--;
            menu[6].setColor(sf::Color::White);
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
        if (!ratonSelecciona) {
            tecladoActivo = true;
            MoveRight();
        }

    }else if (key == sf::Keyboard::A) {
        if (!ratonSelecciona) {
            tecladoActivo = true;
            MoveLeft();
        }

    } else if (key == sf::Keyboard::Return) {
        
        if (selectedItemIndex == 0) {

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
            selectedItemIndex = 6;
        }

    } else if (key == sf::Keyboard::Escape) {
            menu[3].setString("OPCIONES");

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

    motor->setSizeForView(3, 640, 480);
    motor->SetView(3);
}


void Menu::cargarAnimacionesMenu() {
    if (random == 0) {
        SoundManager *sonido = SoundManager::Instance();
        sonido->setVolumen("resources/Sounds/Cascada.ogg",SoundManager::Instance()->volumen);
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
            sonido->setVolumen("resources/Sounds/CasaFuego.ogg",SoundManager::Instance()->volumen);
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
              sonido->setVolumen("resources/Sounds/Truenos.ogg",SoundManager::Instance()->volumen);
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
