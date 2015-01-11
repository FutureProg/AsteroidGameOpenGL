//
//  Utils.h
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-04.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#ifndef AsteroidGameOpenGL_Utils_h
#define AsteroidGameOpenGL_Utils_h
#define GLM_FORCE_RADIANS

#include <unordered_map>
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

class GameWindow;

class Utils {
    
public:
    static void printMatrix(glm::mat4 matrix){
        for (int y = 0; y < 3; y++) {
            printf("(");
            for (int x = 0; x < 3; x++) {
                printf("%.2f,",matrix[x][y]);
            }
            printf(")\n\t");
        }
        printf("\n");
    };
    
    static std::unordered_map<std::string,ShaderProgram> shaderPrograms;
    
    static glm::mat4 view;
    static glm::mat4 projection;
    static glm::mat4 makeMVP(glm::mat4 model){
        return projection * view * model;
    };
    
    static GLFWwindow* mainWindow;

};

#endif
