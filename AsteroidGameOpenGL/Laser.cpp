//
//  Laser.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-20.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#include "Entities.h"
#include <math.h>

Laser::Laser(glm::vec3 pos, glm::mat4 nmodel):Entity(pos){
    model = nmodel;
    model = glm::translate(model, glm::vec3(0.f,80.f,0.f));
}

void Laser::init(){
    VBO = new GLuint[1];
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    GLfloat vertices[] = {
        0.0f, 0.0f,
        0.0f, 50.f,
        50.f, 50.f,
        50.f, 0.f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    VAO = new GLuint[1];
    glGenVertexArrays(1, VAO);
    glBindVertexArray(VAO[0]);
    GLint pos = shaderprogram().getAttribLoc("position");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0 * sizeof(GL_FLOAT)));
}

void Laser::update(){
    model = glm::translate(model, glm::vec3(0.f, 10.f,0.f));
}

void Laser::onCollision(Entity::Collider &other){
    destroy();
}

void Laser::render(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBindVertexArray(VAO[0]);
    
    glm::mat4 mvp = makeMVP(model);
    GLint pos = shaderprogram().getUniformLoc("MVP");
    glUniformMatrix4fv(pos, 1, false,glm::value_ptr(mvp));
    pos = shaderprogram().getUniformLoc("colour");
    glUniform3f(pos, 1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindVertexArray(NULL);
}

Laser::~Laser(){}