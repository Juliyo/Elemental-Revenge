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
    SetVida(2);
}

Melee::~Melee() {
}

void Melee::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;
    
    //Creamos un objeto dinamico
    bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody; 
    bodyDef->position.Set(tmx::SfToBoxFloat(entity->GetPosition().x),tmx::SfToBoxFloat(entity->GetPosition().y));
    bodyDef->fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    circleShape = new b2CircleShape();
    circleShape->m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);
    //shape->SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    fixtureDef = new b2FixtureDef();
    fixtureDef->shape = circleShape;
    fixtureDef->density = 0.25f;
    fixtureDef->friction = 0.0f;
    body->CreateFixture(fixtureDef);
}

std::string Melee::getClassName() {
    return "Melee";
}

bool Melee::HandleMapCollisions(const sf::Time& elapsedTime) {
    InGame* world = InGame::Instance();
    /* for (int i = 0; i < objetosCercanos.size(); i++) {
         BoundingBox bb(objetosCercanos.at(i)->GetAABB());
         if (CheckColision(bb, elapsedTime)) {
             type = TypeOfColision(bb, elapsedTime);
             OnColision(type);
         }
     }*/
    int tileWidth = 24;
    int tileHeight = 24;
    int **colisiones = world->level->map->colisiones;
    int height = world->level->map->_height;
    int width = world->level->map->_width;
    /*for(int i=0 ; i < width ; i++){
        for(int j= 0;j<height; j++){
            std::cout<<colisiones[i][j];
        }
        std::cout<<std::endl;
    }*/

    BoundingBox boundingPlayer = Collisionable::CalculateNextRect(elapsedTime);
    sf::Vector2i indiceTopLeft = sf::Vector2i(boundingPlayer.GetTopLeft().x / 24, boundingPlayer.GetTopLeft().y / 24);
    sf::Vector2i indiceTopRight = sf::Vector2i(boundingPlayer.GetTopRight().x / 24, boundingPlayer.GetTopRight().y / 24);
    sf::Vector2i indiceBotLeft = sf::Vector2i(boundingPlayer.GetBottomLeft().x / 24, boundingPlayer.GetBottomLeft().y / 24);
    sf::Vector2i indiceBotRight = sf::Vector2i(boundingPlayer.GetBottomRight().x / 24, boundingPlayer.GetBottomRight().y / 24);
    /*std::cout<<"xTopright"<<indiceTopRight.x<<" , "<<"yTopright"<<indiceTopRight.y<<std::endl;
    std::cout<<"Valor mapa"<<colisiones[indiceTopRight.x][indiceTopRight.y]<<std::endl;*/


    if (indiceTopLeft.x >= 0 && indiceTopLeft.y >= 0 && indiceTopLeft.x < width && indiceTopLeft.y < height && colisiones[indiceTopLeft.y][indiceTopLeft.x] == 1) {
        //std::cout<<"Colisiona esquina superior izquierda"<<std::endl;
        BoundingBox boundingArbol(indiceTopLeft.x * 24, indiceTopLeft.y * 24, 24, 24);

        //Hacer algo

        PhysicsState::SetSpeed(0, 0);
        return true;

    } else if (indiceTopRight.x >= 0 && indiceTopRight.y >= 0 && indiceTopRight.x < width && indiceTopRight.y < height && colisiones[indiceTopRight.y][indiceTopRight.x] == 1) {
        //std::cout<<"Colisiona esquina superior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceTopRight.x * 24), (indiceTopRight.y * 24), 24, 24);
        //Hacer algo
        PhysicsState::SetSpeed(0, 0);
        //printf("Dali\n");
        return true;


    } else if (indiceBotLeft.x >= 0 && indiceBotLeft.y >= 0 && indiceBotLeft.x < width && indiceBotLeft.y < height && colisiones[indiceBotLeft.y][indiceBotLeft.x] == 1) {
        //std::cout<<"Colisiona esquina inferior izquierda"<<std::endl;
        BoundingBox boundingArbol((indiceBotLeft.x * 24), (indiceBotLeft.y * 24), 24, 24);

        PhysicsState::SetSpeed(0, 0);
        return true;


    } else if (indiceBotRight.x >= 0 && indiceBotRight.y >= 0 && indiceBotRight.x < width && indiceBotRight.y < height && colisiones[indiceBotRight.y][indiceBotRight.x] == 1) {
        //std::cout<<"Colisiona esquina inferior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceBotRight.x * 24), (indiceBotRight.y * 24), 24, 24);
        PhysicsState::SetSpeed(0, 0);
        return true;

    }
    return false;

}

