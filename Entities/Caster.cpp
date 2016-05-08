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



Caster::Caster() : Collisionable((Entity*)this) {
}



Caster::~Caster() {
}

void Caster::Inicializar(float posX, float posY, Tipo::Caster tipo, float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    /*Reservamos memoria para los punteros de Animation*/
    m_tipo = tipo;
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    animationMuerte = new Animation();
    disparo = new DisparoEnemigo[50];

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

    camino = NULL;
    posiblecamino=NULL;
    currentAnimation = &animationMuerte;
    Render::InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    PhysicsState::SetPosition(posX, posY);
    PhysicsState::SetSpeed(speedX, speedY);
    Enemigo::SetVelocity(150);
    Enemigo::SetVida(5);
    PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
    Render::SetOriginAnimatedSprite(17, 16);
    SetOriginColision(17, 16);
    SetEstado(Estado::ID::Vivo);

    empujado = false;
    empujado2 = false;
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
    sf::CircleShape *rs = new sf::CircleShape();
    rs->setPosition(entity->GetPosition());
    rs->setRadius(rectColision->GetWidth() / 2.f);
    rs->setFillColor(sf::Color::Transparent);
    rs->setOutlineColor(sf::Color::Red);
    rs->setOrigin(rectColision->GetWidth() / 2.f,rectColision->GetHeight() / 2.f);
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


bool Caster::HandleMapCollisions(const sf::Time& elapsedTime) {
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
    sf::Vector2i indiceTopLeft = sf::Vector2i(boundingPlayer.GetTopLeft().x/24,boundingPlayer.GetTopLeft().y/24);
    sf::Vector2i indiceTopRight = sf::Vector2i(boundingPlayer.GetTopRight().x/24,boundingPlayer.GetTopRight().y/24);
    sf::Vector2i indiceBotLeft = sf::Vector2i(boundingPlayer.GetBottomLeft().x/24,boundingPlayer.GetBottomLeft().y/24);
    sf::Vector2i indiceBotRight = sf::Vector2i(boundingPlayer.GetBottomRight().x/24,boundingPlayer.GetBottomRight().y/24);
    /*std::cout<<"xTopright"<<indiceTopRight.x<<" , "<<"yTopright"<<indiceTopRight.y<<std::endl;
    std::cout<<"Valor mapa"<<colisiones[indiceTopRight.x][indiceTopRight.y]<<std::endl;*/
    
    
    if(indiceTopLeft.x>=0 && indiceTopLeft.y>=0 && indiceTopLeft.x<width &&  indiceTopLeft.y<height && colisiones[indiceTopLeft.y][indiceTopLeft.x] == 1){
        //std::cout<<"Colisiona esquina superior izquierda"<<std::endl;
        BoundingBox boundingArbol(indiceTopLeft.x*24,indiceTopLeft.y*24,24,24);
        
        //Hacer algo

        PhysicsState::SetSpeed(0,0);
        return true;
        
    }
    else if(indiceTopRight.x>=0 && indiceTopRight.y>=0 && indiceTopRight.x<width &&  indiceTopRight.y<height && colisiones[indiceTopRight.y][indiceTopRight.x] == 1){
        //std::cout<<"Colisiona esquina superior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceTopRight.x*24),(indiceTopRight.y*24),24,24);
        //Hacer algo
        PhysicsState::SetSpeed(0,0);
        //printf("Dali\n");
                return true;


    }
    else if(indiceBotLeft.x>=0 && indiceBotLeft.y>=0 && indiceBotLeft.x<width &&  indiceBotLeft.y<height && colisiones[indiceBotLeft.y][indiceBotLeft.x] == 1){
        //std::cout<<"Colisiona esquina inferior izquierda"<<std::endl;
        BoundingBox boundingArbol((indiceBotLeft.x*24),(indiceBotLeft.y*24),24,24);

        PhysicsState::SetSpeed(0,0);
                return true;


    }
    else if(indiceBotRight.x>=0 && indiceBotRight.y>=0 && indiceBotRight.x<width &&  indiceBotRight.y<height && colisiones[indiceBotRight.y][indiceBotRight.x] == 1){
        //std::cout<<"Colisiona esquina inferior derecha"<<std::endl;
        BoundingBox boundingArbol((indiceBotRight.x*24),(indiceBotRight.y*24),24,24);
        PhysicsState::SetSpeed(0,0);
                return true;


    }
    return false;

}



void Caster::Update(const sf::Time elapsedTime, float x1, float x2, float multiplicador) {
 InGame* world = InGame::Instance();
    sf::Vector2f movement(0, 0);
   // if (inicio.getTiempo() > 0.5f) {
        float x = world->player->GetPosition().x - this->GetPosition().x;
        float y = world->player->GetPosition().y - this->GetPosition().y;
         distancia = sqrt(pow(x, 2) + pow(y, 2));
        if (distancia < 700) {

            if(!encola){
                    world->colaEnemigos->push_back((Enemigo*)this);
                    encola=true;

            }

        
            inicio.restart();
            
            shapesDebug.clear();


            if (camino != NULL) {
                for (int i = 0; i < camino->size(); i++) {
                    
                    sf::RectangleShape shape;
                    shape.setPosition(sf::Vector2f(camino->at(i).x * 24, camino->at(i).y * 24));
                    shape.setSize(sf::Vector2f(24, 24));
                    shape.setOrigin(12.f, 12.f);
                    shape.setFillColor(color);

                    shapesDebug.push_back(shape);

                }
            }
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

void Caster::UpdateAnimation(sf::Time elapsedTime) {
    Render::UpdateAnimation(elapsedTime);
}

void Caster::StopAnimation() {
    Render::StopAnimation();
}



void Caster::updateDisparoEnemigo(bool disparado, sf::Time elapsedTime,float x4,float y4) {

        sf::Vector2f movement2(0.f, 0.f);
        
        if (disparado) {
            
            if (numDisparo == 49) {
                numDisparo = 0;
            }
            
            if (clockCdDisparo.getTiempo() > CdDisparo || primercastDisparo == true) {
                primercastDisparo = false;
                clockCdDisparo.restart();
                disparo[numDisparo].Disparar(sf::Vector2f(getPosition()),sf::Vector2f(x4,y4));
                castDisparo.restart();
            }
            numDisparo++;
        }
        for (int aux = 0; aux <= 49; aux++) {
            movement2.x = (40 * cos(disparo[aux].angleshot2) * 10.0f);
            movement2.y = (40 * sin(disparo[aux].angleshot2) * 10.0f);
            disparo[aux].Update2(movement2, elapsedTime);
        }

}

void Caster::RestarVida(int a) {
    int vida = GetVida();
    if ((GetVida() - a) >= 0) {
            SetVida(GetVida() - a);
    } else {
        currentAnimation = &animationMuerte;
        SetEstado(Estado::ID::Muriendo);
    }
}

void Caster::CambiarVectorVelocidad() {
    sf::Vector2f movement(0, 0);
    if (camino != NULL) {
        if(distancia>230){ //va a por ti
                   if (nodoactual < camino->size() -1 && camino->size()>0) {
            
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
        }else{ //si la distancia es menor esta muy cerca por lo que se alejara un poco, si se pasa vuelve a calcular tu camino con el if de arriba se acercaria de nuevo al player
            //std::cout<<"Randooom"<<std::endl;
            int x3;
            int y3;
                srand(time(NULL));

                int random = rand() % 4; // v1 in the range 0 to 99
    
                if(random==0){
                    x3=5000;
                    y3=5000;
                }
                 
                if(random==1){
                     x3=-5000;
                    y3=5000;
                }
                if(random==2){
                     x3=-5000;
                    y3=-5000;
                }
                if(random==3){
                     x3=5000;
                    y3=-5000;
                }
                
                movement.x=x3;
                movement.y=y3;
            
            
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