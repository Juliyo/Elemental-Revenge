/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Caster.cpp
 * Author: RuCri
 * 
 * Created on 8 de mayo de 2016, 13:13
 */

#include "Caster.hpp"
#include "../States/InGame.hpp"
#include "../Headers/Util.hpp"
#include "../Otros/tmxHelper.hpp"
#include "../States/InGame.hpp"
#include "../Motor/SoundManager.hpp"

Caster::Caster() : Collisionable((Entity*)this) {
}

Caster::~Caster() {
    delete walkingAnimationDown;
    walkingAnimationDown = nullptr;
    
    delete walkingAnimationLeft;
    walkingAnimationLeft = nullptr;
    
    delete walkingAnimationRight;
    walkingAnimationRight = nullptr;
    
    delete walkingAnimationUp;
    walkingAnimationUp = nullptr;
    
    delete animationMuerte;
    animationMuerte = nullptr;
    
    delete damaged;
    damaged = nullptr;
    
    while(!disparos->empty()){
        delete disparos->back(), disparos->pop_back();
    }
    delete disparos;
}

void Caster::Inicializar(float posX, float posY, Tipo::Caster tipo, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/
    m_tipo = tipo;
    numContactos = 0;
    damageTaken = 0;
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    animationMuerte = new Animation();
    disparos = new std::vector<DisparoEnemigo*>();
    for(int i=0;i<2;i++){
        disparos->push_back(new DisparoEnemigo());
    }

    if (tipo == Tipo::Caster::Mago) {
        //8 Maximo
        //5 Minimo
        int randNum = rand()%(5-3 + 1) + 3;
        CdDisparo = (float)randNum;
        




        walkingAnimationLeft->setSpriteSheet("resources/Textures/magoenemigo.png");
        walkingAnimationLeft->addFrame(sf::IntRect(0, 69, 67, 69));
        walkingAnimationLeft->addFrame(sf::IntRect(67, 69, 66, 69));
        walkingAnimationLeft->addFrame(sf::IntRect(133, 69, 66, 69));
        walkingAnimationLeft->addFrame(sf::IntRect(199, 69, 66, 69));


        walkingAnimationRight->setSpriteSheet("resources/Textures/magoenemigo.png");
        walkingAnimationRight->addFrame(sf::IntRect(0, 0, 66, 69));
        walkingAnimationRight->addFrame(sf::IntRect(66, 0, 66, 69));
        walkingAnimationRight->addFrame(sf::IntRect(132, 0, 66, 69));
        walkingAnimationRight->addFrame(sf::IntRect(198, 0, 67, 69));


        animationMuerte->setSpriteSheet("resources/Textures/magoenemigo.png");
        animationMuerte->addFrame(sf::IntRect(0, 138, 76, 40));





    } else {
        
        int randNum = rand()%(5-3 + 1) + 3;
        CdDisparo = (float)randNum;
        




        walkingAnimationLeft->setSpriteSheet("resources/Textures/bandidos.png");
        walkingAnimationLeft->addFrame(sf::IntRect(0, 17, 17, 17));
        walkingAnimationLeft->addFrame(sf::IntRect(17, 17, 17, 17));
        walkingAnimationLeft->addFrame(sf::IntRect(34, 17, 17, 17));
        walkingAnimationLeft->addFrame(sf::IntRect(51, 17, 16, 17));
        walkingAnimationLeft->addFrame(sf::IntRect(67, 17, 17, 17));
        walkingAnimationLeft->addFrame(sf::IntRect(84, 17, 17, 17));

        walkingAnimationRight->setSpriteSheet("resources/Textures/bandidos.png");
        walkingAnimationRight->addFrame(sf::IntRect(0, 0, 17, 17));
        walkingAnimationRight->addFrame(sf::IntRect(17, 0, 17, 17));
        walkingAnimationRight->addFrame(sf::IntRect(34, 0, 16, 17));
        walkingAnimationRight->addFrame(sf::IntRect(50, 0, 17, 17));
        walkingAnimationRight->addFrame(sf::IntRect(67, 0, 17, 17));
        walkingAnimationRight->addFrame(sf::IntRect(84, 0, 17, 17));


        animationMuerte->setSpriteSheet("resources/Textures/bandidos.png");
        animationMuerte->addFrame(sf::IntRect(0, 34, 19, 14));



      
    }


    camino = NULL;
    posiblecamino = NULL;
    currentAnimation = &animationMuerte;
    Render::InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    PhysicsState::SetPosition(posX, posY);
    PhysicsState::SetSpeed(speedX, speedY);
    Enemigo::SetVelocity(170);
    Enemigo::SetVida(2);
    Enemigo::SetDamage(3);
    PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
    Render::SetOriginAnimatedSprite(17, 16);
    SetOriginColision(17, 16);
    SetRectangleColision(0, 0, 34, 34);
    if(m_tipo == Tipo::Caster::Bandido){
        SetScaleAnimation(2.0, 2.0);
        Render::SetOriginAnimatedSprite(8, 8);
        SetOriginColision(8*2.0, 8*2.0);
        SetRectangleColision(0, 0, 17*2.0, 17*2.0);
        SetEstado(Estado::ID::Vivo);
    }else{
        SetScaleAnimation(0.6, 0.6);
        Render::SetOriginAnimatedSprite(34, 34);
        SetOriginColision(34*0.6, 34*0.6);
        SetEstado(Estado::ID::Vivo);
        SetRectangleColision(0, 0, 67*0.6, 69*0.6);
    }

    /*if (tipo == Tipo::Caster::Mago) {
        SetScaleAnimation(0.6, 0.6);
        Render::SetOriginAnimatedSprite(17, 16);
        SetOriginColision(17*0.6, 16*0.6);
        SetEstado(Estado::ID::Vivo);
        SetRectangleColision(0, 0, 34*0.6, 34*0.6);
    }
    if (tipo == Tipo::Caster::Bandido) {
        SetScaleAnimation(1.5, 1.5);
        Render::SetOriginAnimatedSprite(17*1.5, 16*1.5);
        SetOriginColision(17*1.5, 16*1.5);
        SetRectangleColision(0, 0, 34*1.5, 34*1.5);
        SetEstado(Estado::ID::Vivo);
    }*/
    
    empujado = false;
    empujado2 = false;
    damaged = new Reloj();
    //Cargamos shader del player para el colo
    LoadShader("resources/Shader/fs.frag");
    ActiveShader(false);
}

