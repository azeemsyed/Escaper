#ifndef __BLOCK_AGENT__H
#define __BLOCK_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BlockController : public Process, public AgentInterface {

    public:
    BlockController() : Process(), AgentInterface(), hit(false) {}

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
    void update() {
        if (hit){
            pop();
        }
    }
    void stop() {}
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