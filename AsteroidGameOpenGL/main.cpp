//
//  main.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#include <stdio.h>
#include "GameWindow.h"
#include "Entities.h"


int main(int argc, const char * argv[]) {
    GLint glfwstatus = glfwInit();
    if (glfwstatus != GL_TRUE) {
        glfwTerminate();
        throw "Unable to initialize GLFW!";
    }
    char name[] = "Asteroid Game";
    GameWindow game(name,500,500);
    
    Rocket rocket(glm::vec3(0.f,0.f,0.f));
    rocket.setID("rocket");
    Entity::Collider col = Entity::Collider(20,0,60,50);
    col.makeCircle(50, glm::vec3(50.f,50.f,0.f));
    rocket.addCollider(col);
    
    game.init();
    game.instantiate(rocket); 
    
    return game.execute();
}
