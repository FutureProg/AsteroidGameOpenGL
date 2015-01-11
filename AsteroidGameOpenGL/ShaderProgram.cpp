//
//  ShaderProgram.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(){
    _programID = glCreateProgram();
    
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(_programID);
}

void ShaderProgram::attachShader(Shader shader){
    glAttachShader(_programID, shader.getShaderID());
}

/*void ShaderProgram::bindFragDataLocation(GLint colourAttachment, std::string name){
 glBindFragDataLocation(_programID, colourAttachment, name.c_str());
 }*/

void ShaderProgram::link(){
    glLinkProgram(_programID);
    GLint linkStatus;
    glGetProgramiv(_programID, GL_LINK_STATUS, &linkStatus);
    if(linkStatus != GL_TRUE){
        std::cout << "Program Link failed:" << std::endl;
        GLint logLength;
        GLchar* log = new GLchar[logLength-1];
        glGetShaderiv(_programID, GL_INFO_LOG_LENGTH, &logLength);
        glGetShaderInfoLog(_programID, logLength + 1, NULL, log);
        std::cout << log << std::endl;
        delete log;
        throw "Program Link Failed!";
    }
}

void ShaderProgram::use(){
    glUseProgram(_programID);
}

GLuint ShaderProgram::getProgramID(){
    return _programID;
}

GLint ShaderProgram::getAttribLoc(std::string name){
    return glGetAttribLocation(_programID, name.c_str());
}

GLint ShaderProgram::getUniformLoc(std::string name){
    return glGetUniformLocation(_programID, name.c_str());
}

