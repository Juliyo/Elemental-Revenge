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

#include "Headers/Menu2.hpp"

Menu2::Menu2() {
    
    animationMenu = new Animation();
    
        if(!texturaAnimation.loadFromFile("resources/MenuInicio/SpritesheetMenu.png")){
       std::cout<<"Error cargando la textura: "<<"resources/MenuInicio/SpritesheetMenu.png"<<std::endl;
       exit(0);
    }
    texturaAnimation.setSmooth(true);
    
    animationMenu->setSpriteSheet(texturaAnimation);
    animationMenu->addFrame(sf::IntRect(0, 0, 800, 336));
    animationMenu->addFrame(sf::IntRect(800, 0, 800, 336));
    animationMenu->addFrame(sf::IntRect(0, 336, 800, 336));
    animationMenu->addFrame(sf::IntRect(799, 336, 800, 336));
    animationMenu->addFrame(sf::IntRect(0, 672, 800, 336));
    animationMenu->addFrame(sf::IntRect(799, 672, 800, 336));
   animationMenu->addFrame(sf::IntRect(-1, 1008, 800, 336));
    animationMenu->addFrame(sf::IntRect(799, 1008, 800, 336));

    EstadoActivo=true;
    
    InicializarAnimatedSprite(sf::seconds(3.f), true, false);
    SetPosition(100, 330);


    if(!font.loadFromFile("resources/Fonts/PressStart.ttf")){
        
    }
    
     if(!fontTitulo.loadFromFile("resources/Fonts/Old Europe.ttf")){
        
    }
            mouseTexture.loadFromFile("resources/Textures/mouse.png");
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setScale(0.2, 0.2);
    mouseSprite.setPosition(20, 20);
    mouseSprite.setOrigin(64, 64);
    
    texturaFondoMenu.loadFromFile("resources/Textures/Fondo-menu-principal.png");
    spriteFondoMenu.setTexture(texturaFondoMenu);
    spriteFondoMenu.setScale(1.4,1);
    spriteFondoMenu.setPosition(0,330);
    
            texturaFondo.loadFromFile("resources/Textures/fondo.png");

            texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);

    rectanguloFondo.setSize(sf::Vector2f(1000, 1000));
     rectanguloFondo.setFillColor(sf::Color::Black);
 rectanguloFondo.setPosition(-100.f, -100.f);


    texturaFondo.setSmooth(true);
    texturaFondo.setRepeated(1);
    spriteFondo.setTexture(texturaFondo);
    
        texturaRelleno.loadFromFile("resources/Textures/background.png");

        spriteRelleno.setTexture(texturaRelleno);
    spriteRelleno.setTextureRect(sf::IntRect(0, 0, 1024, 2048));
    spriteRelleno.setScale(1, 2);
    
    mWindow = ref.GetWindow();
    
    
        texturaMancha.loadFromFile("resources/Textures/ManchaMenu.png");
        
        for(int i=0; i<3;i++){
        Mancha[i].setTexture(texturaMancha);
    Mancha[i].setScale(0.3,0.3);
    
        }
    
        texturaTitulo.loadFromFile("resources/Textures/Titulo-juego.png");
        
            Titulo.setTexture(texturaTitulo);
    Titulo.setPosition(250,450);
        
    float width= mWorldView.getSize().x;
    float height= mWorldView.getSize().x;
    sf::Color color(112,112,112);

    
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::White);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width/2+100, height/(MAX_NUMBER_OF_ITEMS+1) *1.7));
    Mancha[0].setPosition(sf::Vector2f(width/2+50, height/(MAX_NUMBER_OF_ITEMS+1) *1.5));
    menu[0].setStyle(sf::Text::Bold);
            menu[0].setScale(0.7,0.7);

    menu[1].setFont(font);
    menu[1].setColor(color);
    menu[1].setString("Options");
    menu[1].setPosition(sf::Vector2f(width/2+100, height/(MAX_NUMBER_OF_ITEMS+1) *2));
    Mancha[1].setScale(0.4,0.3);
    Mancha[1].setPosition(sf::Vector2f(width/2+50, height/(MAX_NUMBER_OF_ITEMS+1) *1.8));

            menu[1].setStyle(sf::Text::Bold);
            menu[1].setScale(0.7,0.7);

    
    menu[2].setFont(font);
    menu[2].setColor(color);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width/2+100, height/(MAX_NUMBER_OF_ITEMS+1) *2.3));
        Mancha[2].setPosition(sf::Vector2f(width/2+50, height/(MAX_NUMBER_OF_ITEMS+1) *2.1));

            menu[2].setStyle(sf::Text::Bold);
            menu[2].setScale(0.7,0.7);

    menu[3].setFont(font);
    menu[3].setColor(sf::Color::White);
    menu[3].setString("OPTIONS");
    menu[3].setPosition(sf::Vector2f(width/2+100, height/(MAX_NUMBER_OF_ITEMS+1) *1.5));
            menu[3].setStyle(sf::Text::Bold);
                menu[3].setScale(0.7,0.7);

            
    textTitulo.setFont(fontTitulo);
    textTitulo.setColor(sf::Color::Black);
    textTitulo.setString("Elemental\n Revenge");
    textTitulo.scale(1.5,1.5);
    textTitulo.setPosition(sf::Vector2f(width/2-250, height/(MAX_NUMBER_OF_ITEMS+1) *1.8));
    textTitulo.setStyle(sf::Text::Bold);
    
    
    selectedItemIndex=0;
    
}

