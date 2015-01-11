//
//  Entity.h
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//

#ifndef __AsteroidGameOpenGL__Entity__
#define __AsteroidGameOpenGL__Entity__
#define  GLM_FORCE_RADIANS
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <OpenGL/gl3.h>

#include "Utils.h"


class Entity {
public:
    
    enum ColliderType{
        COLLIDER_SQUARE,
        COLLIDER_CIRCLE
    };
    
    struct Collider{
        
        ColliderType type;
        
        float x;
        float y;
        float width;
        float height;
        
        float radius;
        glm::vec3 centre;
        
        std::string parentID;
        
        Collider(float nx = 0, float ny = 0,float nw = 0, float nh = 0):x(nx),y(ny),width(nw),height(nh){
            type = ColliderType::COLLIDER_SQUARE;
        };
        void makeCircle(float nRadius,glm::vec3 nCentre){
            radius = nRadius;
            centre = nCentre;
            type = ColliderType::COLLIDER_CIRCLE;
        };
        std::vector<glm::vec3> createVert(){
            std::vector<glm::vec3> list;
            list.push_back(glm::vec3(x,y,0));
            list.push_back(glm::vec3(x+(width),y,0));
            list.push_back(glm::vec3(x+width,y+height,0));
            list.push_back(glm::vec3(x,y+height,0));
            return list;
        };
    };
protected:
    GLuint* VBO;
    GLuint* VAO;
    
    glm::mat4 model;
    std::vector<Collider> colliders;
    
    std::string objectID;
    
    bool trash;
    
protected:
    ShaderProgram shaderprogram(){
        return Utils::shaderPrograms["MAIN"];
    };
    
    glm::mat4 makeMVP(glm::mat4 _model){
        return Utils::makeMVP(_model);
    };
    
public:
    Entity(glm::vec3 pos){
        model = glm::translate(model, pos);
        trash = false;
    };
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void onCollision(Collider &other) = 0;
    
    glm::mat4 objectModel() const{return model;};
    
    void addCollider(Collider &col){col.parentID = objectID;colliders.push_back(col);};
    Collider getCollider(){return colliders[0];};
    
    void setID(std::string newID){objectID = newID;};
    std::string getID(){return objectID;};
    
    void destroy(){trash = true;};
    bool shouldDestroy(){return trash;};
    
    
};

#endif /* defined(__AsteroidGameOpenGL__Entity__) */
