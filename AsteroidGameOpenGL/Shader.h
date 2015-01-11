//
//  Shader.h
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#ifndef __AsteroidGameOpenGL__Shader__
#define __AsteroidGameOpenGL__Shader__

#include <stdio.h>

#include <iostream>
#include <GLFW/glfw3.h>

class Shader {
private:
    GLuint _shaderID;
    
public:
    Shader(std::string pathToFile,GLenum type);
    virtual ~Shader();
    
    GLuint getShaderID();
    
    std::string source;
};

#endif /* defined(__AsteroidGameOpenGL__Shader__) */
