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



bool Boss::HandleMapCollisions(const sf::Time& elapsedTime) {
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
    fixtureDef.filter.maskBits =  Filtro::_entityCategory::BOUNDARY | Filtro::_entityCategory::PLAYER;
    body->CreateFixture(&fixtureDef);
}


void Boss::Inicializar(float posX, float posY,float speedX, float speedY, float maxSpeedX, float maxSpeedY) {
    
        motor = Motor2D::Instance();

    
    /*Reservamos memoria para los punteros de Animation*/
    walkingAnimationDown = new Animation();
    walkingAnimationLeft = new Animation();
    walkingAnimationRight = new Animation();
    walkingAnimationUp = new Animation();
    
    disparo = new std::vector<AtaqueBossA*>();
    
    for(int i=0;i<30;i++){
        disparo->push_back(new AtaqueBossA());
    }
    
    rayo = new AtaqueBossB;
    espiral = new std::vector<AtaqueBossC*>();
    
    for(int i=0;i<150;i++){
        espiral->push_back(new AtaqueBossC());
    }
    
    for(int i=0; i<50;i++){
        rotacion[i]=0;
    }
    for(int i=50; i<100;i++){
        rotacion2[i]=120;
    }
    for(int i=100; i<150;i++){
        rotacion3[i]=240;
    }

    walkingAnimationDown->setSpriteSheet("resources/Textures/ninjapeq.png");
    walkingAnimationDown->addFrame(sf::IntRect(0, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(34, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(68, 0, 34, 32));
    walkingAnimationDown->addFrame(sf::IntRect(102, 0, 34, 32));



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


    walkingAnimationUp->setSpriteSheet("resources/Textures/ninjapeq.png");
    walkingAnimationUp->addFrame(sf::IntRect(0, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(34, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(68, 0, 34, 32));
    walkingAnimationUp->addFrame(sf::IntRect(102, 0, 34, 32));


    currentAnimation = &walkingAnimationLeft;
    Render::InicializarAnimatedSprite(sf::seconds(0.075f), true, false);
    PhysicsState::SetPosition(posX, posY);
    PhysicsState::SetSpeed(speedX, speedY);
    Enemigo::SetVelocity(100);
    Enemigo::SetVida(5);
    PhysicsState::SetMaxSpeed(maxSpeedX, maxSpeedY);
    Render::SetOriginAnimatedSprite(30, 38);
    SetOriginColision(30, 38);
    
    

    empujado = false;
    empujado2 = false;
}


void Boss::renderAtaqueA(sf::Time elapsedTime, float interpolation) {

    for (int k = 0; k <= 29; k++) {
        disparo->at(k)->PlayAnimation(disparo->at(k)->animationAtaque);
        disparo->at(k)->UpdateAnimation(elapsedTime);
        disparo->at(k)->DrawAnimation(disparo->at(k)->GetPreviousPosition(),disparo->at(k)->GetPosition(), interpolation);


    }
}

void Boss::renderAtaqueB(sf::Time elapsedTime, float interpolation) {

        
        rayo->PlayAnimation(*rayo->currentAnimation);
        rayo->UpdateAnimation(elapsedTime);
        rayo->DrawAnimation(rayo->GetPreviousPosition(),rayo->GetPosition(), interpolation);

     
}

void Boss::renderAtaqueC(sf::Time elapsedTime, float interpolation) {

    
     if(espiral->at(0)->ClockResetEspiral.getTiempo()<espiral->at(0)->cdResetEspiral){

         //printf("numBolas: %d\n", numBolasEspiral);
    
        for (int p = 0; p <= numBolasEspiral; p++) {
            if(p!=0){
        espiral->at(p)->PlayAnimation(espiral->at(p)->animationAtaque);
        espiral->at(p)->UpdateAnimation(elapsedTime);
        espiral->at(p)->DrawAnimation(espiral->at(p)->GetPreviousPosition(),espiral->at(p)->GetPosition(), interpolation);
        espiral->at(p+50)->PlayAnimation( espiral->at(p+50)->animationAtaque);
         espiral->at(p+50)->UpdateAnimation(elapsedTime);
         espiral->at(p+50)->DrawAnimation( espiral->at(p+50)->GetPreviousPosition(), espiral->at(p+50)->GetPosition(), interpolation);
         espiral->at(p+100)->PlayAnimation(espiral->at(p+100)->animationAtaque);
        espiral->at(p+100)->UpdateAnimation(elapsedTime);
        espiral->at(p+100)->DrawAnimation(espiral->at(p+100)->GetPreviousPosition(),espiral->at(p+100)->GetPosition(), interpolation);
            }
        }
        
     }
}




void Boss::Update(const sf::Time elapsedTime, float x1, float x2, float multiplicador) {
    sf::Vector2f movement(x1, x2);

    //Hay que setear al BodyDef el vector velocidad que hallamos calculado
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(movement) *multiplicador* Enemigo::GetVelocity()));
    PhysicsState::SetSpeed(tmx::BoxToSfVec(body->GetLinearVelocity()));

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



void Boss::updateAtaqueBossA(bool disparado, sf::Time elapsedTime,float x4,float y4) {

        sf::Vector2f movement2(0.f, 0.f);
        
        if (disparado) {
            
            if (numDisparo == 29) {
                numDisparo = 0;
            }
            
            if (clockCdDisparo.getTiempo() > CdDisparo || primercastDisparo == true) {
                primercastDisparo = false;
                clockCdDisparo.restart();
                disparo->at(numDisparo)->Disparar(sf::Vector2f(getPosition()),sf::Vector2f(x4,y4));
                castDisparo.restart();
            }
            numDisparo++;
        }
        for (int aux = 0; aux <= 29; aux++) {
            movement2.x = (40 * cos(disparo->at(aux)->angleshot2) * 10.0f);
            movement2.y = (40 * sin(disparo->at(aux)->angleshot2) * 10.0f);
            disparo->at(aux)->Update2(movement2, elapsedTime);
        }

}




void Boss::updateAtaqueBossB(bool disparado, sf::Time elapsedTime,float x4,float y4) {

        sf::Vector2f movement2(0.f, 0.f);
        
        
    if(castDisparoRayo.getTiempo()>1.5f){
        rayo->SetOriginAnimatedSprite(340,392);
        rayo->currentAnimation=&rayo->animationAtaque;
    }
    else{
        rayo->SetOriginAnimatedSprite(54,30);
        rayo->currentAnimation=&rayo->animationDiana;
    }
        
        
        if (disparado) {
            

            if (clockCdDisparoRayo.getTiempo() > CdDisparoRayo || primercastDisparoRayo == true) {
                primercastDisparoRayo = false;
                clockCdDisparoRayo.restart();
                rayo->Disparar(sf::Vector2f(getPosition()),sf::Vector2f(x4,y4));
                rayo->posCaida=sf::Vector2f(x4,y4);
                rayo->disparo.setPosition(x4,y4);
                castDisparoRayo.restart();
            }

        }
        

        if(castDisparoRayo.getTiempo()<1.0f){
        
            rayo->SetPosition(rayo->posCaida);
        }
        

        
        

}


void Boss::updateAtaqueBossC(bool disparado, sf::Time elapsedTime,float x4,float y4) {


        if(espiral->at(0)->ClockResetEspiral.getTiempo()<espiral->at(0)->cdResetEspiral){
        
        if (disparado) {

            if (clockCdDisparoEspiral.getTiempo() > CdDisparoEspiral) {
               // espiral->SetPosition(getPosition().x-10, getPosition().y-60);
                primercastDisparoEspiral = false;

                ///LINEA 1 DE BOLAS
                if(setOriginEspiral<2){
                espiral->at(0)->SetPosition(getPosition().x, getPosition().y);
                espiral->at(0)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x,GetSpriteAnimated().getOrigin().y);
                setOriginEspiral++;
                }
                else{
                numBolasEspiral++;
                espiral->at(numBolasEspiral)->SetPosition(getPosition().x, getPosition().y);
                espiral->at(numBolasEspiral)->SetOriginAnimation(espiral->at(numBolasEspiral-1)->GetSpriteAnimated().getOrigin().x-360,espiral->at(numBolasEspiral-1)->GetSpriteAnimated().getOrigin().y);
                }
                
                ///LINEA 2 DE BOLAS   
                if(setOriginEspiral2<2){
                espiral->at(50)->SetPosition(getPosition().x, getPosition().y);
                espiral->at(50)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x,GetSpriteAnimated().getOrigin().y);
                setOriginEspiral2++;
                }
                else{
                numBolasEspiral2++;
                espiral->at(numBolasEspiral2+50)->SetPosition(getPosition().x, getPosition().y);
                espiral->at(numBolasEspiral2+50)->SetOriginAnimation(espiral->at(numBolasEspiral2+50-1)->GetSpriteAnimated().getOrigin().x-360,espiral->at(numBolasEspiral2+50-1)->GetSpriteAnimated().getOrigin().y);
                }
                
                
                ///LINEA 3 DE BOLAS
                if(setOriginEspiral3<2){
                espiral->at(numBolasEspiral3+100)->SetPosition(getPosition().x, getPosition().y);
                espiral->at(numBolasEspiral3+100)->SetOriginAnimation(GetSpriteAnimated().getOrigin().x, GetSpriteAnimated().getOrigin().y);
                
                setOriginEspiral3++;
                }
                else{
                numBolasEspiral3++;
                espiral->at(numBolasEspiral3+100)->SetPosition(getPosition().x, getPosition().y);
                espiral->at(numBolasEspiral3+100)->SetOriginAnimation(espiral->at(numBolasEspiral3+100-1)->GetSpriteAnimated().getOrigin().x-360,espiral->at(numBolasEspiral3+100)->GetSpriteAnimated().getOrigin().y);
                }
                
                
                clockCdDisparoEspiral.restart();
                //espiral->Disparar(sf::Vector2f(getPosition()),sf::Vector2f(x4,y4));
                castDisparoEspiral.restart();
            }
            
            for(int i=0; i<=numBolasEspiral;i++){
            //espiral->SetPosition(espiral->GetPosition().x-1,espiral->GetPosition().y-1);
            espiral->at(i)->SetRotation(rotacion[i]);
            rotacion[i]+=5;
            espiral->at(i)->SetPosition(getPosition().x, getPosition().y);
            
            if(rotacion[i]%360==45){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion[i]%360==90){
               espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion[i]%360==135){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion[i]%360==180){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion[i]%360==225){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion[i]%360==270){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }            
            if(rotacion[i]%360==315){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion[i]%360==0){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }

            }
            
            for(int i=50; i<=50+numBolasEspiral2;i++){
            //espiral->SetPosition(espiral->GetPosition().x-1,espiral->GetPosition().y-1);
            espiral->at(i)->SetRotation(rotacion2[i]);
            rotacion2[i]+=5;
            espiral->at(i)->SetPosition(getPosition().x, getPosition().y);
            
            if(rotacion2[i]%360==45){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion2[i]%360==90){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion2[i]%360==135){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion2[i]%360==180){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion2[i]%360==225){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion2[i]%360==270){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }            
            if(rotacion2[i]%360==315){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion2[i]%360==0){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }

            }
            
            for(int i=100; i<=100+numBolasEspiral3;i++){
            //espiral->SetPosition(espiral->GetPosition().x-1,espiral->GetPosition().y-1);
            espiral->at(i)->SetRotation(rotacion3[i]);
            rotacion3[i]+=5;
            espiral->at(i)->SetPosition(getPosition().x, getPosition().y);
            
            if(rotacion3[i]%360==45){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion3[i]%360==90){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion3[i]%360==135){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion3[i]%360==180){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion3[i]%360==225){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion3[i]%360==270){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }            
            if(rotacion3[i]%360==315){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }
            if(rotacion3[i]%360==0){
                espiral->at(i)->SetOriginAnimation(espiral->at(i)->GetSpriteAnimated().getOrigin().x+24,espiral->at(i)->GetSpriteAnimated().getOrigin().y);
            }

            }
            
            
        }
        }else{
            
            if(espiral->at(0)->ClockResetEspiral.getTiempo()>(espiral->at(0)->cdResetEspiral)){
                    for(int i=0; i<50;i++){
                     rotacion[i]=0;
                    }
                    for(int i=50; i<100;i++){
                        rotacion2[i]=120;
                    }
                    for(int i=100; i<150;i++){
                        rotacion3[i]=240;
                    }
                    

                primercastDisparoEspiral=true;
                setOriginEspiral=0;
                setOriginEspiral2=0;
                setOriginEspiral3=0;
                numBolasEspiral=0;
                numBolasEspiral2=0;
                numBolasEspiral3=0;
                espiral->at(0)->ClockResetEspiral.restart();
            }
            
        }

}


