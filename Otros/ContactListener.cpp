    /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContactListener.cpp
 * Author: tonir
 * 
 * Created on 29 de abril de 2016, 14:42
 */

#include "ContactListener.hpp"
#include "../Otros/Dummy.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Melee.hpp"
#include "../Entities/Caster.hpp"

ContactListener::ContactListener() {
}

ContactListener::ContactListener(const ContactListener& orig) {
}

ContactListener::~ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {
    std::string claseA = "";
    std::string claseB = "";
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if(fixtureA->GetBody()->GetUserData()){
        claseA = static_cast<Entity*> (fixtureA->GetBody()->GetUserData())->getClassName();
    }
    if(fixtureB->GetBody()->GetUserData()){
        claseB = static_cast<Entity*> (fixtureB->GetBody()->GetUserData())->getClassName();
    }
    
    if(claseA == "Player"){
        if(claseB == "Melee"){
            Player *p = static_cast<Player*> (fixtureA->GetBody()->GetUserData());
            if(p->invulnerable.getTiempo() > 0.5f){
                b2Vec2 toTarget = fixtureA->GetBody()->GetPosition() - fixtureB->GetBody()->GetPosition();
                toTarget.Normalize();
                b2Vec2 desiredVel = 3.f*toTarget;
                b2Vec2 currentVel = fixtureA->GetBody()->GetLinearVelocity();
                b2Vec2 thrust = desiredVel - currentVel;
                fixtureA->GetBody()->ApplyForceToCenter(2.5f*thrust,true);
            }
            p->numContactos++;
            
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            p->damageTaken = m->GetDamage();
            
            
        }
    }else if(claseA == "Melee"){
        if(claseB == "Player"){
           Player *p = static_cast<Player*> (fixtureB->GetBody()->GetUserData());
           
           if(p->invulnerable.getTiempo() > 0.5f){
                b2Vec2 toTarget = fixtureB->GetBody()->GetPosition() - fixtureA->GetBody()->GetPosition();
                toTarget.Normalize();
                b2Vec2 desiredVel = 3.f*toTarget;
                b2Vec2 currentVel = fixtureB->GetBody()->GetLinearVelocity();
                b2Vec2 thrust = desiredVel - currentVel;
                fixtureB->GetBody()->ApplyForceToCenter(2.5f*thrust,true);
            }
           p->numContactos++;
           
           Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
           p->damageTaken = m->GetDamage();
        }else if(claseB == "hFireBasic"){
            Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(1);
            
            hFireBasic *f = static_cast<hFireBasic*> (fixtureB->GetBody()->GetUserData());
            f->Colision();
        }else if(claseB == "hFireAdvanced"){
            Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
            hFireAdvanced *f = static_cast<hFireAdvanced*> (fixtureB->GetBody()->GetUserData());

            /*b2Vec2 toTarget = fixtureA->GetBody()->GetPosition() - fixtureB->GetBody()->GetPosition();
            toTarget.Normalize();
            b2Vec2 desiredVel = 2.f * toTarget;
            fixtureA->GetBody()->ApplyLinearImpulse(desiredVel,fixtureA->GetBody()->GetWorldCenter(), true);*/
                
            m->RestarVida(f->getDamage());
        }
    }else if(claseA == "hFireBasic"){
        if(claseB == "Melee"){
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            hFireBasic *f = static_cast<hFireBasic*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(f->getDamage());
 
            f->Colision();
        }else if(claseB == ""){
            hFireBasic *f = static_cast<hFireBasic*> (fixtureA->GetBody()->GetUserData());
            f->Colision();
        }else if(claseB == "Caster"){
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            hFireBasic *f = static_cast<hFireBasic*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(f->getDamage());
            
            f->Colision();
        }
    }else if(claseA == ""){
        if(claseB == "hFireBasic"){
            hFireBasic *f = static_cast<hFireBasic*> (fixtureB->GetBody()->GetUserData());
            f->Colision();
        }
    }else if(claseA == "hFireAdvanced"){
        if(claseB == "Melee"){
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            hFireAdvanced *f = static_cast<hFireAdvanced*> (fixtureA->GetBody()->GetUserData());

            /*b2Vec2 toTarget = fixtureB->GetBody()->GetPosition() - fixtureA->GetBody()->GetPosition();
            toTarget.Normalize();
            b2Vec2 desiredVel = 2.f * toTarget;
            fixtureB->GetBody()->ApplyLinearImpulse(desiredVel,fixtureB->GetBody()->GetWorldCenter(), true);*/
                
            m->RestarVida(f->getDamage());
        }else if(claseB == "Caster"){
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            hFireAdvanced *f = static_cast<hFireAdvanced*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(f->getDamage());
        }
    }
}
void ContactListener::EndContact(b2Contact* contact) { 
    std::string claseA = "";
    std::string claseB = "";
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if(fixtureA->GetBody()->GetUserData()){
        claseA = static_cast<Entity*> (fixtureA->GetBody()->GetUserData())->getClassName();
    }
    if(fixtureB->GetBody()->GetUserData()){
        claseB = static_cast<Entity*> (fixtureB->GetBody()->GetUserData())->getClassName();
    }
    if(claseA == "Player"){
        if(claseB == "Melee"){
            Player *p = static_cast<Player*> (fixtureA->GetBody()->GetUserData());
            p->numContactos--;
        }
    }else if(claseA == "Melee"){
        if(claseB == "Player"){
            Player *p = static_cast<Player*> (fixtureB->GetBody()->GetUserData());
            p->numContactos--;
        }
    }
    
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    std::string claseA = "";
    std::string claseB = "";
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if(fixtureA->GetBody()->GetUserData()){
        claseA = static_cast<Entity*> (fixtureA->GetBody()->GetUserData())->getClassName();
    }
    if(fixtureB->GetBody()->GetUserData()){
        claseB = static_cast<Entity*> (fixtureB->GetBody()->GetUserData())->getClassName();
    }
    if(claseA == "hFireBasic"){
        if(claseB == "Melee"){
            //contact->SetEnabled(false);
        }else if(claseB == "Player"){
            ///contact->SetEnabled(false);
        }
    }
}



/*bool ContactListener::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) {
    //std::cout<<static_cast<Entity*> (fixtureA->GetBody()->GetUserData())->getClassName()<<std::endl;
    std::string claseA = "";
    std::string claseB = "";
    if(fixtureA->GetBody()->GetUserData()){
        claseA = static_cast<Entity*> (fixtureA->GetBody()->GetUserData())->getClassName();
    }
    if(fixtureB->GetBody()->GetUserData()){
        claseB = static_cast<Entity*> (fixtureB->GetBody()->GetUserData())->getClassName();
    }

    if(claseA == "Player"){
        if(claseB == ""){
            return true;
        }else if(claseB == "Melee"){
            return true;
        }else if(claseB == "hFireBasic"){
            return false;
        }
    }
    if(claseA == "hFireBasic"){
        if(claseB == "Player"){
            return false;
        }else if(claseB == "Melee"){
            return true;
        }else if(claseB == "hFireBasic"){
            return false;
        }
    }
    if(claseA == "Melee"){
        if(claseB == "Player"){
           //Player *p = static_cast<Player*> (fixtureA->GetBody()->GetUserData());
           //p->restaVida(1);
           return true;
        }else if(claseB == "hFireBasic"){
            return true;
        }
    }

    
    return true;
}*/
