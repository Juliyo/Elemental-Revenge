/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Boss.cpp
 * Author: Julio
 * 
 * Created on 26 de abril de 2016, 11:19
 */

#include "Boss.hpp"
#include "../States/InGame.hpp"
#include "../Headers/Util.hpp"
#include "../Otros/tmxHelper.hpp"

Boss::Boss() : Collisionable((Entity*)this) {
}

Boss::~Boss() {
}

std::string Boss::getClassName() {
    return "Boss";
}

void Boss::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;

    //Creamos un objeto dinamico
    //bodyDef = new b2BodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(tmx::SfToBoxFloat(entity->GetPosition().x), tmx::SfToBoxFloat(entity->GetPosition().y));
    bodyDef.fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    //shape = new b2PolygonShape();
    shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    //fixtureDef = new b2FixtureDef();
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    //fixtureDef->filter.groupIndex = Filtro::_entityCategory::PLAYER;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::ENEMIGO;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::BOUNDARY | Filtro::_entityCategory::PLAYER | Filtro::_entityCategory::HECHIZO;
    body->CreateFixture(&fixtureDef);
}

void Boss::Inicializar(float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {

    motor = Motor2D::Instance();


    /*Reservamos memoria para los punteros de Animation*/
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    animationMuerte = new Animation();
    
    disparo = new std::vector<AtaqueBossA*>();

    for (int i = 0; i < 30; i++) {
        disparo->push_back(new AtaqueBossA());
    }

    rayo = new AtaqueBossB;
    espiral = new std::vector<AtaqueBossC*>();

    for (int i = 0; i < 90; i++) {
        espiral->push_back(new AtaqueBossC());
    }

    for (int i = 0; i < 30; i++) {
        rotacion[i] = 0;
    }
    for (int i = 30; i < 60; i++) {
        rotacion2[i] = 120;
    }
    for (int i = 60; i < 90; i++) {
        rotacion3[i] = 240;
    }

    walkingAnimationLeft->setSpriteSheet("resources/Textures/boss.png");
    walkingAnimationLeft->addFrame(sf::IntRect(0, 76, 60, 76));
    walkingAnimationLeft->addFrame(sf::IntRect(60, 76, 60, 76));
    walkingAnimationLeft->addFrame(sf::IntRect(120, 76, 60, 76));
    walkingAnimationLeft->addFrame(sf::IntRect(180, 76, 60, 76));

    walkingAnimationRight->setSpriteSheet("resources/Textures/boss.png");
    walkingAnimationRight->addFrame(sf::IntRect(0, 0, 60, 76));
    walkingAnimationRight->addFrame(sf::IntRect(60, 0, 60, 76));
    walkingAnimationRight->addFrame(sf::IntRect(120, 0, 60, 76));
    walkingAnimationRight->addFrame(sf::IntRect(180, 0, 60, 76));
    
    animationMuerte->setSpriteSheet("resources/Textures/boss.png");
    animationMuerte->addFrame(sf::IntRect(0, 76*2, 60, 76));

    currentAnimation = &walkingAnimationLeft;
    Render::InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    PhysicsState::SetPosition(posX, posY);
    PhysicsState::SetSpeed(speedX, speedY);
    Enemigo::SetVelocity(100);
    Enemigo::SetVida(50);

    PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
    Render::SetOriginAnimatedSprite(30, 38);
    SetOriginColision(30, 38);
    SetEstado(Estado::ID::Vivo);

    damaged = new Reloj();
    //Cargamos shader del player para el colo
    LoadShader("resources/Shader/fs.frag");
    ActiveShader(false);
    
    numContactos = 0;
    damageTaken = 0;
}

void Boss::renderAtaqueA(sf::Time elapsedTime, float interpolation) {
    for (int i = 0; i <= 29; i++) {
        if (disparo->at(i)->GetEstado() == Estado::ID::Vivo) {
            disparo->at(i)->PlayAnimation(*disparo->at(i)->currentAnimation);
            disparo->at(i)->UpdateAnimation(elapsedTime);
            disparo->at(i)->DrawAnimation(disparo->at(i)->GetPreviousPosition(), disparo->at(i)->GetPosition(), interpolation);
        } else if (disparo->at(i)->GetEstado() == Estado::ID::Muriendo) {
            disparo->at(i)->PlayAnimation(*disparo->at(i)->currentAnimation);
            disparo->at(i)->UpdateAnimation(elapsedTime);
            disparo->at(i)->DrawAnimationWithOut(disparo->at(i)->GetRenderPosition());
        } else {
            disparo->at(i)->StopAnimation();
        }
    }
}

void Boss::renderAtaqueB(sf::Time elapsedTime, float interpolation) {
    rayo->PlayAnimation(*rayo->currentAnimation);
    rayo->UpdateAnimation(elapsedTime);
    rayo->DrawAnimation(rayo->GetPreviousPosition(), rayo->GetPosition(), interpolation);
}

void Boss::renderAtaqueC(sf::Time elapsedTime, float interpolation) {

    if (espiral->at(0)->ClockResetEspiral.getTiempo() < espiral->at(0)->cdResetEspiral) {

        //printf("numBolas: %d\n", numBolasEspiral);

        for (int p = 0; p <= numBolasEspiral; p++) {
            if (p != 0) {
                espiral->at(p)->PlayAnimation(espiral->at(p)->animationAtaque);
                espiral->at(p)->UpdateAnimation(elapsedTime);
                espiral->at(p)->DrawAnimation(espiral->at(p)->GetPreviousPosition(), espiral->at(p)->GetPosition(), interpolation);
                espiral->at(p + 30)->PlayAnimation(espiral->at(p + 30)->animationAtaque);
                espiral->at(p + 30)->UpdateAnimation(elapsedTime);
                espiral->at(p + 30)->DrawAnimation(espiral->at(p + 30)->GetPreviousPosition(), espiral->at(p + 30)->GetPosition(), interpolation);
                espiral->at(p + 60)->PlayAnimation(espiral->at(p + 60)->animationAtaque);
                espiral->at(p + 60)->UpdateAnimation(elapsedTime);
                espiral->at(p + 60)->DrawAnimation(espiral->at(p + 60)->GetPreviousPosition(), espiral->at(p + 60)->GetPosition(), interpolation);
            }
        }

    }
}

void Boss::CambiarVectorVelocidad() {
    sf::Vector2f movement(0, 0);
    if (distancia > 400) {
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
        }
    } else {
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
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * Enemigo::GetVelocity()));
}

