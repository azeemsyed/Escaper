#ifndef __GUY_AGENT__H
#define __GUY_AGENT__H 

#include "enviro.h"
#include <math.h>

using namespace enviro;

double min(double a, double b) {
    if ( a < b ) { 
        return a;
    } else {
        return b;
    }
}

class GuyController : public Process, public AgentInterface {

    public:
    GuyController() : Process(), AgentInterface(), LEFT(false), RIGHT(false), JUMP(false), firing(false)  {}

    double height() {
        return min(sensor_value(0), sensor_value(1));
    }

    double airborne() { 
        return height() > H_MIN;
    }

    void init() {
        prevent_rotation();
        watch("keydown", [&](Event& e) {
            std::string k = e.value()["key"];
            if ( k == " " && ! airborne() ) {
                JUMP = true;
            } else if ( k == "a" ) {
                LEFT = true;
            } else if ( k == "d" ) {
                RIGHT = true;
            } else  if ( k == "s" && !firing ) {
                  Agent& bullet = add_agent("Bullet", 
                    x() + 17*cos(angle()), 
                    y() + 17*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(50,0);
                  firing = true;
                  }    
        });
        watch("keyup", [&](Event& e) {
            std::string k = e.value()["key"];
            if ( k == "a" ) {
                LEFT = false;
            } else if ( k == "d" ) {
                RIGHT = false;
            }else if ( k == "s" ) {
                firing = false;
            }
        });     
        notice_collisions_with("Ghost", [&](Event &e) {
            teleport(280,-250,0);
        });               
    }
    void start() {}

    void update() {
        double fx;
        double fy = JUMP ? JUMP_F : 0;
        if ( !airborne() ) {
            if ( RIGHT ) {
                vx = VEL_X;
            } if ( LEFT ) {
                vx = -VEL_X;
            } else if ( !RIGHT && !LEFT ) {
                vx = 0;
            }
            fx = -K_X*(velocity().x-vx);
        } else {
            if ( RIGHT ) {
                vx = 0.2*VEL_X;
            } if ( LEFT ) {
                vx = -0.2*VEL_X;
            }            
            fx = 0;
            fx = -K_X*(velocity().x-vx);
        }
        omni_apply_force(fx,G+fy);
        JUMP = false;
    }

    void stop() {}

    bool LEFT, RIGHT, JUMP, firing;
    double vx;

    const double VEL_X = 20;
    const double JUMP_F = -2300;
    const double K_X = 15;
    const double G = 500;
    const double H_MIN = 1.0;

    const json BULLET_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "5px"},
                   {"strokeOpacity", "0.25"}
               };

};

class Guy : public Agent {
    public:
    Guy(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GuyController c;
};

DECLARE_INTERFACE(Guy)

#endif