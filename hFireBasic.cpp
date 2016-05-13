/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hFireBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 12:45
 */

#include "../Headers/hFireBasic.hpp"
#include "../States/InGame.hpp"


void hFireBasic::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;
    
    //Creamos un objeto dinamico
    //bodyDef = new b2BodyDef();
    bodyDef.type = b2_dynamicBody; 
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    //bodyDef.bullet = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    //circleShape = new b2CircleShape();
    circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);
   /* sf::CircleShape *rs = new sf::CircleShape();
    rs->setPosition(entity->GetPosition());
    rs->setRadius(rectColision->GetWidth() / 2.f);
    rs->setFillColor(sf::Color::Transparent);
    rs->setOutlineColor(sf::Color::Red);
    rs->setOrigin(rectColision->GetWidth() / 2.f,rectColision->GetHeight() / 2.f);
    rs->setOutlineThickness(2);
    InGame::Instance()->player->shapesFuego->push_back(rs);*/
    //shape = new b2PolygonShape();
    //shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    //fixtureDef = new b2FixtureDef();
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::HECHIZO;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::ENEMIGO | Filtro::_entityCategory::BOUNDARY;
    body->CreateFixture(&fixtureDef);
}


hFireBasic::hFireBasic(): Collisionable((Entity*)this) {
    animationInicio = new Animation();
    animationFin = new Animation();
    
    animationInicio->setSpriteSheet("resources/Textures/FuegoSpriteSheet.png");
    animationInicio->addFrame(sf::IntRect(0, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 0, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 0, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 148, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 148, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 148, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 148, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 148, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 296, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 296, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 296, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 296, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 296, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 444, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 444, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 444, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 444, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 444, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 592, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 592, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 592, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 592, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 592, 152, 148));

    animationInicio->addFrame(sf::IntRect(0, 740, 152, 148));
    animationInicio->addFrame(sf::IntRect(152, 740, 152, 148));
    animationInicio->addFrame(sf::IntRect(304, 740, 152, 148));
    animationInicio->addFrame(sf::IntRect(456, 740, 152, 148));
    animationInicio->addFrame(sf::IntRect(608, 740, 152, 148));
    
    animationFin->setSpriteSheet("resources/Textures/fuegoMuriendo.png");
    
    animationFin->addFrame(sf::IntRect(0,0,172,159));
    animationFin->addFrame(sf::IntRect(172,0,172,159));
    animationFin->addFrame(sf::IntRect(344,0,172,159));
    animationFin->addFrame(sf::IntRect(516,0,172,159));
    animationFin->addFrame(sf::IntRect(688,0,172,159));
    
    currentAnimation = &animationInicio;
    
    
    Render::InicializarAnimatedSprite(sf::seconds(0.02f), true, false);
    Render::SetOriginAnimatedSprite(76, 74);
    SetOriginColision(14,15);
    Render::SetScaleAnimation(0.2, 0.2);
    SetRectangleColision(0,0,30,29);
    CreateBody();
    SetEstado(Estado::ID::Vivo);
    explosionTiempo = new Reloj();
    
    Hechizo::setDamage(0.5f);
}

std::string hFireBasic::getClassName() {
    return "hFireBasic";
}


hFireBasic::~hFireBasic() {
    delete animationFin;
    animationFin = nullptr;
    
    delete animationInicio;
    animationInicio = nullptr;
    
    currentAnimation=nullptr;
    
    delete explosionTiempo;
    explosionTiempo = nullptr;

    
}

/*void hFireBasic::Clear() {
    animationFin=NULL;
    animationInicio=NULL;
    currentAnimation=NULL;
    explosionTiempo=NULL;
}*/

void hFireBasic::cast(sf::Vector2f posicion) {
    SoundManager *sonido = SoundManager::Instance();
    //sonido->setVolumen("resources/Sounds/Fbasico.wav",SoundManager::Instance()->volumen);
    sonido->play("resources/Sounds/Fbasico.wav");
    currentAnimation = &animationInicio;
    Render::SetOriginAnimatedSprite(76, 74);
    Render::SetFrameTime(sf::seconds(0.02f));
    Render::SetScaleAnimation(0.2, 0.2);
    SetPosition(posicion);
    float angleShot = Motor2D::Instance()->getAngleShot(posicion);
    angleshot2 = angleShot; //so it goes in a straight line
    body->SetTransform(tmx::SfToBoxVec(posicion),0);
}

void hFireBasic::DrawWithInterpolation(float interpolation) {
    Draw(GetPreviousPosition(), GetPosition(), interpolation);
}

void hFireBasic::Update2(sf::Vector2f velocity, sf::Time elapsedTime) {
    SetSpeed(velocity);
    //sf::Vector2f movement(0.f, 0.f);
     //Hay que setear al BodyDef el vector velocidad que hallamos calculado
    body->SetLinearVelocity(tmx::SfToBoxVec(Util::Normalize(velocity)*450.f));
    //Actualizamos la posicion del player con la posicion del bodyDef
    SetPosition(tmx::BoxToSfVec(body->GetPosition()));
    //Update(elapsedTime);
}
void hFireBasic::Colision() {
    if(GetEstado() == Estado::Vivo){
        //SetPosition(sf::Vector2f(0,0));
        //body->SetTransform(tmx::SfToBoxVec(sf::Vector2f(0,0)),0);
        explosionTiempo->restart();
        currentAnimation = &animationFin;
        Render::SetOriginAnimatedSprite(86, 79);
        Render::SetFrameTime(sf::seconds(0.15f));
        Render::SetLooped(false);
        Render::SetScaleAnimation(0.4, 0.4);
        SetEstado(Estado::ID::Muriendo);
    }
    
}

void hFireBasic::ComprobarSiMuerto() {
    if (explosionTiempo->getTiempo() > 0.5f) {
        SetEstado(Estado::ID::Muerto);
    }
}

