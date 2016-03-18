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


void PhysicsState::Update(sf::Time elapsedTime)
{

	/*  COLISIONES  */
	
	posPrev = posNew;
        posNew += speed * elapsedTime.asSeconds();
        
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