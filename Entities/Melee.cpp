/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Melee.cpp
 * Author: Julio
 * 
 * Created on 26 de abril de 2016, 11:19
 */

#include "Melee.hpp"
#include "../States/InGame.hpp"
#include "../Headers/Util.hpp"
#include "../Otros/tmxHelper.hpp"
Melee::Melee() : Collisionable((Entity*)this) {
}

Melee::~Melee() {
}

void Melee::Inicializar(float posX, float posY, Tipo::ID tipo,float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/
    m_tipo = tipo;
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();

    walkingAnimationDown->setSpriteSheet("resources/Textures/ninjapeq.png");
    walkingAnimationDown->addFrame(sf::IntRect(0, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(34, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(68, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(102, 0, 34, 32));



    walkingAnimationLeft->setSpriteSheet("resources/Textures/ninjapeq.png");
    walkingAnimationLeft->addFrame(sf::IntRect(0, 0, 34, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(34, 0, 34, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(68, 0, 34, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(102, 0, 34, 32));

    walkingAnimationRight->setSpriteSheet("resources/Textures/ninjapeq.png");
    walkingAnimationRight->addFrame(sf::IntRect(0, 0, 34, 32));
    walkingAnimationRight->addFrame(sf::IntRect(34, 0, 34, 32));
    walkingAnimationRight->addFrame(sf::IntRect(68, 0, 34, 32));
    walkingAnimationRight->addFrame(sf::IntRect(102, 0, 34, 32));


    walkingAnimationUp->setSpriteSheet("resources/Textures/ninjapeq.png");
    walkingAnimationUp->addFrame(sf::IntRect(0, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(34, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(68, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(102, 0, 34, 32));


    currentAnimation = &walkingAnimationDown;
    Render::InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    PhysicsState::SetPosition(posX, posY);
    PhysicsState::SetSpeed(speedX, speedY);
    Enemigo::SetVelocity(100);
    Enemigo::SetVida(5);
    PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
    Render::SetOriginAnimatedSprite(17, 16);
    SetOriginColision(17, 16);

    empujado = false;
    empujado2 = false;
}

void Melee::FindPlayer(sf::Time elapsedTime) {
    InGame* world = InGame::Instance();
    int tileWidth = 24;
    int tileHeight = 24;
    int **colisiones = world->level->map->colisiones;
    int height = world->level->map->_height;
    int width = world->level->map->_width;

    BoundingBox boundingEnemigo = CalculateNextRect(elapsedTime);
    sf::Vector2i indiceTopLeft = sf::Vector2i(boundingEnemigo.GetTopLeft().x/24,boundingEnemigo.GetTopLeft().y/24);
    sf::Vector2i indiceTopRight = sf::Vector2i(boundingEnemigo.GetTopRight().x/24,boundingEnemigo.GetTopRight().y/24);
    sf::Vector2i indiceBotLeft = sf::Vector2i(boundingEnemigo.GetBottomLeft().x/24,boundingEnemigo.GetBottomLeft().y/24);
    sf::Vector2i indiceBotRight = sf::Vector2i(boundingEnemigo.GetBottomRight().x/24,boundingEnemigo.GetBottomRight().y/24);
    /*std::cout<<"xTopright"<<indiceTopRight.x<<" , "<<"yTopright"<<indiceTopRight.y<<std::endl;
    std::cout<<"Valor mapa"<<colisiones[indiceTopRight.x][indiceTopRight.y]<<std::endl;*/
    if(indiceTopLeft.y >= 0 && indiceTopLeft.x >=0 && indiceTopLeft.y < height && indiceTopLeft.x < width && colisiones[indiceTopLeft.y][indiceTopLeft.x] == 1){
        //std::cout<<"Colisiona esquina superior izquierda"<<std::endl;
        BoundingBox boundingArbol(indiceTopLeft.x*24,indiceTopLeft.y*24,24,24);
        
        //Hacer algo
       // SetSpeed(0,0);
    }
    else if(indiceTopRight.y >= 0 && indiceTopRight.x >=0 && indiceTopRight.y < height && indiceTopRight.x < width && colisiones[indiceTopRight.y][indiceTopRight.x] == 1){
        //std::cout<<"Colisiona esquina superior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceTopRight.x*24),(indiceTopRight.y*24),24,24);
        //Hacer algo
        //SetSpeed(0,0);
    }
    else if(indiceBotLeft.y >= 0 && indiceBotLeft.x >=0 && indiceBotLeft.y < height && indiceBotLeft.x < width && colisiones[indiceBotLeft.y][indiceBotLeft.x] == 1){
        //std::cout<<"Colisiona esquina inferior izquierda"<<std::endl;
        BoundingBox boundingArbol((indiceBotLeft.x*24),(indiceBotLeft.y*24),24,24);
        
        //SetSpeed(0,0);
    }
    else if(indiceBotRight.y >= 0 && indiceBotRight.x >=0 && indiceBotRight.y < height && indiceBotRight.x < width && colisiones[indiceBotRight.y][indiceBotRight.x] == 1){
        //std::cout<<"Colisiona esquina inferior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceBotRight.x*24),(indiceBotRight.y*24),24,24);
        
        //SetSpeed(0,0);
    }
    
}

void Melee::Update(const sf::Time elapsedTime, float x1, float x2) {
    sf::Vector2f movement(x1, x2);
    /*if (up)
        movement.y -= 100.f;
    if (down)
        movement.y += 100.f;
    if (right)
        movement.x += 100.f;
    if (left)
        movement.x -= 100.f;*/
    //sf::Vector2f nVelocity = Util::Normalize(movement);
    //SetSpeed(nVelocity * Enemigo::GetVelocity());
    
    //SetSpeed(movement);
    
    FindPlayer(elapsedTime);
    //UpdateEnemigo(elapsedTime,mapa);
    //PhysicsState::Update(elapsedTime);
     //Hay que setear al BodyDef el vector velocidad que hallamos calculado
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * Enemigo::GetVelocity()));
   // FindPlayer(elapsedTime);
    //Actualizamos la posicion del player con la posicion del bodyDef
    SetPosition(tmx::BoxToSfVec(body->GetPosition()));
}

void Melee::Draw() {
     Render::GetSprite().setPosition(PhysicsState::GetPosition().x, PhysicsState::GetPosition().y);
     Motor2D::Instance()->draw(&GetSprite());
}

void Melee::DrawWithInterpolation(float interpolation) {
    Render::DrawAnimation(GetPreviousPosition(), GetPosition(), interpolation);
}

void Melee::PlayAnimation(Animation* animation) {
   Render::PlayAnimation(animation);
   
}

void Melee::UpdateEnemyAnimation(int x, int y) {
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

void Melee::UpdateAnimation(sf::Time elapsedTime) {
    Render::UpdateAnimation(elapsedTime);
}

void Melee::StopAnimation() {
    Render::StopAnimation();
}


