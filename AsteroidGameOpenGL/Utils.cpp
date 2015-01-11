//
//  Utils.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-05.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#include <stdio.h>
#include "Utils.h"


std::unordered_map<std::string,ShaderProgram> Utils::shaderPrograms = std::unordered_map<std::string, ShaderProgram>();
glm::mat4 Utils::view = glm::mat4(1.0f);
glm::mat4 Utils::projection = glm::mat4(1.0f);
GLFWwindow* Utils::mainWindow = glfwCreateWindow(0, 0, "asdf", 0, 0);