#ifndef __BUMPER_AGENT__H
#define __BUMPER_AGENT__H 

#include "enviro.h"

using namespace enviro;

/*
This is a class to define the Bumper behavior to allow the guards
to go across walls
*/

class BumperController : public Process, public AgentInterface {

    public:
    BumperController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class Bumper : public Agent {
    public:
    Bumper(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BumperController c;
};

DECLARE_INTERFACE(Bumper)

#endif