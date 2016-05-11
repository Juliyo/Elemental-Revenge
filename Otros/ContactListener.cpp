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
        }else if(claseB == "Kamehameha"){
            Player *p = static_cast<Player*> (fixtureA->GetBody()->GetUserData());
            DisparoEnemigo *d = static_cast<DisparoEnemigo*> (fixtureB->GetBody()->GetUserData());
            p->restaVida(d->getDamage());
            d->Colision();
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
            hFireBasic *f = static_cast<hFireBasic*> (fixtureB->GetBody()->GetUserData());
            f->Colision();
            m->RestarVida(f->getDamage());
        }else if(claseB == "hFireAdvanced"){
            Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
            hFireAdvanced *f = static_cast<hFireAdvanced*> (fixtureB->GetBody()->GetUserData());
            
            m->numContactos++;
            m->damageTaken = f->getDamage();
        }else if(claseB == "hRayBasic"){
            Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
            hRayBasic *f = static_cast<hRayBasic*> (fixtureB->GetBody()->GetUserData());
            m->numContactos++;
            m->damageTaken = f->getDamage();
        }else if(claseB == "hWaterBasic"){
            hWaterBasic *w = static_cast<hWaterBasic*> (fixtureB->GetBody()->GetUserData());
            b2Vec2 toTarget = fixtureA->GetBody()->GetPosition() - fixtureB->GetBody()->GetPosition();
            toTarget.Normalize();
            b2Vec2 desiredVel = 0.08f * toTarget;
            fixtureA->GetBody()->ApplyLinearImpulse(desiredVel, fixtureA->GetBody()->GetWorldCenter(), true);
            Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(w->getDamage());
        }else if(claseB == "hWaterAdvanced"){
            hWaterAdvanced *w = static_cast<hWaterAdvanced*> (fixtureB->GetBody()->GetUserData());
            Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(w->getDamage());
            
        }
    }else if(claseA == "hFireBasic"){
        if(claseB == "Melee"){
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            hFireBasic *f = static_cast<hFireBasic*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(1.f);
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
        }else if(claseB == "Kamehameha"){
            DisparoEnemigo *d = static_cast<DisparoEnemigo*> (fixtureB->GetBody()->GetUserData());
            d->Colision();
        }
    }else if(claseA == "hFireAdvanced"){
        if(claseB == "Melee"){
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            hFireAdvanced *f = static_cast<hFireAdvanced*> (fixtureA->GetBody()->GetUserData());
            m->numContactos++;
            m->damageTaken = f->getDamage();
        }else if(claseB == "Caster"){
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            hFireAdvanced *f = static_cast<hFireAdvanced*> (fixtureA->GetBody()->GetUserData());
            m->numContactos++;
            m->damageTaken = f->getDamage();
        }
    } else if (claseA == "hWaterBasic") {
        if (claseB == "Melee") {
            hWaterBasic *w = static_cast<hWaterBasic*> (fixtureA->GetBody()->GetUserData());
            b2Vec2 toTarget = fixtureB->GetBody()->GetPosition() - fixtureA->GetBody()->GetPosition();
            toTarget.Normalize();
            b2Vec2 desiredVel = 0.15f * toTarget;
            fixtureB->GetBody()->ApplyLinearImpulse(desiredVel, fixtureB->GetBody()->GetWorldCenter(), true);
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            m->RestarVida(w->getDamage());
        } else if (claseB == "Caster") {
            hWaterBasic *w = static_cast<hWaterBasic*> (fixtureA->GetBody()->GetUserData());
            b2Vec2 toTarget = fixtureB->GetBody()->GetPosition() - fixtureA->GetBody()->GetPosition();
            toTarget.Normalize();
            b2Vec2 desiredVel = 0.15f * toTarget;
            fixtureB->GetBody()->ApplyLinearImpulse(desiredVel, fixtureB->GetBody()->GetWorldCenter(), true);
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            m->RestarVida(w->getDamage());
        } else if(claseB == "Kamehameha"){
            DisparoEnemigo *d = static_cast<DisparoEnemigo*> (fixtureB->GetBody()->GetUserData());
            d->Colision();
        }
    } else if (claseA == "hWaterAdvanced") {
        hWaterBasic *w = static_cast<hWaterBasic*> (fixtureB->GetBody()->GetUserData());
        b2Vec2 toTarget = fixtureB->GetBody()->GetPosition() - fixtureA->GetBody()->GetPosition();
            toTarget.Normalize();
            b2Vec2 desiredVel = 0.09f * toTarget;
            fixtureB->GetBody()->ApplyLinearImpulse(desiredVel,fixtureB->GetBody()->GetWorldCenter(), true);
        if(claseB == "Melee"){
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            m->RestarVida(w->getDamage());
        }else if(claseB == "Caster"){
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            m->RestarVida(w->getDamage());
        }
    }else if(claseA == "Kamehameha"){
        if(claseB == "Player"){
            Player *p = static_cast<Player*> (fixtureB->GetBody()->GetUserData());
            DisparoEnemigo *d = static_cast<DisparoEnemigo*> (fixtureA->GetBody()->GetUserData());
            d->Colision();
            p->restaVida(d->getDamage());
        }else if(claseB == ""){
            DisparoEnemigo *d = static_cast<DisparoEnemigo*> (fixtureA->GetBody()->GetUserData());
            d->Colision();
        }else if(claseB == "hWaterBasic"){
            DisparoEnemigo *d = static_cast<DisparoEnemigo*> (fixtureA->GetBody()->GetUserData());
            d->Colision();
        }
    }else if(claseA == "Caster"){
        if(claseB == "hFireBasic"){
            Caster *m = static_cast<Caster*> (fixtureA->GetBody()->GetUserData());
            hFireBasic *f = static_cast<hFireBasic*> (fixtureB->GetBody()->GetUserData());
            m->RestarVida(f->getDamage());
            f->Colision();
        }else if(claseB == "hFireAdvanced"){
            Caster *m = static_cast<Caster*> (fixtureA->GetBody()->GetUserData());
            hFireAdvanced *f = static_cast<hFireAdvanced*> (fixtureB->GetBody()->GetUserData());
            
            m->numContactos++;
            m->damageTaken = f->getDamage();
        }else if(claseB == "hRayBasic"){
            Caster *m = static_cast<Caster*> (fixtureA->GetBody()->GetUserData());
            hRayBasic *f = static_cast<hRayBasic*> (fixtureB->GetBody()->GetUserData());
            m->numContactos++;
            m->damageTaken = f->getDamage();
        }else if(claseB == "hWaterBasic"){
            hWaterBasic *w = static_cast<hWaterBasic*> (fixtureB->GetBody()->GetUserData());
            b2Vec2 toTarget = fixtureA->GetBody()->GetPosition() - fixtureB->GetBody()->GetPosition();
            toTarget.Normalize();
            b2Vec2 desiredVel = 0.08f * toTarget;
            fixtureA->GetBody()->ApplyLinearImpulse(desiredVel, fixtureA->GetBody()->GetWorldCenter(), true);
            Caster *m = static_cast<Caster*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(w->getDamage());
        }else if(claseB == "hRayAdvanced"){
            hRayAdvanced *h = static_cast<hRayAdvanced*> (fixtureB->GetBody()->GetUserData());
            Caster *m = static_cast<Caster*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(h->getDamage());
        }else if(claseB == "hWaterAdvanced"){
             hWaterAdvanced *h = static_cast<hWaterAdvanced*> (fixtureB->GetBody()->GetUserData());
            Caster *m = static_cast<Caster*> (fixtureA->GetBody()->GetUserData());
            m->RestarVida(h->getDamage());
        }
    }else if(claseA == "hRayBasic"){
        if(claseB == "Melee"){
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            hRayBasic *f = static_cast<hRayBasic*> (fixtureA->GetBody()->GetUserData());
            m->numContactos++;
            m->damageTaken = f->getDamage();
        }else if(claseB == "Caster"){
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            hRayBasic *f = static_cast<hRayBasic*> (fixtureA->GetBody()->GetUserData());
            m->numContactos++;
            m->damageTaken = f->getDamage();
        }
    }else if(claseA == "hRayAdvanced"){
        
        if(claseB == "Melee"){
            hRayAdvanced *h = static_cast<hRayAdvanced*> (fixtureA->GetBody()->GetUserData());
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            m->RestarVida(h->getDamage());
            
        }else if(claseB == "Caster"){
            hRayAdvanced *h = static_cast<hRayAdvanced*> (fixtureA->GetBody()->GetUserData());
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            m->RestarVida(h->getDamage());
            
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
        }else if(claseB == "hFireAdvanced"){
            Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
            m->numContactos--;
        } else if (claseB == "hRayBasic") {
                Melee *m = static_cast<Melee*> (fixtureA->GetBody()->GetUserData());
                m->numContactos--;
        }
    }else if(claseA == "hFireAdvanced"){
        if(claseB == "Melee"){
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            m->numContactos--;
        }else if(claseB == "Caster"){
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            m->numContactos--;
        }
    }else if(claseA == "hRayBasic"){
        if(claseB == "Melee"){
            Melee *m = static_cast<Melee*> (fixtureB->GetBody()->GetUserData());
            m->numContactos--;
        }else if(claseB == "Caster"){
            Caster *m = static_cast<Caster*> (fixtureB->GetBody()->GetUserData());
            m->numContactos--;
        }
    }else if(claseA == "Caster"){
        if(claseB == "hFireAdvanced"){
            Caster *m = static_cast<Caster*> (fixtureA->GetBody()->GetUserData());
            m->numContactos--;
        } else if (claseB == "hRayBasic") {
            Caster *m = static_cast<Caster*> (fixtureA->GetBody()->GetUserData());
            m->numContactos--;
        }
    }
    
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    std::string claseA = "";
    std::string claseB = "";
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    if (fixtureA->GetBody()->GetUserData()) {
        claseA = static_cast<Entity*> (fixtureA->GetBody()->GetUserData())->getClassName();
    }
    if (fixtureB->GetBody()->GetUserData()) {
        claseB = static_cast<Entity*> (fixtureB->GetBody()->GetUserData())->getClassName();
    }
    if (claseA == "hRayBasic") {
        if (claseB == "Melee") {
            contact->SetEnabled(false);
        }
    } else if (claseA == "Melee") {
        if (claseB == "hRayBasic") {
            contact->SetEnabled(false);
        } else if (claseB == "hFireAdvanced") {
            contact->SetEnabled(false);
        }else if(claseB == "hRayAdvanced"){
            contact->SetEnabled(false);
        }
    } else if (claseA == "hFireAdvanced") {
        if (claseB == "Melee") {
            contact->SetEnabled(false);
        } else if (claseB == "Caster") {
            contact->SetEnabled(false);
        }
    }else if(claseA == "Caster"){
        if(claseB == "hFireAdvanced"){
            contact->SetEnabled(false);
        }else if(claseB == "hFireAdvanced"){
            contact->SetEnabled(false);
        }else if(claseB == "hRayAdvanced"){
            contact->SetEnabled(false);
        }
    }else if(claseA == "hRayAdvanced"){
        if(claseB == "Melee"){
            contact->SetEnabled(false);
        }else if(claseB == "Caster"){
            contact->SetEnabled(false);
        }
    }
}

