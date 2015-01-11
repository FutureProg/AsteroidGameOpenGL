//
//  ShaderProgram.h
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#ifndef __AsteroidGameOpenGL__ShaderProgram__
#define __AsteroidGameOpenGL__ShaderProgram__

#include <stdio.h>

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Shader.h"


class ShaderProgram {
private:
    GLuint _programID;
public:
    ShaderProgram();
    virtual ~ShaderProgram();
    
    void attachShader(Shader shader);
    //void bindFragDataLocation(GLint colourAttachment, std::string name);
    void link();
    void use();
    
    GLint getAttribLoc(std::string name);
    GLint getUniformLoc(std::string name);
    GLuint getProgramID();
};


#endif /* defined(__AsteroidGameOpenGL__ShaderProgram__) */
