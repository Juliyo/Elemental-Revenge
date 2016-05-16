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
#include "AtaqueBossD.hpp"

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
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);

    fixtureDef.shape = &circleShape;
    fixtureDef.density = 0.25f;
    fixtureDef.friction = 0.0f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::BOSS;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::BOUNDARY | Filtro::_entityCategory::PLAYER | Filtro::_entityCategory::HECHIZO;
    body->CreateFixture(&fixtureDef);
}

void Boss::Inicializar(float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {

    motor = Motor2D::Instance();


    /*Reservamos memoria para los punteros de Animation*/
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    animationMuerte = new Animation();
    
    circuloFuego = new std::vector<AtaqueBossD*>();
    for(int i = 0; i<10; i++){
        circuloFuego->push_back(new AtaqueBossD());
    }
    
    disparo = new std::vector<AtaqueBossA*>();

    for (int i = 0; i < 30; i++) {
        disparo->push_back(new AtaqueBossA());
    }

    rayo = new AtaqueBossB;
    /*espiral = new std::vector<AtaqueBossC*>();

    for (int i = 0; i < 90; i++) {
        espiral->push_back(new AtaqueBossC());
    }*/

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
    Enemigo::SetVelocity(130);
    Enemigo::SetVida(20);

    PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
    Render::SetOriginAnimatedSprite(30, 38);
    SetOriginColision(30, 38);
    SetEstado(Estado::ID::Sleeping);

    damaged = new Reloj();
    
    //Cargamos shader del player para el colo
    LoadShader("resources/Shader/fs.frag");
    ActiveShader(false);
    
    numContactos = 0;
    damageTaken = 0;
    
    hud = new Hud();
}

void Boss::Spawn() {
    sf::Vector2f playerPos = InGame::Instance()->player->GetPosition();
    int **colisiones = InGame::Instance()->level->map->colisiones;

    int casillaPx = round(playerPos.x / 24);
    int casillaPy = round(playerPos.y / 24);
    
    int height = InGame::Instance()->level->map->_height;
    int width = InGame::Instance()->level->map->_width;
    int tileAncho = 24;
    int tileAlto = 24;

    bool condicion = casillaPy >= 0 && casillaPx >= 0 && casillaPy < height && casillaPx < width;
    
   
    sf::Vector2f posBoss;
    posBoss.x = (casillaPx+5)*24;
    posBoss.y = (casillaPy+5)*24;
    if (condicion && colisiones[casillaPy - 5][casillaPx - 5] != 1 ) {
        posBoss.x = (casillaPx - 5)*24;
        posBoss.y = (casillaPy - 5)*24;
    } else if (condicion && colisiones[casillaPy - 5][casillaPx] != 1) {
        posBoss.x = (casillaPx)*24;
        posBoss.y = (casillaPy - 5)*24;
    } else if (condicion && colisiones[casillaPy - 5][casillaPx + 5] != 1) {
        posBoss.x = (casillaPx + 5)*24;
        posBoss.y = (casillaPy - 5)*24;
    } else if (condicion && colisiones[casillaPy][casillaPx + 5] != 1) {
        posBoss.x = (casillaPx + 5)*24;
        posBoss.y = (casillaPy)*24;
    } else if (condicion && colisiones[casillaPy + 5][casillaPx + 5] != 1) {
        posBoss.x = (casillaPx + 5)*24;
        posBoss.y = (casillaPy + 5)*24;
    } else if (condicion && colisiones[casillaPy + 5][casillaPx] != 1) {
        posBoss.x = (casillaPx)*24;
        posBoss.y = (casillaPy + 5)*24;
    } else if (condicion && colisiones[casillaPy + 5][casillaPx - 5] != 1) {
        posBoss.x = (casillaPx - 5)*24;
        posBoss.y = (casillaPy + 5)*24;
    } else if (condicion && colisiones[casillaPy][casillaPx - 5] != 1) {
        posBoss.x = (casillaPx - 5)*24;
        posBoss.y = (casillaPy)*24;
    }

    body->SetTransform(tmx::SfToBoxVec(posBoss), 0);
    std::cout<<"Muevo al Boss..."<<std::endl;
    SetEstado(Estado::ID::Vivo);
    std::cout<<"Cambio Estado..."<<std::endl;
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

void Boss::renderAtaqueD(sf::Time elapsedTime, float interpolation) {
    for (int i = 0; i < circuloFuego->size(); i++) {
        if (circuloFuego->at(i)->GetEstado() == Estado::ID::Vivo) {
            circuloFuego->at(i)->PlayAnimation(*circuloFuego->at(i)->currentAnimation);
            circuloFuego->at(i)->UpdateAnimation(elapsedTime);
            circuloFuego->at(i)->DrawAnimation(circuloFuego->at(i)->GetPreviousPosition(), circuloFuego->at(i)->GetPosition(), interpolation);
        } else if (circuloFuego->at(i)->GetEstado() == Estado::ID::Muriendo) {
            circuloFuego->at(i)->PlayAnimation(*circuloFuego->at(i)->currentAnimation);
            circuloFuego->at(i)->UpdateAnimation(elapsedTime);
            circuloFuego->at(i)->DrawAnimationWithOut(circuloFuego->at(i)->GetRenderPosition());
        } else {
            circuloFuego->at(i)->StopAnimation();
        }
    }
}

void Boss::renderAtaqueC(sf::Time elapsedTime, float interpolation) {

    if (espiral->at(0)->ClockResetEspiral.getTiempo() < espiral->at(0)->cdResetEspiral) {

 

        for (int p = 0; p <= numBolasEspiral; p++) {
            if (p != 0) {
                if (espiral->at(p)->GetEstado() == Estado::ID::Vivo) {
                    espiral->at(p)->PlayAnimation(espiral->at(p)->animationAtaque);
                    espiral->at(p)->UpdateAnimation(elapsedTime);
                    espiral->at(p)->DrawAnimation(espiral->at(p)->GetPreviousPosition(), espiral->at(p)->GetPosition(), interpolation);
                } else if (espiral->at(p)->GetEstado() == Estado::ID::Muriendo) {
                    espiral->at(p)->PlayAnimation(*disparo->at(p)->currentAnimation);
                    espiral->at(p)->UpdateAnimation(elapsedTime);
                    espiral->at(p)->DrawAnimationWithOut(disparo->at(p)->GetRenderPosition());
                } else {
                    espiral->at(p)->StopAnimation();
                }
                if (espiral->at(p+30)->GetEstado() == Estado::ID::Vivo) {
                    espiral->at(p+30)->PlayAnimation(espiral->at(p+30)->animationAtaque);
                    espiral->at(p+30)->UpdateAnimation(elapsedTime);
                    espiral->at(p+30)->DrawAnimation(espiral->at(p+30)->GetPreviousPosition(), espiral->at(p+30)->GetPosition(), interpolation);
                } else if (espiral->at(p+30)->GetEstado() == Estado::ID::Muriendo) {
                    espiral->at(p+30)->PlayAnimation(*disparo->at(p+30)->currentAnimation);
                    espiral->at(p+30)->UpdateAnimation(elapsedTime);
                    espiral->at(p+30)->DrawAnimationWithOut(disparo->at(p+30)->GetRenderPosition());
                } else {
                    espiral->at(p+30)->StopAnimation();
                }
                if (espiral->at(p+60)->GetEstado() == Estado::ID::Vivo) {
                    espiral->at(p+60)->PlayAnimation(espiral->at(p+60)->animationAtaque);
                    espiral->at(p+60)->UpdateAnimation(elapsedTime);
                    espiral->at(p+60)->DrawAnimation(espiral->at(p+60)->GetPreviousPosition(), espiral->at(p+60)->GetPosition(), interpolation);
                } else if (espiral->at(p+60)->GetEstado() == Estado::ID::Muriendo) {
                    espiral->at(p+60)->PlayAnimation(*disparo->at(p+60)->currentAnimation);
                    espiral->at(p+60)->UpdateAnimation(elapsedTime);
                    espiral->at(p+60)->DrawAnimationWithOut(disparo->at(p+60)->GetRenderPosition());
                } else {
                    espiral->at(p+60)->StopAnimation();
                }
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

void Boss::RestarVida(float a) {
    
    if (invulnerable.getTiempo() > 0.2f) {
        invulnerable.restart();
        SetVida(GetVida() - a);
        hud->updateHudBoss(GetVida());
        ActiveShader(true);
        damaged->restart();
        SetEstado(Estado::ID::Damaged);
        SoundManager::Instance()->setVolumen("resources/Sounds/bandithit.ogg",SoundManager::Instance()->volumen);
        SoundManager::Instance()->play("resources/Sounds/bandithit.ogg");
        /*if (m_tipo == Tipo::Caster::Bandido) {
           // SoundManager::Instance()->setVolumen("resources/Sounds/bandithit.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/bandithit.ogg");
        } else {
            //SoundManager::Instance()->setVolumen("resources/Sounds/necromancerhurt.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/necromancerhurt.ogg");
        }*/
    }
    if(GetVida() <= 0){
        currentAnimation = &animationMuerte;
        SetEstado(Estado::ID::Muriendo);
        /*if (m_tipo == Tipo::Caster::Bandido) {
            //SoundManager::Instance()->setVolumen("resources/Sounds/banditdie.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/banditdie.ogg");
        } else {
            //SoundManager::Instance()->setVolumen("resources/Sounds/necromancerdead.ogg",SoundManager::Instance()->volumen);
            SoundManager::Instance()->play("resources/Sounds/necromancerdead.ogg");
        }*/
        InGame::Instance()->esperaNivel.restart();
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

void Boss::updateAtaqueBossD(bool disparado, sf::Time elapsedTime) {
    if (ataqueD.getTiempo() > cdAtaqueD) {
        for (int i = 0; i < circuloFuego->size(); i++) {
            circuloFuego->at(i)->cast(GetPosition(), i);
            castDisparo.restart();

        }
        ataqueD.restart();
    }
    for(int i = 0; i<circuloFuego->size();i++){
        sf::Vector2f movement2(0.f, 0.f);
        if (circuloFuego->at(i)->GetEstado() == Estado::ID::Vivo) {
            movement2.x = (40 * cos(circuloFuego->at(i)->angleshot2) * 10.0f);
            movement2.y = (40 * sin(circuloFuego->at(i)->angleshot2) * 10.0f);
            circuloFuego->at(i)->Update2(movement2, elapsedTime);
        } else if (circuloFuego->at(i)->GetEstado() == Estado::ID::Muriendo) {
            //Ademadas hacemos que su cuerpo no interactue
            circuloFuego->at(i)->body->SetActive(false);
            //Si la bala esta desapareciendo comprobamos hasta que desaparezca
            circuloFuego->at(i)->ComprobarSiMuerto();
        }
    }
    
    
}

void Boss::updateAtaqueBossA(bool disparado, sf::Time elapsedTime, float x4, float y4) {

    sf::Vector2f movement2(0.f, 0.f);

    if (disparado) {

        if (numDisparo == 29) {
            numDisparo = 0;
        }

        if (clockCdDisparo.getTiempo() > CdDisparo || primercastDisparo == true) {
            SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/Fbasico.wav");
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
        rayo->marca=false;
        rayo->relojitomagico.restart();
        rayo->body->SetActive(true);
    } else {

        rayo->SetOriginAnimatedSprite(54, 30);
        rayo->currentAnimation = &rayo->animationDiana;
       
        rayo->marca=true;
        //rayo->body->SetActive(false);
    }


    if (disparado) {
        if (clockCdDisparoRayo.getTiempo() > CdDisparoRayo || primercastDisparoRayo == true) {
         SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/RavanzadoBoss.wav");
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
        //rayo->body->SetTransform(rayo->posCaida,0);
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
                    if (espiral->at(0)->GetEstado() == Estado::ID::Vivo) {
                        
                        espiral->at(0)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)),0);
                        espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
                        espiral->at(0)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x, GetSpriteAnimated().getOrigin().y);
                        setOriginEspiral++;
                    }else{
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(0)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(0)->ComprobarSiMuerto();
                    }
                    
                } else {
                    if (espiral->at(0)->GetEstado() == Estado::ID::Vivo) {
                        numBolasEspiral++;
                        espiral->at(numBolasEspiral)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)), 0);
                        espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
                        espiral->at(numBolasEspiral)->SetOriginAnimation(espiral->at(numBolasEspiral - 1)->GetSpriteAnimated().getOrigin().x - 360, espiral->at(numBolasEspiral - 1)->GetSpriteAnimated().getOrigin().y);
                    } else {
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(numBolasEspiral)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(numBolasEspiral)->ComprobarSiMuerto();
                    }
                    
                }

                ///LINEA 2 DE BOLAS   
                if (setOriginEspiral2 < 2) {
                    if (espiral->at(30)->GetEstado() == Estado::ID::Vivo) {
                        espiral->at(30)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)),0);
                        espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
                        espiral->at(30)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x, GetSpriteAnimated().getOrigin().y);
                        setOriginEspiral2++;
                    }else{
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(30)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(30)->ComprobarSiMuerto();
                    }
                    
                } else {
                    if (espiral->at(numBolasEspiral2 + 30)->GetEstado() == Estado::ID::Vivo) {
                        numBolasEspiral2++;
                        espiral->at(numBolasEspiral2 + 30)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)),0);
                        espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
                        espiral->at(numBolasEspiral2 + 30)->SetOriginAnimation(espiral->at(numBolasEspiral2 + 30 - 1)->GetSpriteAnimated().getOrigin().x - 360, espiral->at(numBolasEspiral2 + 30 - 1)->GetSpriteAnimated().getOrigin().y);
                    }else{
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(numBolasEspiral2 + 30)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(numBolasEspiral2 + 30)->ComprobarSiMuerto();
                    }
                    
                }


                ///LINEA 3 DE BOLAS
                if (setOriginEspiral3 < 2) {
                    if (espiral->at(numBolasEspiral3 + 60)->GetEstado() == Estado::ID::Vivo) {
                        espiral->at(numBolasEspiral3 + 60)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)), 0);
                        espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
                        espiral->at(numBolasEspiral3 + 60)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x, GetSpriteAnimated().getOrigin().y);
                    } else {
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(numBolasEspiral3 + 60)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(numBolasEspiral3 + 60)->ComprobarSiMuerto();
                    }
                    setOriginEspiral3++;
                } else {
                    if (espiral->at(numBolasEspiral3 + 60)->GetEstado() == Estado::ID::Vivo) {
                        numBolasEspiral3++;
                        espiral->at(numBolasEspiral3 + 60)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)),0);
                        espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
                        espiral->at(numBolasEspiral3 + 60)->SetOriginAnimation(espiral->at(numBolasEspiral3 + 60 - 1)->GetSpriteAnimated().getOrigin().x - 360, espiral->at(numBolasEspiral3 + 60)->GetSpriteAnimated().getOrigin().y);
                
                    }else{
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(numBolasEspiral3 + 60)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(numBolasEspiral3 + 60)->ComprobarSiMuerto();
                    }
                }


                clockCdDisparoEspiral.restart();
                //espiral->Disparar(sf::Vector2f(getPosition()),sf::Vector2f(x4,y4));
                castDisparoEspiral.restart();
            }

            for (int i = 0; i <= numBolasEspiral; i++) {
                //espiral->SetPosition(espiral->GetPosition().x-1,espiral->GetPosition().y-1);
                if (espiral->at(i)->GetEstado() == Estado::ID::Vivo) {
                    espiral->at(i)->SetRotation(rotacion[i]);
                    rotacion[i] += 5;
                    espiral->at(i)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)), 0);
                    espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
                    
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
                } else {
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(i)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(i)->ComprobarSiMuerto();
                }


            }

            for (int i = 30; i <= 30 + numBolasEspiral2; i++) {
                if (espiral->at(i)->GetEstado() == Estado::ID::Vivo) {
                    espiral->at(i)->SetRotation(rotacion2[i]);
                    rotacion2[i] += 5;
                    
                    espiral->at(i)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)), 0);
                    espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
                    
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
                } else {
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(i)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(i)->ComprobarSiMuerto();
                }


            }

            for (int i = 60; i <= 60 + numBolasEspiral3; i++) {
                if (espiral->at(i)->GetEstado() == Estado::ID::Vivo) {
                    espiral->at(i)->SetRotation(rotacion3[i]);
                    rotacion3[i] += 5;
                    
                    espiral->at(i)->body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(getPosition().x, getPosition().y)), 0);
                    espiral->at(0)->SetPosition(tmx::BoxToSfVec(body->GetPosition()));
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
                } else {
                        //Ademadas hacemos que su cuerpo no interactue
                        espiral->at(i)->body->SetActive(false);
                        //Si la bala esta desapareciendo comprobamos hasta que desaparezca
                        espiral->at(i)->ComprobarSiMuerto();
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


