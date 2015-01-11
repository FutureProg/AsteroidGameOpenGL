//
//  ShaderUtils.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#include "ShaderUtils.h"

GLuint ShaderUtils::createShaderFromFile(std::string path, GLenum shaderType){
    GLuint shaderID = glCreateShader(shaderType);
    
    std::ifstream fin;
    fin.open(path);
    if(!fin.is_open()){
        std::cout<<"File not found at path: " << path << std::endl;
        return 0;
    }
    
    std::string source((std::istreambuf_iterator<GLchar>(fin)),std::istreambuf_iterator<GLchar>());
    fin.close();
    
    const GLchar* source_c = (GLchar*)source.c_str();
    glShaderSource(shaderID, 1, &source_c, NULL);
    
    GLint compileStatus;
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus != GL_TRUE){
        std::cout << "Shader Failed to Compile: " << path << std::endl;
        GLint logLength;
        GLchar* log = new GLchar[logLength-1];
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        glGetShaderInfoLog(shaderID, logLength + 1, NULL, log);
        std::cout << log << std::endl;
        delete log;
        return 0;
    }
    
    return shaderID;
}
