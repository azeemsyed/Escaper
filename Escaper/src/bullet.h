#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

/*
This is a class to define the Bullet behavior to allow the guards
to go across walls
*/


class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface(), counter(0) {}

    void init() {
// this defines a collisions between a block

        notice_collisions_with("Block", [&](Event &e) {
            remove_agent(id());
        });

         
    }
    void start() {}
    void update() {
        if ( counter++ > 20 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;

};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif