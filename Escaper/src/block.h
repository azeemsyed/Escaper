#ifndef __BLOCK_AGENT__H
#define __BLOCK_AGENT__H 

#include "enviro.h"

using namespace enviro;

/*
This is a class to define the Block behavior to allow the guards
to go across walls
*/

class BlockController : public Process, public AgentInterface {

    public:
    BlockController() : Process(), AgentInterface(), hit(false) {}

//  This defines the behavior of if a block gets hit by a bullet 
    void init() {
        notice_collisions_with("Bullet", [&](Event &e) {
            Agent& bullet = find_agent(e.value()["id"]);
            vz = bullet.velocity().x;
            vy = bullet.velocity().y;
            ignore_collisions_with("Bullet");
            hit = true;
        }); 
    }
    void start() {}
   
// This Blockcontroller to remove the block that has been hit
    void update() {
        if (hit){
            pop();
        }
    }
    void stop() {}
    
// this pops out removes the bloc
    void pop(){
        remove_agent(id());
    }

    double vy, vz;
    bool hit; 

};

class Block : public Agent {
    public:
    Block(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BlockController c;
};

DECLARE_INTERFACE(Block)

#endif