void Melee::Inicializar(float posX, float posY, Tipo::ID tipo, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/
    m_tipo = tipo;
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    animationMuerte = new Animation();

    walkingAnimationDown->setSpriteSheet("resources/Textures/ninjapeq.png");
    walkingAnimationDown->addFrame(sf::IntRect(0, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(34, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(68, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(102, 0, 34, 32));



    walkingAnimationLeft->setSpriteSheet("resources/Textures/walkingNinjaLeft.png");
    walkingAnimationLeft->addFrame(sf::IntRect(0, 0, 34, 34));
    walkingAnimationLeft->addFrame(sf::IntRect(35, 0, 34, 34));
    walkingAnimationLeft->addFrame(sf::IntRect(70, 0, 34, 34));
    walkingAnimationLeft->addFrame(sf::IntRect(105, 0, 32, 34));
    walkingAnimationLeft->addFrame(sf::IntRect(138, 0, 34, 34));
    walkingAnimationLeft->addFrame(sf::IntRect(173, 0, 34, 34));

    walkingAnimationRight->setSpriteSheet("resources/Textures/walkingNinjaRight.png");
    walkingAnimationRight->addFrame(sf::IntRect(0, 0, 34, 34));
    walkingAnimationRight->addFrame(sf::IntRect(35, 0, 34, 34));
    walkingAnimationRight->addFrame(sf::IntRect(70, 0, 32, 34));
    walkingAnimationRight->addFrame(sf::IntRect(103, 0, 34, 34));
    walkingAnimationRight->addFrame(sf::IntRect(138, 0, 34, 34));
    walkingAnimationRight->addFrame(sf::IntRect(173, 0, 34, 34));


    walkingAnimationUp->setSpriteSheet("resources/Textures/ninjapeq2.png");
    walkingAnimationUp->addFrame(sf::IntRect(0, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(34, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(68, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(102, 0, 34, 32));
    
    animationMuerte->setSpriteSheet("resources/Textures/ninjaMuerto.png");
    animationMuerte->addFrame(sf::IntRect(0,0,43,32));


    currentAnimation = &animationMuerte;
    Render::InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    PhysicsState::SetPosition(posX, posY);
    PhysicsState::SetSpeed(speedX, speedY);
    Enemigo::SetVelocity(100);
    Enemigo::SetVida(5);
    PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
    Render::SetOriginAnimatedSprite(17, 16);
    SetOriginColision(17, 16);
    SetEstado(Estado::ID::Vivo);

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
    sf::Vector2i indiceTopLeft = sf::Vector2i(boundingEnemigo.GetTopLeft().x / 24, boundingEnemigo.GetTopLeft().y / 24);
    sf::Vector2i indiceTopRight = sf::Vector2i(boundingEnemigo.GetTopRight().x / 24, boundingEnemigo.GetTopRight().y / 24);
    sf::Vector2i indiceBotLeft = sf::Vector2i(boundingEnemigo.GetBottomLeft().x / 24, boundingEnemigo.GetBottomLeft().y / 24);
    sf::Vector2i indiceBotRight = sf::Vector2i(boundingEnemigo.GetBottomRight().x / 24, boundingEnemigo.GetBottomRight().y / 24);
    /*std::cout<<"xTopright"<<indiceTopRight.x<<" , "<<"yTopright"<<indiceTopRight.y<<std::endl;
    std::cout<<"Valor mapa"<<colisiones[indiceTopRight.x][indiceTopRight.y]<<std::endl;*/
    if (indiceTopLeft.y >= 0 && indiceTopLeft.x >= 0 && indiceTopLeft.y < height && indiceTopLeft.x < width && colisiones[indiceTopLeft.y][indiceTopLeft.x] == 1) {
        //std::cout<<"Colisiona esquina superior izquierda"<<std::endl;
        BoundingBox boundingArbol(indiceTopLeft.x * 24, indiceTopLeft.y * 24, 24, 24);

        //Hacer algo
        // SetSpeed(0,0);
    } else if (indiceTopRight.y >= 0 && indiceTopRight.x >= 0 && indiceTopRight.y < height && indiceTopRight.x < width && colisiones[indiceTopRight.y][indiceTopRight.x] == 1) {
        //std::cout<<"Colisiona esquina superior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceTopRight.x * 24), (indiceTopRight.y * 24), 24, 24);
        //Hacer algo
        //SetSpeed(0,0);
    } else if (indiceBotLeft.y >= 0 && indiceBotLeft.x >= 0 && indiceBotLeft.y < height && indiceBotLeft.x < width && colisiones[indiceBotLeft.y][indiceBotLeft.x] == 1) {
        //std::cout<<"Colisiona esquina inferior izquierda"<<std::endl;
        BoundingBox boundingArbol((indiceBotLeft.x * 24), (indiceBotLeft.y * 24), 24, 24);

        //SetSpeed(0,0);
    } else if (indiceBotRight.y >= 0 && indiceBotRight.x >= 0 && indiceBotRight.y < height && indiceBotRight.x < width && colisiones[indiceBotRight.y][indiceBotRight.x] == 1) {
        //std::cout<<"Colisiona esquina inferior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceBotRight.x * 24), (indiceBotRight.y * 24), 24, 24);

        //SetSpeed(0,0);
    }

}

void Melee::Update(const sf::Time elapsedTime, float x1, float x2, float multiplicador) {
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
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * multiplicador * Enemigo::GetVelocity()));
    PhysicsState::SetSpeed(tmx::BoxToSfVec(body->GetLinearVelocity()));
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
/*
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
    }*/
    
    
       if (x > 0) {
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

void Melee::RestarVida(int a) {
    if ((GetVida() - a) >= 0) {
        SetVida(GetVida() - a);
    } else {
            currentAnimation = &animationMuerte;
            body->SetActive(false);
        SetEstado(Estado::ID::Muerto);
    }
}