void Caster::CreateBody() {
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

//    sf::CircleShape *rs = new sf::CircleShape();
//    rs->setPosition(entity->GetPosition());
//    rs->setRadius(rectColision->GetWidth() / 2.f);
//    rs->setFillColor(sf::Color::Transparent);
//    rs->setOutlineColor(sf::Color::Red);
//    rs->setOrigin(rectColision->GetWidth() / 2.f, rectColision->GetHeight() / 2.f);
//    rs->setOutlineThickness(2);
//    InGame::Instance()->meleeShapes->push_back(rs);

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

void Caster::Update(const sf::Time elapsedTime, float x1, float x2, float multiplicador) {
    InGame* world = InGame::Instance();
    sf::Vector2f movement(0, 0);
    // if (inicio.getTiempo() > 0.5f) {
    float x = world->player->GetPosition().x - this->GetPosition().x;
    float y = world->player->GetPosition().y - this->GetPosition().y;
    if (GetEstado() == Estado::ID::Damaged && damaged->getTiempo() > 0.05f) {
        ActiveShader(false);
        SetEstado(Estado::ID::Vivo);
    }
    //Si hay un hechizo colisionando contigo restas vida
    if (numContactos > 0) {
        RestarVida(damageTaken);
    }
    distancia = sqrt(pow(x, 2) + pow(y, 2));
    if (distancia < 700) {

        if (!encola) {
            world->colaEnemigos->push_back((Enemigo*)this);
            encola = true;

        }


        inicio.restart();

        shapesDebug.clear();

    }
    // }

    SetPosition(tmx::BoxToSfVec(body->GetPosition()));
}

void Caster::Draw() {
    Render::GetSprite().setPosition(PhysicsState::GetPosition().x, PhysicsState::GetPosition().y);
    Motor2D::Instance()->draw(&GetSprite());
}

void Caster::DrawWithInterpolation(float interpolation) {
    Render::DrawAnimation(GetPreviousPosition(), GetPosition(), interpolation);
}

void Caster::PlayAnimation(Animation* animation) {
    Render::PlayAnimation(animation);

}

void Caster::UpdateEnemyAnimation(int x, int y) {
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

void Caster::UpdateAnimation(sf::Time elapsedTime) {
    Render::UpdateAnimation(elapsedTime);
}

void Caster::StopAnimation() {
    Render::StopAnimation();
}

void Caster::updateDisparoEnemigo(bool disparado, sf::Time elapsedTime, float x4, float y4) {

    sf::Vector2f movement2(0.f, 0.f);

    if (disparado) {

        if (numDisparo == 1) {
            numDisparo = 0;
        }

        if (clockCdDisparo.getTiempo() > CdDisparo || primercastDisparo == true) {
            primercastDisparo = false;
            clockCdDisparo.restart();
            disparos->at(numDisparo)->Disparar(sf::Vector2f(getPosition()), sf::Vector2f(x4, y4));
            castDisparo.restart();
        }
        numDisparo++;
    }
    for (int aux = 0; aux < disparos->size(); aux++) {
        //Si la bala esta viva updateamos su movimiento
        if (disparos->at(aux)->GetEstado() == Estado::ID::Vivo) {
            movement2.x = (40 * cos(disparos->at(aux)->angleshot2) * 10.0f);
            movement2.y = (40 * sin(disparos->at(aux)->angleshot2) * 10.0f);
            disparos->at(aux)->Update2(movement2, elapsedTime);
        } else if (disparos->at(aux)->GetEstado() == Estado::ID::Muriendo) {
            //Ademadas hacemos que su cuerpo no interactue
            disparos->at(aux)->body->SetActive(false);
            //Si la bala esta desapareciendo comprobamos hasta que desaparezca
            disparos->at(aux)->ComprobarSiMuerto();
        }

    }

}

void Caster::RestarVida(int a) {
    if (invulnerable.getTiempo() > 0.2f) {
        invulnerable.restart();
        SetVida(GetVida() - a);
        ActiveShader(true);
        damaged->restart();
        SetEstado(Estado::ID::Damaged);
        if (m_tipo == Tipo::Caster::Bandido) {
            SoundManager::Instance()->setVolumen("resources/Sounds/bandithit.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/bandithit.ogg");
        } else {
            SoundManager::Instance()->setVolumen("resources/Sounds/necromancerhurt.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/necromancerhurt.ogg");
        }
    }
    if(GetVida() <= 0){
       // std::cout<<"CAMBIO LA ANIMACION A MUERTEEEEEEEEEEEEEEE\n"<<std::endl;
       // std::cout<<"CAMBIO LA ANIMACION A MUERTEEEEEEEEEEEEEEE\n"<<std::endl;
       // std::cout<<"CAMBIO LA ANIMACION A MUERTEEEEEEEEEEEEEEE\n"<<std::endl;
        InGame::Instance()->level->map->numEnemigos--;
        currentAnimation = &animationMuerte;
        SetEstado(Estado::ID::Muriendo);
        if (m_tipo == Tipo::Caster::Bandido) {
            SoundManager::Instance()->setVolumen("resources/Sounds/banditdie.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/banditdie.ogg");
        } else {
            SoundManager::Instance()->setVolumen("resources/Sounds/necromancerdead.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/necromancerdead.ogg");
        }
    }
}

void Caster::CambiarVectorVelocidad() {
    sf::Vector2f movement(0, 0);
    if (camino != NULL) {
        if (distancia > 230) { //va a por ti
            if (nodoactual < camino->size() - 1 && camino->size() > 0) {

                // std::cout<<"Origen: "<<ceil(GetPosition().x/24)<<" , "<<ceil(GetPosition().x/24)<<std::endl;
                // std::cout<<"Destino: "<<camino->at(nodoactual+1).y<<" , "<<camino->at(nodoactual+1).y<<std::endl;
                if (round(GetPosition().x / 24) == camino->at(nodoactual + 1).x && round(GetPosition().y / 24) == camino->at(nodoactual + 1).y) {
                    nodoactual++;

                } else {
                    float x = camino->at(nodoactual + 1).x * 24 - this->GetPosition().x;
                    float y = camino->at(nodoactual + 1).y * 24 - this->GetPosition().y;
                    movement.x = x;
                    movement.y = y;
                }
            }
        } else { //si la distancia es menor esta muy cerca por lo que se alejara un poco, si se pasa vuelve a calcular tu camino con el if de arriba se acercaria de nuevo al player
            //std::cout<<"Randooom"<<std::endl;
            int x3;
            int y3;
            srand(time(1 / 25));

            int random = rand() % 4; // v1 in the range 0 to 99

            if (random == 0) {
                x3 = 5000;
                y3 = 5000;
            }

            if (random == 1) {
                x3 = -5000;
                y3 = 5000;
            }
            if (random == 2) {
                x3 = -5000;
                y3 = -5000;
            }
            if (random == 3) {
                x3 = 5000;
                y3 = -5000;
            }

            movement.x = x3;
            movement.y = y3;


        }

        //Hay que setear al BodyDef el vector velocidad que hallamos calculado
        //        if(distancia<200){
        //              movement.x = 0;
        //                movement.y = 0;
        //        }
        body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * Enemigo::GetVelocity()));

        //std::cout<<x<<" , "<<y<<std::endl;
    }
}

std::string Caster::getClassName() {
    return "Caster";
}