void Boss::RestarVida(int a) {
    if (invulnerable.getTiempo() > 0.2f) {
        invulnerable.restart();
        SetVida(GetVida() - a);
        ActiveShader(true);
        damaged->restart();
        SetEstado(Estado::ID::Damaged);
        /*if (m_tipo == Tipo::Caster::Bandido) {
           // SoundManager::Instance()->setVolumen("resources/Sounds/bandithit.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/bandithit.ogg");
        } else {
            //SoundManager::Instance()->setVolumen("resources/Sounds/necromancerhurt.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/necromancerhurt.ogg");
        }*/
    }
    if(GetVida() <= 0){
        InGame::Instance()->level->map->numEnemigos--;
        currentAnimation = &animationMuerte;
        SetEstado(Estado::ID::Muriendo);
        /*if (m_tipo == Tipo::Caster::Bandido) {
            //SoundManager::Instance()->setVolumen("resources/Sounds/banditdie.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/banditdie.ogg");
        } else {
            //SoundManager::Instance()->setVolumen("resources/Sounds/necromancerdead.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/necromancerdead.ogg");
        }*/
    }
}

void Boss::Update(const sf::Time elapsedTime) {
    InGame* world = InGame::Instance();
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
    camino = world->pathfingind->buscaCaminoBoss(GetPosition(), world->player->GetPosition());

    //Hay que setear al BodyDef el vector velocidad que hallamos calculado
    //body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) * multiplicador * Enemigo::GetVelocity()));
    //PhysicsState::SetSpeed(tmx::BoxToSfVec(body->GetLinearVelocity()));

    SetPosition(tmx::BoxToSfVec(body->GetPosition()));
}

void Boss::Draw() {
    Render::GetSprite().setPosition(PhysicsState::GetPosition().x, PhysicsState::GetPosition().y);
    Motor2D::Instance()->draw(&GetSprite());
}

void Boss::DrawWithInterpolation(float interpolation) {
    Render::DrawAnimation(GetPreviousPosition(), GetPosition(), interpolation);
}

void Boss::PlayAnimation(Animation* animation) {
    Render::PlayAnimation(animation);

}

