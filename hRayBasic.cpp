/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hRayBasic.cpp
 * Author: tonir
 * 
 * Created on 22 de febrero de 2016, 23:05
 */

#include "../Headers/hRayBasic.hpp"
#include "Entities/Player.hpp"
#include "Motor/Motor2D.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>
#include "States/InGame.hpp"

void hRayBasic::CreateBody() {
    physicWorld = InGame::Instance()->physicWorld;
    
    //Creamos un objeto dinamico
    //bodyDef = new b2BodyDef();
    bodyDef.type = b2_kinematicBody; 
    bodyDef.position = (tmx::SfToBoxVec(entity->GetPosition()));
    bodyDef.fixedRotation = true;
    //Añadimos el objeto al mundo
    body = physicWorld->CreateBody(&bodyDef);
    body->SetUserData(this);
    
    //Se crea una shape, le damos las dimensiones pasandole la mitad del ancho y la mitad del alto
    //del BoundingBox
    //circleShape = new b2CircleShape();
    shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth()/2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f)/*,tmx::SfToBoxVec(sf::Vector2f(40,-30)),0*/);
    //circleShape.m_radius = tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f);
    InGame::Instance()->rs = new sf::RectangleShape();
    InGame::Instance()->rs->setPosition(InGame::Instance()->player->GetPosition().x,InGame::Instance()->player->GetPosition().y*-1);
    InGame::Instance()->rs->setFillColor(sf::Color::Transparent);
    InGame::Instance()->rs->setOutlineColor(sf::Color::Blue);
    //InGame::Instance()->rs->setOrigin(40,-30);
    InGame::Instance()->rs->setOutlineThickness(2);
    InGame::Instance()->rs->setSize(sf::Vector2f(445,89));
    /*sf::CircleShape *rs = new sf::CircleShape();
    rs->setPosition(InGame::Instance()->player->GetPosition().x,InGame::Instance()->player->GetPosition().y*-1);
    rs->setRadius(rectColision->GetWidth() / 2.f);
    rs->setFillColor(sf::Color::Transparent);
    rs->setOutlineColor(sf::Color::Blue);
    rs->setOrigin(rectColision->GetWidth() / 2.f,rectColision->GetHeight() / 2.f);
    rs->setOutlineThickness(2);
    
    InGame::Instance()->player->shapesFuego->push_back(rs);*/
    //shape = new b2PolygonShape();
    //shape.SetAsBox(tmx::SfToBoxFloat(rectColision->GetWidth() / 2.f), tmx::SfToBoxFloat(rectColision->GetHeight() / 2.f));
    //Objeto que le da las propiedades fisicas al bodyDef
    //fixtureDef = new b2FixtureDef();
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.restitution = 0.7f;
    fixtureDef.filter.categoryBits = Filtro::_entityCategory::HECHIZO;
    fixtureDef.filter.maskBits = Filtro::_entityCategory::ENEMIGO;
    body->CreateFixture(&fixtureDef);
}

