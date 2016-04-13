/* 
 * File:   PhysicsState.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 8:32 AM
 */
#include "../Headers/PhysicsState.hpp"
PhysicsState::PhysicsState() : posPrev(sf::Vector2f(0.f,0.f)), posNew(sf::Vector2f(0.f,0.f)), speed(sf::Vector2f(0.f,0.f)), maxSpeed(sf::Vector2f(1000.f,1000.f))
{
}

PhysicsState::PhysicsState(const PhysicsState& orig) {
}
PhysicsState::~PhysicsState() {
}


void PhysicsState::SetPosition(float pos_x, float pos_y)
{
	posPrev = sf::Vector2f(pos_x, pos_y);
	posNew = sf::Vector2f(pos_x, pos_y);
}

void PhysicsState::SetPosition(sf::Vector2f pos)
{
	posPrev = pos;
	posNew = pos;
}


void PhysicsState::SetSpeed(float vel_x, float vel_y)
{
	speed = sf::Vector2f(vel_x, vel_y);
	//previousvelocity_ = sf::Vector2f(vel_x, vel_y);
}
void PhysicsState::SetSpeed(sf::Vector2f speed)
{
	this->speed = speed;
}


void PhysicsState::SetMaxSpeed(float speed_x, float speed_y)
{
	maxSpeed = sf::Vector2f(speed_x, speed_y);
}

void PhysicsState::SetMaxSpeed(sf::Vector2f maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

sf::Vector2f PhysicsState::GetNextPosition(sf::Time elapsedTime) const {
    return posNew + speed * elapsedTime.asSeconds();
}
void PhysicsState::Update(sf::Time elapsedTime)
{
	/*  COLISIONES  */
	
	posPrev = posNew;
        posNew += speed * elapsedTime.asSeconds();
        
}
void PhysicsState::Update(sf::Time elapsedTime, Map *mapa){
    /*  COLISIONES  */
    sf::Vector2f nextPos = GetNextPosition(elapsedTime);
    int top=(int)nextPos.y-16;
    int bot=(int)nextPos.y+16;
    int left=(int)nextPos.x-16;
    int right=(int)nextPos.x+16;
    int left_right = (left+right)/2;
    int top_bot = (top+bot)/2;
    top=top/16;
    bot=bot/16;
    left=left/16;
    right=right/16;
    left_right=left_right/16;
    top_bot=top_bot/16;
    
     sf::Vector2f speed2 = speed;
     printf("%d,%d,%d\n",mapa->_tilemap[2][top][left],mapa->_tilemap[2][top_bot][left],mapa->_tilemap[2][top][left_right]);
    if (mapa->_tilemap[2][top][left_right] != 0 && mapa->_tilemap[2][top_bot][left] != 0) {
        posPrev = posNew;
    }else if (mapa->_tilemap[2][top][left_right] != 0 && mapa->_tilemap[2][top_bot][right] != 0) {
        posPrev = posNew;
    }else if (mapa->_tilemap[2][bot][left_right] != 0 && mapa->_tilemap[2][top_bot][left] != 0) {
        posPrev = posNew;
    }else if (mapa->_tilemap[2][bot][left_right] != 0 && mapa->_tilemap[2][top_bot][right] != 0) {
        posPrev = posNew;
    }else if (mapa->_tilemap[2][top][left_right] != 0) {
        if(speed2.y<0){
               speed2.y=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
    }else if (mapa->_tilemap[2][bot][left_right] != 0) {
         if(speed2.y>0){
               speed2.y=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
    }else if (mapa->_tilemap[2][top_bot][left] != 0) {
        if(speed2.x<0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
    }else if (mapa->_tilemap[2][top_bot][right] != 0) {
                if(speed2.x>0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
    }else if (mapa->_tilemap[2][top][left] != 0 && mapa->_tilemap[2][top_bot][left] == 0 && mapa->_tilemap[2][top][left_right] == 0) {
             if(speed2.y<0){
               speed2.y=0;  
             }
             if(speed2.x<0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
        printf("entro esquina izq top");
    }else if (mapa->_tilemap[2][top][right] != 0 && mapa->_tilemap[2][top_bot][right] == 0 && mapa->_tilemap[2][top][left_right] == 0) {
             if(speed2.y<0){
               speed2.y=0;  
             }
             if(speed2.x>0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
             printf("entro esquina der top");
        posPrev = posNew;
    } else if (mapa->_tilemap[2][bot][left] != 0 && mapa->_tilemap[2][top_bot][left] == 0 && mapa->_tilemap[2][bot][left_right] == 0) {
             if(speed2.y>0){
               speed2.y=0;  
             }
             if(speed2.x<0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
             
        printf("entro esquina izq bot");
    }else if (mapa->_tilemap[2][bot][right] != 0 && mapa->_tilemap[2][top_bot][right] == 0 && mapa->_tilemap[2][bot][left_right] == 0) {
             if(speed2.y>0){
               speed2.y=0;  
             }
             if(speed2.x>0){
               speed2.x=0;  
             }
             posPrev = posNew;
             posNew += speed2 * elapsedTime.asSeconds();
             printf("entro esquina der bot");
        posPrev = posNew;
    } else{
        posPrev = posNew;
        posNew += speed * elapsedTime.asSeconds();
    }
     
}


/*
void PhysicsState::SetAcceleration(float acc_x, float acc_y)
{
	acceleration_ = sf::Vector2f(acc_x, acc_y);
}
 * */
void PhysicsState::SetAngle(float angleP, float angleN){
    anglePrev = angleP;
    angleNew = angleN;
}