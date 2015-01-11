//
//  Asteroid.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-05.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#include "Entities.h"
#include <math.h>

Asteroid::Asteroid(glm::vec3 pos,float nDir):Entity(pos){    
    speed = .5f;
    dir = nDir;
    accumX = 0.f;
    accumY = 0.f;
}

void Asteroid::init(){
#ifdef DEBUG_COLLIDERS
    if (colliders.size() > 0) {
        VBO = new GLuint[2];
        glGenBuffers(2, VBO);
    }
#else
    VBO = new GLuint[1];
    glGenBuffers(1, VBO);
#endif
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    static const GLfloat vertices[] = {
        0.0, 0.0,
        0.0, 100.f,
        100.f,100.f,
        100.f,0.f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    
#ifdef DEBUG_COLLIDERS
    if (colliders.size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        std::vector<glm::vec3> colCoords = colliders[0].createVert();
        static const GLfloat colvertices[] = {
            (colCoords[0])[0],(colCoords[0])[1],
            (colCoords[1])[0],(colCoords[1])[1],
            (colCoords[2])[0],(colCoords[2])[1],
            (colCoords[3])[0],(colCoords[3])[1],
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(colvertices), &colvertices[0], GL_STATIC_DRAW);
    }
#endif
    
#ifdef DEBUG_COLLIDERS
    if (colliders.size() > 0) {
        VAO = new GLuint[2];
        glGenVertexArrays(2, VAO);
    }
#else
    VAO = new GLuint[1];
    glGenVertexArrays(1, VAO);
#endif
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBindVertexArray(VAO[0]);
    GLint posLoc = shaderprogram().getAttribLoc("position");
    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0 * sizeof(GL_FLOAT)));
#ifdef DEBUG_COLLIDERS
    if (colliders.size() > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBindVertexArray(VAO[1]);
        GLint posLoc = shaderprogram().getAttribLoc("position");
        glEnableVertexAttribArray(posLoc);
        glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0*sizeof(GL_FLOAT)));
    }
#endif
    
    glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void Asteroid::update(){
    float x = glm::cos(glm::radians(dir))* speed * 2.f;
    float y = glm::sin(glm::radians(dir))* speed * 2.f;
    
    model = glm::translate(model, glm::vec3(x,y,.0f));
    
    /*model = glm::translate(model, glm::vec3(50.f,50.f,.0f));
    model = glm::rotate(model, -0.005f, glm::vec3(0,0,1));
    model = glm::translate(model, glm::vec3(-50.f, -50.f, .0f));*/
}

void Asteroid::onCollision(Collider &other){
    if(other.parentID != "asteroid")
        destroy();
}

void Asteroid::setDirection(float nDir){
    dir = nDir;
}

void Asteroid::render(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBindVertexArray(VAO[0]);
    
    glm::mat4 mvp = makeMVP(model);
    GLint pos = shaderprogram().getUniformLoc("MVP");
    glUniformMatrix4fv(pos, 1, false,glm::value_ptr(mvp));
    pos = shaderprogram().getUniformLoc("colour");
    glUniform3f(pos, 0.7f, 0.3f, 0.0f);
    pos = shaderprogram().getUniformLoc("ZValue");
    glUniform1f(pos, 1.f);
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
#ifdef DEBUG_COLLIDERS
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBindVertexArray(VAO[1]);
    pos = shaderprogram().getUniformLoc("colour");
    glUniform3f(pos, 0.0,1.0, 0.0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glFlush();
#endif
    
    pos = shaderprogram().getUniformLoc("ZValue");
    glUniform1f(pos, 0.f);
    glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

Asteroid::~Asteroid(){
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
}