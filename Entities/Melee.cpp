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

    currentAnimation = NULL;
    walkingAnimationDown = NULL;
    walkingAnimationLeft = NULL;
    walkingAnimationRight = NULL;
    walkingAnimationUp = NULL;
    animationMuerte = NULL;
    paloninja=NULL;

}

void Melee::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;

    //Creamos un objeto dinamico
    //bodyDef = new b2BodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    //circleShape = new b2CircleShape();
    circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);
    sf::CircleShape *rs = new sf::CircleShape();
    rs->setPosition(entity->GetPosition());
    rs->setRadius(rectColision->GetWidth() / 2.f);
    rs->setFillColor(sf::Color::Transparent);
    rs->setOutlineColor(sf::Color::Red);
    rs->setOrigin(rectColision->GetWidth() / 2.f, rectColision->GetHeight() / 2.f);
    rs->setOutlineThickness(2);
    InGame::Instance()->meleeShapes->push_back(rs);
    //shape = new b2PolygonShape();
    //shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    //fixtureDef = new b2FixtureDef();
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0.25f;
    fixtureDef.friction = 0.0f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::ENEMIGO;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::PLAYER | Filtro::_entityCategory::BOUNDARY | Filtro::_entityCategory::HECHIZO | Filtro::_entityCategory::ENEMIGO;

    body->CreateFixture(&fixtureDef);
}

std::string Melee::getClassName() {
    return "Melee";
}

void Melee::Inicializar(float posX, float posY, Tipo::ID tipo, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/
    m_tipo = tipo;
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    animationMuerte = new Animation();
    paloninja= new Animation();

    if (tipo == Tipo::ID::Ninja) {

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
        animationMuerte->addFrame(sf::IntRect(0, 0, 43, 32));
        
        currentAnimation = &animationMuerte;
        Render::InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
        PhysicsState::SetPosition(posX, posY);
        PhysicsState::SetSpeed(speedX, speedY);
        Enemigo::SetVelocity(150);
        Enemigo::SetVida(2);
        Enemigo::SetDamage(2);
        PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
        Render::SetOriginAnimatedSprite(11, 10);
        SetOriginColision(20, 17);
        SetEstado(Estado::ID::Vivo);
    } else {
        walkingAnimationLeft->setSpriteSheet("resources/Textures/ratas.png");
        walkingAnimationLeft->addFrame(sf::IntRect(0, 20, 27, 20));
        walkingAnimationLeft->addFrame(sf::IntRect(27, 20, 28, 20));
        walkingAnimationLeft->addFrame(sf::IntRect(55, 20, 29, 20));
        walkingAnimationLeft->addFrame(sf::IntRect(84, 20, 30, 20));
        walkingAnimationLeft->addFrame(sf::IntRect(114, 20, 26, 20));
        walkingAnimationLeft->addFrame(sf::IntRect(140, 20, 22, 20));

        walkingAnimationRight->setSpriteSheet("resources/Textures/ratas.png");
        walkingAnimationRight->addFrame(sf::IntRect(0, 0, 22, 20));
        walkingAnimationRight->addFrame(sf::IntRect(22, 0, 26, 20));
        walkingAnimationRight->addFrame(sf::IntRect(48, 0, 30, 20));
        walkingAnimationRight->addFrame(sf::IntRect(78, 0, 29, 20));
        walkingAnimationRight->addFrame(sf::IntRect(107, 0, 28, 20));
        walkingAnimationRight->addFrame(sf::IntRect(135, 0, 27, 20));


        animationMuerte->setSpriteSheet("resources/Textures/ratas.png");
        animationMuerte->addFrame(sf::IntRect(0, 40, 25, 14));
        
        currentAnimation = &animationMuerte;
        Render::InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
        PhysicsState::SetPosition(posX, posY);
        PhysicsState::SetSpeed(speedX, speedY);
        Enemigo::SetVelocity(150);
        Enemigo::SetVida(5);
        Enemigo::SetDamage(1);
        PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
        Render::SetOriginAnimatedSprite(17, 16);
        SetOriginColision(17, 16);
        SetEstado(Estado::ID::Vivo);
        SetScaleAnimation(1.7f,1.7f);

    }
    camino = NULL;
    posiblecamino = NULL;
    empujado = false;
    empujado2 = false;
}