hRayBasic::hRayBasic(): Collisionable((Entity*)this) {
    
    draw = false;
    animation = new Animation();
    animationDurante = new Animation();
    PrimeraAnimacion = new Animation();
    setCD(5);
    hDamage = 3;
    setCast(3);
    if (!hTexture.loadFromFile("resources/Textures/RayoSpriteSheet.png")) {

        //comentario error
        exit(0);
    }
    // hSprite.setTexture(hTexture);
    //SetPosition()
    PrimeraAnimacion->setSpriteSheet("resources/Textures/RayoSpriteSheet.png");
    animationDurante->setSpriteSheet("resources/Textures/RayoSpriteSheet.png");

    animationDurante->addFrame(sf::IntRect(0, 445, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(0, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(0, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(0, 890, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(89, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89, 890, 89, 445));

    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 0, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 445, 89, 445));
    PrimeraAnimacion->addFrame(sf::IntRect(89 * 2, 890, 89, 445));

    //PrimeraAnimacion->addFrame(sf::IntRect(0,0,89,445));

    animationDurante->addFrame(sf::IntRect(89 * 3, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 3, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 3, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 4, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 4, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 4, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 5, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 5, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 5, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 6, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 6, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 6, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 7, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 7, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 7, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 8, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 8, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 8, 890, 89, 445));

    animationDurante->addFrame(sf::IntRect(89 * 9, 0, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 9, 445, 89, 445));
    animationDurante->addFrame(sf::IntRect(89 * 9, 890, 89, 445));

    currentAnimation = &PrimeraAnimacion;
    InicializarAnimatedSprite(sf::seconds(0.5f / 8), true, false);
    SetOriginAnimatedSprite(40, -30);
    Collisionable::SetOriginColision(40,-30);
    
    Collisionable::SetRectangleColision(0,0,89,445);
    CreateBody();
}


hRayBasic::~hRayBasic() {

}

std::string hRayBasic::getClassName() {
    return "hRayBasic";
}

void hRayBasic::cast(sf::Vector2f posicion) {

      /*if(!buffer.loadFromFile("resources/Sounds/Pistola.wav")){
        exit(0);
    }

    sound.setBuffer(buffer);
    sound.play();
*/
    if(primeraVez){
        SoundManager *sonido = SoundManager::Instance();
        sonido->play("resources/Sounds/Rbasico.wav");
        primeraVez=false;
    }
    
    draw = true;
    float angleShot = Motor2D::Instance()->getAngleShot(posicion);

    angleShot = (angleShot * 180 / 3.14) + 270;
    SetAngle(angleshot2, angleShot);
    body->SetTransform(tmx::SfToBoxVec(posicion),0);
    body->
    SetPosition(tmx::BoxToSfVec(body->GetPosition()));
    angleshot2 = angleShot; //so it goes in a straight line
    InGame::Instance()->rs->setPosition(tmx::BoxToSfVec(body->GetPosition()));
    InGame::Instance()->rs->setRotation(((angleShot-270)));

}

void hRayBasic::rotateObject(Body body, float x1, float y1, float width1, float height1, float rotation,float PPM){
 
        float DEGTORAD = 0.0174532925199432957f;
        // Top left corner of object
        sf::Vector2f pos;
        pos((x1) / PPM, (y1 + height1) / PPM);
        // angle of rotation in radians
        float angle = DEGTORAD * (rotation);
        // half of diagonal for rectangular object
        float radius = (float) ((std::sqrt(
                (width1 * width1 + height1 * height1)) / 2f) / PPM);
        // Angle at diagonal of rectangular object
        double theta = (std::tanh(height1 / width1) * DEGTORAD);
 
                 // Finding new position if rotation was with respect to top-left corner of object.  
        // X=x+ radius*cos(theta-angle)+(h/2)cos(90+angle)
        // Y= y+radius*sin(theta-angle)-(h/2)sin(90+angle)
        pos.x = pos.x + 
        pos = pos.add((float) (radius * Math.cos(-angle + theta)),(float) (radius * Math.sin(-angle + theta))).add((float) ((height1 / PPM / 2) * Math.cos(90 * DEGTORAD+ angle)),(float) (-(height1 / PPM / 2) * Math.sin(90* DEGTORAD + angle)));
        // transform the body
        body.setTransform(pos, -angle);
 
    }
}

void hRayBasic::stopSound() {
    SoundManager *sonido = SoundManager::Instance();
    sonido->stop("resources/Sounds/Rbasico.wav");
}


void hRayBasic::DrawWithInterpolation(float interpolation, const sf::Vector2f &posPrev, const sf::Vector2f &posNew) {
    //std::cout<<"Llega"<<std::endl;
    DrawAnimation(posPrev, posNew, interpolation, &anglePrev, &angleNew);
}
void hRayBasic::update(){
    
}