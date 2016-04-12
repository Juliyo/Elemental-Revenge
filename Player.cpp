/* 
 * File:   Player.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 7:43 AM
 */

#include "Player.hpp"
#include "Util.hpp"

Player::Player() {
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

void Player::Inicializar(float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    
    //casteo rayo
    castingAnimationUpRayo= new Animation();
    castingAnimationDownRayo= new Animation();
    castingAnimationRightRayo= new Animation();
    castingAnimationLeftRayo= new Animation();
    //casteo Fuego
    castingAnimationUpFuego= new Animation();
    castingAnimationDownFuego= new Animation();
    castingAnimationRightFuego= new Animation();
    castingAnimationLeftFuego= new Animation();
    //casteo Agua
    castingAnimationUpAgua= new Animation();
    castingAnimationDownAgua= new Animation();
    castingAnimationRightAgua= new Animation();
    castingAnimationLeftAgua= new Animation();
    
    //fuego
    fuegoAnimationDown = new Animation();
    fuegoAnimationLeft = new Animation();
    fuegoAnimationRight = new Animation();
    fuegoAnimationUp = new Animation();
    fuego2AnimationDown = new Animation();
    fuego2AnimationLeft = new Animation();
    fuego2AnimationRight = new Animation();
    fuego2AnimationUp = new Animation();
    //heal
    healingAnimationDown = new Animation();
    healingAnimationLeft = new Animation();
    healingAnimationRight = new Animation();
    healingAnimationUp = new Animation();
    
    
    
    
    
    
    hud = new Hud();
    hRayoBasico = new hRayBasic();
    hRayoAvanzado = new hRayAdvanced();
    
    hFuegoBasico = new hFireBasic[50];
    hFuegoAvanzado = new hFireAdvanced();
    
    hAguaBasico=new hWaterBasic();
    hAguaAvanzado = new hWaterAdvanced();
    
    hHeal = new Heal();
    
    flash = new Flash(1);//Animacion que aparece en la posicion que deja el jugador
    flash2 = new Flash(2);//Animacion que aparece a la posicion en que se ha movido el jugador
            
    if(!texturaPlayer.loadFromFile("resources/Textures/player.png")){
       std::cout<<"Error cargando la textura: "<<"resources/Textures/player.png"<<std::endl;
       exit(0);
    }
    texturaPlayer.setSmooth(true);
    
    walkingAnimationDown->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationDown->addFrame(sf::IntRect(512, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(0, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(64, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(128, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(192, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(256, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(320, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(384, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(448, 640, 64, 64));
    walkingAnimationDown->addFrame(sf::IntRect(512, 640, 64, 64));
   
    
    walkingAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationLeft->addFrame(sf::IntRect(512, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(0, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(64, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(128, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(192, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(256, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(320, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(384, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(448, 576, 64, 64));
    walkingAnimationLeft->addFrame(sf::IntRect(512, 576, 64, 64));
    
    walkingAnimationRight->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationRight->addFrame(sf::IntRect(512, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(0, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(64, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(128, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(192, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(256, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(320, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(384, 704, 64, 64));
    walkingAnimationRight->addFrame(sf::IntRect(448, 704, 64, 64));
    
    
    walkingAnimationUp->setSpriteSheet("resources/Textures/player.png");
    walkingAnimationUp->addFrame(sf::IntRect(512, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(0, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(64, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(128, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(192, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(256, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(320, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(384, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(448, 512, 64, 64));
    walkingAnimationUp->addFrame(sf::IntRect(512, 512, 64, 64));
    
    //casteo Rayo
    castingAnimationUpRayo->setSpriteSheet("resources/Textures/player.png");
    castingAnimationUpRayo->addFrame(sf::IntRect(320, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(0, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(64, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(128, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(192, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(256, 768, 64, 64));
    castingAnimationUpRayo->addFrame(sf::IntRect(320, 768, 64, 64));
  
 
    castingAnimationDownRayo->setSpriteSheet("resources/Textures/player.png");
    castingAnimationDownRayo->addFrame(sf::IntRect(320, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(0, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(64, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(128, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(192, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(256, 896, 64, 64));
    castingAnimationDownRayo->addFrame(sf::IntRect(320, 896, 64, 64));
 
    
    castingAnimationRightRayo->setSpriteSheet("resources/Textures/player.png");
    castingAnimationRightRayo->addFrame(sf::IntRect(320, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(0, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(64, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(128, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(192, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(256, 960, 64, 64));
    castingAnimationRightRayo->addFrame(sf::IntRect(320, 960, 64, 64));
  
   
    castingAnimationLeftRayo->setSpriteSheet("resources/Textures/player.png");
    castingAnimationLeftRayo->addFrame(sf::IntRect(320, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(0, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(64, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(128, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(192, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(256, 832, 64, 64));
    castingAnimationLeftRayo->addFrame(sf::IntRect(320, 832, 64, 64));
 
    
    
    
    //Casteo Fuego
    
    
    //Casteo Agua
    //casteo
    castingAnimationUpAgua->setSpriteSheet("resources/Textures/player.png");
    castingAnimationUpAgua->addFrame(sf::IntRect(448, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(0, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(64, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(128, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(192, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(256, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(320, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(384, 256, 64, 64));
    castingAnimationUpAgua->addFrame(sf::IntRect(448, 256, 64, 64));
  
    
    
    castingAnimationDownAgua->setSpriteSheet("resources/Textures/player.png");
    castingAnimationDownAgua->addFrame(sf::IntRect(448, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(0, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(64, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(128, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(192, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(256, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(320, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(384, 384, 64, 64));
    castingAnimationDownAgua->addFrame(sf::IntRect(448, 384, 64, 64));
    
    
    castingAnimationRightAgua->setSpriteSheet("resources/Textures/player.png");
    castingAnimationRightAgua->addFrame(sf::IntRect(448, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(0, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(64, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(128, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(192, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(256, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(320, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(384, 448, 64, 64));
    castingAnimationRightAgua->addFrame(sf::IntRect(448, 448, 64, 64));
    
    
    castingAnimationLeftAgua->setSpriteSheet("resources/Textures/player.png");
    castingAnimationLeftAgua->addFrame(sf::IntRect(448, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(0, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(64, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(128, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(192, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(256, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(320, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(384, 320, 64, 64));
    castingAnimationLeftAgua->addFrame(sf::IntRect(448, 320, 64, 64));
    
    
    
    /////////////////////////////////
    //Fuegooo
    //castingAnimationLeftFuego
    fuegoAnimationUp->setSpriteSheet("resources/Textures/player.png");
    //fuegoAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(0, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(64, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(128, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(192, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(256, 768, 64, 64));
    fuegoAnimationUp->addFrame(sf::IntRect(320, 768, 64, 64));
  
  
    
    
    fuegoAnimationDown->setSpriteSheet("resources/Textures/player.png");
    //fuegoAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(0, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(64, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(128, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(192, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(256, 896, 64, 64));
    fuegoAnimationDown->addFrame(sf::IntRect(320, 896, 64, 64));
 
    
    
    fuegoAnimationRight->setSpriteSheet("resources/Textures/player.png");
    //fuegoAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(0, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(64, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(128, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(192, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(256, 960, 64, 64));
    fuegoAnimationRight->addFrame(sf::IntRect(320, 960, 64, 64));
  
    
    
    fuegoAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    //fuegoAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(0, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(64, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(128, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(192, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(256, 832, 64, 64));
    fuegoAnimationLeft->addFrame(sf::IntRect(320, 832, 64, 64));

    fuego2AnimationDown->setSpriteSheet("resources/Textures/player.png");
    fuego2AnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(0, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(64, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(128, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(192, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(256, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(320, 128, 64, 64));
    fuego2AnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));


    fuego2AnimationLeft->setSpriteSheet("resources/Textures/player.png");
    fuego2AnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(0, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(64, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(128, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(192, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(256, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(320, 64, 64, 64));
    fuego2AnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));

    fuego2AnimationRight->setSpriteSheet("resources/Textures/player.png");
    fuego2AnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(0, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(64, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(128, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(192, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(256, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(320, 192, 64, 64));
    fuego2AnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));


    fuego2AnimationUp->setSpriteSheet("resources/Textures/player.png");
    fuego2AnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(0, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(64, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(128, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(192, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(256, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(320, 0, 64, 64));
    fuego2AnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    
    //casteo heal
    
    healingAnimationDown->setSpriteSheet("resources/Textures/player.png");
    healingAnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(0, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(64, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(128, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(192, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(256, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(320, 128, 64, 64));
    healingAnimationDown->addFrame(sf::IntRect(384, 128, 64, 64));


    healingAnimationLeft->setSpriteSheet("resources/Textures/player.png");
    healingAnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(0, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(64, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(128, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(192, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(256, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(320, 64, 64, 64));
    healingAnimationLeft->addFrame(sf::IntRect(384, 64, 64, 64));

    healingAnimationRight->setSpriteSheet("resources/Textures/player.png");
    healingAnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(0, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(64, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(128, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(192, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(256, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(320, 192, 64, 64));
    healingAnimationRight->addFrame(sf::IntRect(384, 192, 64, 64));


    healingAnimationUp->setSpriteSheet("resources/Textures/player.png");
    healingAnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(0, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(64, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(128, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(192, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(256, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(320, 0, 64, 64));
    healingAnimationUp->addFrame(sf::IntRect(384, 0, 64, 64));
    
    
    
    ////////
    
    
    currentAnimation = &walkingAnimationDown;
    InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    SetPosition(posX, posY);
    SetSpeed(speedX, speedY);
    SetMaxSpeed(maxSpeedX, maxSpeedY);
    SetOriginAnimatedSprite(32,38);
}

void Player::Update(sf::Vector2f velocity, sf::Time elapsedTime) {
    /**Hay que normalizar la velocidad**/
    sf::Vector2f nVelocity = Util::Normalize(velocity);
    SetSpeed(nVelocity * Player::getVelocidad());
    PhysicsState::Update(elapsedTime);
}

void Player::Draw() {
    GetSprite().setPosition(GetPosition().x,GetPosition().y);
    
    Motor2D::Instance()->draw(GetSprite());
}

void Player::DrawWithInterpolation( float interpolation) {
    
    Render::DrawAnimation(GetPreviousPosition(), GetPosition(), interpolation);
}

float Player::getVelocidad() {
    return velocity;
}
sf::Vector2f Player::getPosition() {
    return GetSpriteAnimated().getPosition();
}

void Player::UpdatePlayerAnimation(int x,int y) {
    //sf::Vector2f distancia(mouseSprite.getPosition().y - player -> GetRenderPosition().y, mouseSprite.getPosition().x - player -> GetRenderPosition().x);
   
    // 1 -> Arriba
    // 2 -> Abajo
    // 3 -> Derecha
    // 4 -> Izquierda


    if (abs(y) > abs(x) && y <= 0) {
        cuadrante = 1;
        currentAnimation = &walkingAnimationUp;
    } else if (abs(y) > abs(x) && y > 0) {
        currentAnimation = &walkingAnimationDown;
        cuadrante = 2;
    } else if (abs(x) > abs(y) && x > 0) {
        currentAnimation = &walkingAnimationRight;
        cuadrante = 3;
    } else {
        currentAnimation = &walkingAnimationLeft;
        cuadrante = 4;
    }
}
PhysicsState* Player::getPhysics() {
    return &physicsState;
}

int Player::getVida() {
    return vida;
}

int Player::restaVida(int a) {

    if (invulnerable.getTiempo() > 0.5f && (vida-a) >= 0) {
        //std::cout <<"Resto vidas";
        vida -= a;
        hud->updateHud(vida);
        invulnerable.restart();
    }


    return vida;
}

void Player::heal() {
    if (hHeal->cast()) {
        //std::cout <<"Sumo vidas";
        vida += 2;
        if (vida > 15) {
            vida = 15;

        }
        hud->updateHud(vida);
    }
}

void Player::Colocar(sf::Vector2f NuevaPosicion) {
    SetPosition(NuevaPosicion);
}