Menu2::Menu2(const Menu2& orig) {
}

Menu2::~Menu2() {
}

sf::Vector2f Menu2::getPosition() {
    return GetSpriteAnimated().getPosition();
}

void Menu2::draw(){
    
    
sf::Time t1 = sf::seconds(0.5f);
    
        
    sf::View previa = mWindow->getView();
    mWindow->setView(mBackgroundView);
    mWindow->draw(spriteRelleno);
    mWindow->setView(previa);
    
    updateView();
    mWindow->draw(rectanguloFondo);
    mWindow->draw(spriteFondo);
     //   mWindow->draw(spriteFondoMenu);

            PlayAnimation(animationMenu);
Render::UpdateAnimation(t1);

sf::Vector2f v1(100.f, 330.f);
        DrawAnimationWithOut(*mWindow, v1);

    mWindow->draw(Titulo);
    
    if(selectedItemIndex<3){
        mWindow->draw(Mancha[0]);
        mWindow->draw(Mancha[1]);
        mWindow->draw(Mancha[2]);
    }
    if(selectedItemIndex<3){
    for(int i=0; i<MAX_NUMBER_OF_ITEMS;i++){

        mWindow->draw(menu[i]);
       
    }
    }
    else{
        mWindow->draw(menu[3]);
    }
        mWindow->draw(mouseSprite);

}

void Menu2::MoveUp(){
    
    sf::Color color(112,112,112);
    
        if(selectedItemIndex<3){

    if(selectedItemIndex-1>=0){
        
        menu[selectedItemIndex].setColor(color);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::White);
        
    }
        }
}

void Menu2::MoveDown(){
    
    sf::Color color(112,112,112);
    
        if(selectedItemIndex<3){

    if(selectedItemIndex+1<MAX_NUMBER_OF_ITEMS){
        
        menu[selectedItemIndex].setColor(color);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::White);
        
    }
        }
    
}


void Menu2::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    
    if (key == sf::Keyboard::W) { //Esto lo hago para que cuando no estes presionando cambia a false
        MoveUp();
    } else if (key == sf::Keyboard::S) {
        MoveDown();
    } else if (key == sf::Keyboard::Return) {
        if(selectedItemIndex==1){
        selectedItemIndex=3;
        }
        if(selectedItemIndex==2){
            mWindow->close();
        }

    } else if (key == sf::Keyboard::Escape) {
        if(selectedItemIndex<3){
        mWindow->close();}
        else{
            selectedItemIndex=1;
        }
    } 
}


    void Menu2::updateView(){
    sf::Vector2f mousePosition = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

    sf::Vector2f position = mousePosition;
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.width + viewBounds.left);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.height + viewBounds.top);

    mouseSprite.setPosition(position);

    mWorldView.setSize(640, 480);

    mWindow->setView(getLetterboxView(mWorldView, ref.ancho, ref.alto, 640, 480));
    }
    
sf::View Menu2::getLetterboxView(sf::View view, int windowWidth, int windowHeight, int viewRatioWidth, int viewRatioHeight){
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