void Boss::UpdateEnemyAnimation(int x, int y) {
    // 1 -> Arriba
    // 2 -> Abajo
    // 3 -> Derecha
    // 4 -> Izquierda

    /*if (abs(y) > abs(x) && y <= 0) {
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

void Boss::UpdateAnimation(sf::Time elapsedTime) {
    Render::UpdateAnimation(elapsedTime);
}

void Boss::StopAnimation() {
    Render::StopAnimation();
}

void Boss::updateAtaqueBossA(bool disparado, sf::Time elapsedTime, float x4, float y4) {

    sf::Vector2f movement2(0.f, 0.f);

    if (disparado) {

        if (numDisparo == 29) {
            numDisparo = 0;
        }

        if (clockCdDisparo.getTiempo() > CdDisparo || primercastDisparo == true) {
            primercastDisparo = false;
            clockCdDisparo.restart();
            disparo->at(numDisparo)->Disparar(sf::Vector2f(getPosition()), sf::Vector2f(x4, y4));
            castDisparo.restart();
        }
        numDisparo++;
    }
    for (int aux = 0; aux <= 29; aux++) {
        //Si la bala esta viva updateamos su movimiento
        if (disparo->at(aux)->GetEstado() == Estado::ID::Vivo) {
            movement2.x = (40 * cos(disparo->at(aux)->angleshot2) * 10.0f);
            movement2.y = (40 * sin(disparo->at(aux)->angleshot2) * 10.0f);
            disparo->at(aux)->Update2(movement2, elapsedTime);
        } else if (disparo->at(aux)->GetEstado() == Estado::ID::Muriendo) {
            //Ademadas hacemos que su cuerpo no interactue
            disparo->at(aux)->body->SetActive(false);
            //Si la bala esta desapareciendo comprobamos hasta que desaparezca
            disparo->at(aux)->ComprobarSiMuerto();
        }
    }

}

void Boss::updateAtaqueBossB(bool disparado, sf::Time elapsedTime, float x4, float y4) {

    sf::Vector2f movement2(0.f, 0.f);

    if (castDisparoRayo.getTiempo() > 1.5f) {
        rayo->SetOriginAnimatedSprite(340, 392);
        rayo->currentAnimation = &rayo->animationAtaque;
    } else {
        rayo->SetOriginAnimatedSprite(54, 30);
        rayo->currentAnimation = &rayo->animationDiana;
    }


    if (disparado) {
        if (clockCdDisparoRayo.getTiempo() > CdDisparoRayo || primercastDisparoRayo == true) {
            primercastDisparoRayo = false;
            clockCdDisparoRayo.restart();
            rayo->Disparar(sf::Vector2f(getPosition()), sf::Vector2f(x4, y4));
            rayo->posCaida = sf::Vector2f(x4, y4);
            rayo->disparo.setPosition(x4, y4);
            castDisparoRayo.restart();
        }
    }
    
    if (castDisparoRayo.getTiempo() < 1.0f) {

        rayo->SetPosition(rayo->posCaida);
    }

}

void Boss::updateAtaqueBossC(bool disparado, sf::Time elapsedTime, float x4, float y4) {
    if (espiral->at(0)->ClockResetEspiral.getTiempo() < espiral->at(0)->cdResetEspiral) {

        if (disparado) {

            if (clockCdDisparoEspiral.getTiempo() > CdDisparoEspiral) {
                // espiral->SetPosition(getPosition().x-10, getPosition().y-60);
                primercastDisparoEspiral = false;

                ///LINEA 1 DE BOLAS
                if (setOriginEspiral < 2) {
                    espiral->at(0)->SetPosition(getPosition().x, getPosition().y);
                    espiral->at(0)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x, GetSpriteAnimated().getOrigin().y);
                    setOriginEspiral++;
                } else {
                    numBolasEspiral++;
                    espiral->at(numBolasEspiral)->SetPosition(getPosition().x, getPosition().y);
                    espiral->at(numBolasEspiral)->SetOriginAnimation(espiral->at(numBolasEspiral - 1)->GetSpriteAnimated().getOrigin().x - 360, espiral->at(numBolasEspiral - 1)->GetSpriteAnimated().getOrigin().y);
                }

                ///LINEA 2 DE BOLAS   
                if (setOriginEspiral2 < 2) {
                    espiral->at(30)->SetPosition(getPosition().x, getPosition().y);
                    espiral->at(30)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x, GetSpriteAnimated().getOrigin().y);
                    setOriginEspiral2++;
                } else {
                    numBolasEspiral2++;
                    espiral->at(numBolasEspiral2 + 30)->SetPosition(getPosition().x, getPosition().y);
                    espiral->at(numBolasEspiral2 + 30)->SetOriginAnimation(espiral->at(numBolasEspiral2 + 30 - 1)->GetSpriteAnimated().getOrigin().x - 360, espiral->at(numBolasEspiral2 + 30 - 1)->GetSpriteAnimated().getOrigin().y);
                }


                ///LINEA 3 DE BOLAS
                if (setOriginEspiral3 < 2) {
                    espiral->at(numBolasEspiral3 + 60)->SetPosition(getPosition().x, getPosition().y);
                    espiral->at(numBolasEspiral3 + 60)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x, GetSpriteAnimated().getOrigin().y);

                    setOriginEspiral3++;
                } else {
                    numBolasEspiral3++;
                    espiral->at(numBolasEspiral3 + 60)->SetPosition(getPosition().x, getPosition().y);
                    espiral->at(numBolasEspiral3 + 60)->SetOriginAnimation(espiral->at(numBolasEspiral3 + 60 - 1)->GetSpriteAnimated().getOrigin().x - 360, espiral->at(numBolasEspiral3 + 60)->GetSpriteAnimated().getOrigin().y);
                }


                clockCdDisparoEspiral.restart();
                //espiral->Disparar(sf::Vector2f(getPosition()),sf::Vector2f(x4,y4));
                castDisparoEspiral.restart();
            }

            for (int i = 0; i <= numBolasEspiral; i++) {
                //espiral->SetPosition(espiral->GetPosition().x-1,espiral->GetPosition().y-1);
                espiral->at(i)->SetRotation(rotacion[i]);
                rotacion[i] += 5;
                espiral->at(i)->SetPosition(getPosition().x, getPosition().y);

                if (rotacion[i] % 360 == 45) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion[i] % 360 == 90) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion[i] % 360 == 135) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion[i] % 360 == 180) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion[i] % 360 == 225) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion[i] % 360 == 270) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion[i] % 360 == 315) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion[i] % 360 == 0) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }

            }

            for (int i = 30; i <= 30 + numBolasEspiral2; i++) {
                //espiral->SetPosition(espiral->GetPosition().x-1,espiral->GetPosition().y-1);
                espiral->at(i)->SetRotation(rotacion2[i]);
                rotacion2[i] += 5;
                espiral->at(i)->SetPosition(getPosition().x, getPosition().y);

                if (rotacion2[i] % 360 == 45) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion2[i] % 360 == 90) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion2[i] % 360 == 135) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion2[i] % 360 == 180) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion2[i] % 360 == 225) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion2[i] % 360 == 270) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion2[i] % 360 == 315) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion2[i] % 360 == 0) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }

            }

            for (int i = 60; i <= 60 + numBolasEspiral3; i++) {
                //espiral->SetPosition(espiral->GetPosition().x-1,espiral->GetPosition().y-1);
                espiral->at(i)->SetRotation(rotacion3[i]);
                rotacion3[i] += 5;
                espiral->at(i)->SetPosition(getPosition().x, getPosition().y);

                if (rotacion3[i] % 360 == 45) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion3[i] % 360 == 90) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion3[i] % 360 == 135) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion3[i] % 360 == 180) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion3[i] % 360 == 225) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion3[i] % 360 == 270) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion3[i] % 360 == 315) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }
                if (rotacion3[i] % 360 == 0) {
                    espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x + 24, espiral->at(i)->GetSpriteAnimated().getOrigin().y);
                }

            }


        }
    } else {

        if (espiral->at(0)->ClockResetEspiral.getTiempo()>(espiral->at(0)->cdResetEspiral)) {
            for (int i = 0; i < 30; i++) {
                rotacion[i] = 0;
            }
            for (int i = 30; i < 60; i++) {
                rotacion2[i] = 120;
            }
            for (int i = 60; i < 90; i++) {
                rotacion3[i] = 240;
            }


            primercastDisparoEspiral = true;
            setOriginEspiral = 0;
            setOriginEspiral2 = 0;
            setOriginEspiral3 = 0;
            numBolasEspiral = 0;
            numBolasEspiral2 = 0;
            numBolasEspiral3 = 0;
            espiral->at(0)->ClockResetEspiral.restart();
        }

    }

}


