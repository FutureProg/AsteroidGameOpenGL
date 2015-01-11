//
//  GameWindow.h
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#ifndef __AsteroidGameOpenGL__GameWindow__
#define __AsteroidGameOpenGL__GameWindow__
#define GLFW_INCLUDE_GLCOREARB
#define GLM_FORCE_RADIANS

#include <stdio.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "ShaderProgram.h"
#include "Utils.h"

#include "Entities.h"

class GameWindow {
public:
    static GameWindow* mainWindow;
    
private:
    GLFWwindow* window;
    int width, height;
    char* title;
    
    glm::mat4 view;
    glm::mat4 projection;
    
    ShaderProgram* program;
    Rocket* rocket;
    Asteroid* asteroid;
    
    std::vector<Entity*> objects;
    
    glm::vec3 spawnPos;
    bool canFire;
    
public:
    GameWindow(char* _title, int _width = 500,int _height = 400);
    ~GameWindow();
    
    void init();
    int execute();
    void instantiate(Entity &ent);
    void remove(Entity &ent);
    void remove(std::string entID);
    Entity* findByID(std::string entID);
    void collisionCheck();

public:
    ShaderProgram* shaderProgram() const {return program;};
    glm::mat4 makeMVP(glm::mat4 model) const;
    
    void setTitle(char*);
    char* getTitle() const {return title;};
    
    bool running() const {return glfwWindowShouldClose(window);};
    
    GLFWwindow* gameWindow() const { return window;};
    
private:
    void update();
    void render();
    void clean();
    
    void asteroidGen();
};

#endif /* defined(__AsteroidGameOpenGL__GameWindow__) */