void Melee::CambiarVectorVelocidad() {
    sf::Vector2f movement(0, 0);
    if (camino != NULL) {
        if (nodoactual < camino->size() - 1 && camino->size() > 0) {
            //std::cout<<"Origen: "<<ceil(GetPosition().x/24)<<" , "<<ceil(GetPosition().x/24)<<std::endl;
            //std::cout<<"Destino: "<<camino->at(nodoactual+1).y<<" , "<<camino->at(nodoactual+1).y<<std::endl;
            if (round(GetPosition().x / 24) == camino->at(nodoactual + 1).x && round(GetPosition().y / 24) == camino->at(nodoactual + 1).y) {
                nodoactual++;

            } else {
                float x = camino->at(nodoactual + 1).x * 24 - this->GetPosition().x;
                float y = camino->at(nodoactual + 1).y * 24 - this->GetPosition().y;
                movement.x = x;
                movement.y = y;
            }
        }
        //Hay que setear al BodyDef el vector velocidad que hallamos calculado
        body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * Enemigo::GetVelocity()));

        //std::cout<<x<<" , "<<y<<std::endl;
    }
}

void Melee::Update(const sf::Time elapsedTime, float x1, float x2, float multiplicador) {
    InGame* world = InGame::Instance();
    sf::Vector2f movement(0, 0);
    // if (inicio.getTiempo() > 0.5f) {
    float x = world->player->GetPosition().x - this->GetPosition().x;
    float y = world->player->GetPosition().y - this->GetPosition().y;
    distancia = sqrt(pow(x, 2) + pow(y, 2));
    if (distancia < 500) {
        //std::cout<<"Enemigo:"<<this->GetPosition().x/24<<","<<this->GetPosition().y/24<<"  Meta:"<<world->player->GetPosition().x/24<<","<<world->player->GetPosition().y/24<<std::endl;
        //posiblecamino = world->pathfingind->buscaCamino(this->GetPosition(), world->player->GetPosition());
        if (!encola) {
            world->colaEnemigos->push_back((Enemigo*)this);
            encola = true;
            //printf("METO ENEMIGO A LA COLA\n");
            // std::cout<<"cola size: "<<world->colaMelees->size()<<std::endl;
        }

        //        if(bueno){
        //            camino=posiblecamino;
        //            nodoactual = 0;
        //        }
        //            
        //        
        //        bueno=!bueno;

        inicio.restart();

        shapesDebug.clear();


        if (camino != NULL) {
            for (int i = 0; i < camino->size(); i++) {
                //std::cout << "Nodo " << i << " " << camino->at(i).x << "," << camino->at(i).y << "    Meta " << ceil(world->player->GetPosition().x/24) << "," << ceil(world->player->GetPosition().y/24) << std::endl;
                sf::RectangleShape shape;
                shape.setPosition(sf::Vector2f(camino->at(i).x * 24, camino->at(i).y * 24));
                shape.setSize(sf::Vector2f(24, 24));
                shape.setOrigin(12.f, 12.f);
                shape.setFillColor(color);

                shapesDebug.push_back(shape);
                //std::cout<<"Camino        "<<i<<": "<<camino->at(i).x<<","<<camino->at(i).y<<std::endl;
                //if(i<posiblecamino->size())
                //std::cout<<"Psible Camino "<<i<<": "<<posiblecamino->at(i).x<<","<<posiblecamino->at(i).y<<std::endl;
            }
        }
    }
    // }
    //Hay que setear al BodyDef el vector velocidad que hallamos calculado
    //body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * Enemigo::GetVelocity()));
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
    int vida = GetVida();
    if ((GetVida() - a) > 0) {
        SetVida(GetVida() - a);
    } else {
        currentAnimation = &animationMuerte;
        SetEstado(Estado::ID::Muriendo);
    }
}

