//
//  ShaderUtils.h
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#ifndef __AsteroidGameOpenGL__ShaderUtils__
#define __AsteroidGameOpenGL__ShaderUtils__

#include <iostream>
#include <GLFW/glfw3.h>
#include <fstream>
#include <streambuf>
#include <string.h>


class ShaderUtils {
    
public:
    static GLuint createShaderFromFile(std::string path, GLenum shaderType);
};

#endif /* defined(__AsteroidGameOpenGL__ShaderUtils__) */
