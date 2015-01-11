//
//  Asteroid.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#include "Entities.h"


Rocket::Rocket(glm::vec3 pos):Entity(pos){
    speed = .5f;
    rdir = 0;
    rotation = 0.f;
}

void Rocket::init(){
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
        50.0, 100.0,
        100.0,0.0
    };
    width = 100.f;
    height = 100.f;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    
#ifdef DEBUG_COLLIDERS
    if (colliders.size() > 0 && colliders[0].type == ColliderType::COLLIDER_SQUARE) {
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
    else if(colliders.size() > 0 && colliders[0].type == ColliderType::COLLIDER_CIRCLE){
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        std::vector<glm::vec3> colCoords = colliders[0].createVert();
        int steps = 30;
        GLfloat colvertices[steps * 4];
        float t = 0;
        int pos = 0;
        Collider col = colliders[0];
        for (int i = 0; i < steps; i++) {
            float x = col.radius * cos(t)+ col.centre[0];
            float y = col.radius * sin(t) + col.centre[1];
            
            colvertices[pos++] = col.centre[0];
            colvertices[pos++] = col.centre[1];
            colvertices[pos++] = x;
            colvertices[pos++] = y;
            t += (360 - 0)/steps;
        }
        printf("%.2lu",sizeof(colvertices)/sizeof(GLfloat));
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

void Rocket::update(){
    if(glfwGetKey(Utils::mainWindow, GLFW_KEY_A) == GLFW_PRESS){
        model = glm::translate(model, glm::vec3(width/2.f,height/2.f,0.f));
        model = glm::rotate(model, speed*0.05f, glm::vec3(0.f,0.f,1.f));
        model = glm::translate(model, glm::vec3(-width/2.f,-height/2.f,0.f));
        rdir = 1;
        mdir = 0;
    }
    else if(glfwGetKey(Utils::mainWindow, GLFW_KEY_D) == GLFW_PRESS){
        model = glm::translate(model, glm::vec3(width/2.f,height/2.f,0.f));
        model = glm::rotate(model, -speed*0.05f, glm::vec3(0.f,0.f,1.0f));
        model = glm::translate(model, glm::vec3(-width/2.f,-height/2.f,0.f));
        rdir = -1;
        mdir = 0;
    }
    if(glfwGetKey(Utils::mainWindow, GLFW_KEY_DOWN) == GLFW_PRESS){
        model = glm::translate(model, glm::vec3(0.f,-speed,0.f));
        rdir = 0;
        mdir = 1;
    }
    else if(glfwGetKey(Utils::mainWindow, GLFW_KEY_UP) == GLFW_PRESS){
        model = glm::translate(model, glm::vec3(0.f,speed,0.f));
        rdir = 0;
        mdir = -1;
    }        
    floatRotate();
    floatMove();
}

bool between(double val,double min, double max){
    return (val >= min && val <= max);
}

void Rocket::floatRotate(){
    if (rdir == 0) {
        return;
    }
    model = glm::translate(model, glm::vec3(width/2.f,height/2.f,0.f));
    model = glm::rotate(model, speed*0.05f*rdir*0.4f, glm::vec3(0.f,0.f,1.0f));
    model = glm::translate(model, glm::vec3(-width/2.f,-height/2.f,0.f));
    if (rdir > 0.01f) {
        rdir -= 0.01f;
    }
    else if(rdir < -0.01f){
        rdir += 0.01f;
    }
    rotation += speed * 0.05f * rdir * 0.4f;
}

void Rocket::floatMove(){
    if (mdir == 0) {
        return;
    }
    model = glm::translate(model, glm::vec3(0.f,-speed*mdir,0.f));
    if (mdir > 0.01f) {
        mdir -= 0.01f;
    }
    else if(mdir < -0.01f){
        mdir += 0.01f;
    }
}

void Rocket::onCollision(Collider &other){
    destroy();
}

void Rocket::render(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBindVertexArray(VAO[0]);
    
    glm::mat4 mvp = makeMVP(model);
    GLint pos = shaderprogram().getUniformLoc("MVP");
    glUniformMatrix4fv(pos, 1, false,glm::value_ptr(mvp));
    pos = shaderprogram().getUniformLoc("colour");
    glUniform3f(pos, 1.0,0.0, 0.0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    glFlush();
    
#ifdef DEBUG_COLLIDERS
    if (colliders.size() > 0) {
        if (colliders[0].type == ColliderType::COLLIDER_SQUARE) {
            glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
            glBindVertexArray(VAO[1]);
            pos = shaderprogram().getUniformLoc("colour");
            glUniform3f(pos, 0.0,1.0, 0.0);
            glDrawArrays(GL_LINES, 0, 4);
            glFlush();

        }
        else{
            glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
            glBindVertexArray(VAO[1]);
            pos = shaderprogram().getUniformLoc("colour");
            glUniform3f(pos, 0.0,1.0, 0.0);
            glDrawArrays(GL_LINES, 0, 120);
            glFlush();

        }
    }
#endif
    
    glBindVertexArray(NULL);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

Rocket::~Rocket(){
    glDeleteBuffers(1, VBO);
    glDeleteVertexArrays(1, VAO);
}