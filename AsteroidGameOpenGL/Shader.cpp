//
//  Shader.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#include "Shader.h"
#include "ShaderUtils.h"

Shader::Shader(std::string path, GLenum shaderType){
    _shaderID = ShaderUtils::createShaderFromFile(path, shaderType);
    source = path;
}

Shader::~Shader(){
    glDeleteShader(_shaderID);
}

GLuint Shader::getShaderID(){
    return _shaderID;
}
