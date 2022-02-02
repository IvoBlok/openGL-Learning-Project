#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// internal
#include "engineObjects/EngineObject.h"
#include "shaders/Shader.h"

// std headers
#include <map>
#include <stdlib.h>

float getRandNumber() {
    return ((rand() % 201) - 100) / 2;
}

void init(std::vector<EngineObject>& objects, std::map<std::string, Shader>& shaders) {

    for (int i = -5; i <= 5; i++)
    {
        for (int j = -5; j <= 5; j++)
        {
            for (int k = -5; k <= 5; k++)
            {
                float sizeOfVector = std::sqrt(std::pow(j * k, 2) + std::pow(i * k, 2) + std::pow(i * j, 2));
                float sigmoidValue = 1 / (1 + std::exp(-sizeOfVector));
                objects.push_back(EngineObject(shaders["lightingShader"], shaders["lightingOneColorShader"], ElementaryShapes::VECTOR, glm::vec3(1.5 - sigmoidValue, 0, sigmoidValue))); //glm::vec3(0.4, 0.1, 0.8)
                objects[objects.size() - 1].move(glm::vec3(5 * i, 5 * j, 5 * k));
                objects[objects.size() - 1].rotate(glm::vec3(j * k, i * k, i * j));
                //objects[objects.size() - 1].scale(glm::vec3(0, sigmoidValue * 4, 0));
            }
        }
    }
    int vertexCount = 11 * 11 * 11 * objects[0].model.meshes[0].vertices.size();
    std::cout << "VERTEXCOUNT: " << vertexCount << std::endl;

    //objects.push_back(EngineObject(shaders["lightingShader"], shaders["lightingOneColorShader"], ElementaryShapes::VECTOR, glm::vec3(0, 0, 1)));
    //objects.push_back(EngineObject(shaders["lightingShader"], shaders["lightingOneColorShader"], ElementaryShapes::VECTOR, glm::vec3(0, 1, 0)));
    //objects.push_back(EngineObject(shaders["lightingShader"], shaders["lightingOneColorShader"], ElementaryShapes::VECTOR, glm::vec3(1, 0, 0)));
    //// x+
    //objects[0].move(glm::vec3(1, 0, 0));
    //objects[0].rotate(glm::vec3(1, 0, 0));
    //// y+ -> up
    //objects[1].move(glm::vec3(0, 1, 0));
    //objects[1].rotate(glm::vec3(0, 1, 0));
    //// z+ 
    //objects[2].move(glm::vec3(0, 0, 1));
    //objects[2].rotate(glm::vec3(0, 0, 1));
}

void frame(std::vector<EngineObject>& objects, std::map<std::string, Shader>& shaders) {

}