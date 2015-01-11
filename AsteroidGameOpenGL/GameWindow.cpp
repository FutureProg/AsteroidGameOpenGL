//
//  GameWindow.cpp
//  AsteroidGameOpenGL
//
//  Created by Nickolas Morrison on 2014-11-02.
//  Copyright (c) 2014 Nickolas Morrison. All rights reserved.
//
#include "GameWindow.h"
#include "Entities.h"

GameWindow::GameWindow(char* _title, int _width,int _height):width(_width),height(_height),title(_title){
    canFire = false;
}

void GameWindow::init(){
     
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);
    Utils::mainWindow = window;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH);
    
    projection = glm::ortho(-float(width)*2, float(width)*2.f,-float(height)*2,float(height)*2.f,-10.0f,100.0f);
    //projection = glm::perspective(60.0f, aspect, -0.01f, 100000.f);
    view = glm::mat4();
    //view = glm::lookAt(glm::vec3(0.0f,0.f,5.f), glm::vec3(0.f,0.f,0.f), glm::vec3(0.f,1.f,0.f));
    
    
    program = new ShaderProgram();
    Shader vShader("plainshader.vsh",GL_VERTEX_SHADER);
    Shader fShader("plainshader.fsh",GL_FRAGMENT_SHADER);
    program->attachShader(fShader);
    program->attachShader(vShader);
    program->link();
    program->use();
    Utils::shaderPrograms["MAIN"] = *program;
}

int GameWindow::execute(){
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        update();
        render();
    }
    
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i] != nullptr){
            objects.erase(objects.begin()+i);
            i--;
        }
    }
    delete program;
    glfwTerminate();
    return 0;
}

float x = 0.0f;
float y = 0.0f;
void GameWindow::update(){
    static float spawnAngle = 0.0f;
    static const float radius = sqrt(pow(width*2,2) + pow(height*2,2));
    glfwGetWindowSize(window, &width, &height);
    width*=2;height*=2;
    
    Utils::view = view;
    Utils::projection = projection;
    
    if (glfwGetKey(Utils::mainWindow, GLFW_KEY_SPACE) == GLFW_PRESS
        && findByID("rocket") != nullptr &&
        canFire) {
        glm::mat4 model = findByID("rocket")->objectModel();
        Laser* laser = new Laser(glm::vec3(0.f,0.f,0.f),model);
        Entity::Collider col(0,0,60,60);
        laser->addCollider(col);
        laser->setID("laser");
        instantiate(*laser);
        canFire = false;
    }
    if (glfwGetKey(Utils::mainWindow, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        if (!canFire)
            canFire = true;
    }
    
    if(spawnAngle >= 360.f) spawnAngle = 0.f;
    spawnPos[0] = cos(glm::radians(spawnAngle)) * radius;
    spawnPos[1] = sin(glm::radians(spawnAngle)) * radius;
    spawnPos[2] = 0.f;
    asteroidGen();
    
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->update();
    }
    clean();
    collisionCheck();
    spawnAngle++;
}

void GameWindow::render(){
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->render();
    }
    glfwSwapBuffers(window);
}

void GameWindow::clean(){
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i] == nullptr || objects[i]->shouldDestroy()) {
            objects.erase(std::remove(objects.begin(),objects.end(),objects[i]),objects.end());
            i--;
        }
    }
    
}

GameWindow::~GameWindow(){
}

glm::mat4 GameWindow::makeMVP(glm::mat4 model) const{
    return projection * view * model;
}

void GameWindow::instantiate(Entity &ent){
    objects.push_back(&ent);
    ent.init();
}

void GameWindow::remove(Entity &ent){
    objects.erase(std::remove(objects.begin(), objects.end(), &ent), objects.end());
}

void GameWindow::remove(std::string entID){
    for(int i = 0; i < objects.size();i++){
        if (objects[i]->getID() == entID) {
            remove(*objects[i]);
            return;
        }
    }
}

Entity* GameWindow::findByID(std::string entID){
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->getID() == entID) {
            return objects[i];
        }
    }
    return 0;
}

void GameWindow::collisionCheck(){
    std::vector<Entity*> collisionCall;
    std::vector<Entity::Collider> arguments;

    struct Circle{
        glm::vec3 c;
        float radius;
    };
    
    for (int i = 0;  i < objects.size(); i++) {
        glm::vec4 centre;
        Circle a;
        Entity* player = objects[i];
        centre = player->objectModel() * glm::vec4(player->getCollider().centre,1.0f);
        a.c = glm::vec3(centre.x,centre.y,0.f);
        a.radius = player->getCollider().radius;
        for (int j = 0;  j < objects.size(); j++) {
            if (j == i) {
                continue;
            }
            Circle b;
            Entity* rocket = objects[j];
            centre = rocket->objectModel() * glm::vec4(rocket->getCollider().centre,1.0f);
            b.c = glm::vec3(centre.x,centre.y,0.f);
            b.radius = rocket->getCollider().radius;
            
            glm::vec3 d = a.c - b.c;
            
            float dist = glm::dot(d, d);
            float radSum = a.radius + b.radius;
            if (dist <= radSum * radSum) {
                Entity::Collider col = rocket->getCollider();
                col.parentID = rocket->getID();
                collisionCall.push_back(player);
                arguments.push_back(col);
            }
        }
    }
    
    for (int i = 0;  i < collisionCall.size() && i < arguments.size(); i++) {
        collisionCall[i]->onCollision(arguments[i]);
    }
}

void GameWindow::asteroidGen(){
    static float time = 100;
    if (time <= 1) {
        time = 100;
        float spawnDir = atan2(0-spawnPos[1],0-spawnPos[0]);
        //printf("Spawn dir %.2f\n",glm::degrees(spawnDir));
        Asteroid *asteroid = new Asteroid(spawnPos,glm::degrees(spawnDir));
        Entity::Collider col = Entity::Collider(0,0,100,100);
        col.makeCircle(sqrt(pow(100,2)+pow(100, 2)), glm::vec3(50.f,50.f,0.f));
        asteroid->addCollider(col);
        asteroid->setID("asteroid");
        instantiate(*asteroid);
    }
    
    time-= 3;
}