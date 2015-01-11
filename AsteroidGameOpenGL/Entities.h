//
//  Asteroid.h
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#ifndef __AsteroidGameOpenGL__Asteroid__
#define __AsteroidGameOpenGL__Asteroid__

#include "Entity.h"
//#define DEBUG_COLLIDERS

class Rocket : public Entity {
    
public:
    Rocket(glm::vec3 pos);
    ~Rocket();
    
    void init();
    void update();
    void render();
    void onCollision(Collider &other);
    
private:
    void floatRotate();
    void floatMove();
    float speed;
    float width,height;
    float rdir; //0 = none, -1 = left, 1 = right
    float mdir; //0 = none, -1 = back, 1 = forward
    float rotation;
};

class Laser : public Entity{
public:
    Laser(glm::vec3 pos,glm::mat4 nmodel);
    ~Laser();
    
    void init();
    void update();
    void render();
    void onCollision(Collider &other);
};


class Asteroid : public Entity {
public:
    Asteroid(glm::vec3 pos, float ndir = 0);
    ~Asteroid();
    
private:
    float speed;
    float dir;
    float accumX, accumY;
    
public:
    void init();
    void update();
    void render();
    void onCollision(Collider &other);
    void setDirection(float nDir);
};



#endif /* defined(__AsteroidGameOpenGL__Asteroid__) */
