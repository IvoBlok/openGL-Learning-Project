#ifndef SIMPLELIGHTINGSHADER_H
#define SIMPLELIGHTINGSHADER_H

#include <shaders/Shader.h>
#include <vector>
#include <iostream>

struct DirLightData {
	glm::vec3 direction = glm::vec3(0.f, 0.f, -1.f);

	glm::vec3 ambient = glm::vec3(0.2f);
	glm::vec3 diffuse = glm::vec3(1.f);
	glm::vec3 specular = glm::vec3(1.f);
};

struct PointLightData {
    glm::vec3 position = glm::vec3(0.f);

    float constant = 1.f;
    float linear = 0.09f;
    float quadratic =  0.032f;

    glm::vec3 ambient = glm::vec3(0.05f);
    glm::vec3 diffuse = glm::vec3(0.8f);
    glm::vec3 specular = glm::vec3(1.f);

    int enabled = 1; // 0 is disabled, 1 is enabled

    // for some reason I had to explicitly make the constructor
    PointLightData(
        glm::vec3 _position = glm::vec3(0.f),
        float _constant = 1.f,
        float _linear = 0.09f,
        float _quadratic = 0.032f,
        glm::vec3 _ambient = glm::vec3(0.05f),
        glm::vec3 _diffuse = glm::vec3(0.8f),
        glm::vec3 _specular = glm::vec3(1.f),
        int _enabled = 1) {
        position = _position;
        constant = _constant;
        linear = _linear;
        quadratic = _quadratic;
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
        enabled = _enabled;
    }

    // function for updating all values in one call
    void updateData(
        PointLightData& baseData,
        glm::vec3 _position = glm::vec3(NULL),
        float _constant = NULL,
        float _linear = NULL,
        float _quadratic = NULL,
        glm::vec3 _ambient = glm::vec3(NULL),
        glm::vec3 _diffuse = glm::vec3(NULL),
        glm::vec3 _specular = glm::vec3(NULL),
        int _enabled = 1)
    {
        position = (_position.x != NULL) ? _position : baseData.position;
        constant = (_constant != NULL) ? _constant : baseData.constant;
        linear = (_linear != NULL) ? _linear : baseData.linear;
        quadratic = (_quadratic != NULL) ? _quadratic : baseData.quadratic;
        ambient = (_ambient.x != NULL) ? _ambient : baseData.ambient;
        diffuse = (_diffuse.x != NULL) ? _diffuse : baseData.diffuse;
        specular = (_specular.x != NULL) ? _specular : baseData.specular;
        enabled = _enabled;
    }
    
    int getID() {
        return ID;
    }
    void setID(int _ID) {
        ID = _ID;
    }

private:
    int ID = -1;

};

struct SpotLightData {
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    int enabled; // 0 is disabled, 1 is enabled

        // for some reason I had to explicitly make the constructor
    SpotLightData(
        glm::vec3 _position = glm::vec3(0.f),
        glm::vec3 _direction = glm::vec3(1.f),
        float _cutOff = glm::cos(glm::radians(12.5f)),
        float _outerCutOff = glm::cos(glm::radians(15.0f)),
        float _constant = 1.f,
        float _linear = 0.09f,
        float _quadratic = 0.032f,
        glm::vec3 _ambient = glm::vec3(0.05f),
        glm::vec3 _diffuse = glm::vec3(0.8f),
        glm::vec3 _specular = glm::vec3(1.f),
        int _enabled = 1) {
        position = _position;
        cutOff = _cutOff;
        outerCutOff = _outerCutOff;
        constant = _constant;
        linear = _linear;
        quadratic = _quadratic;
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
        enabled = _enabled;
    }

    // function for updating all values in one call
    void updateData(
        SpotLightData& baseData,
        const glm::vec3& _position = glm::vec3(NULL),
        const glm::vec3& _direction = glm::vec3(NULL),
        const float& _cutOff = NULL,
        float _outerCutOff = NULL,
        float _constant = NULL,
        float _linear = NULL,
        float _quadratic = NULL,
        glm::vec3 _ambient = glm::vec3(NULL),
        glm::vec3 _diffuse = glm::vec3(NULL),
        glm::vec3 _specular = glm::vec3(NULL),
        int _enabled = 1)
    {
        position = (_position.x != NULL) ? _position : baseData.position;
        direction = (_direction.x != NULL) ? _direction : baseData.direction;
        cutOff = (_cutOff != NULL) ? _cutOff : baseData.cutOff;
        outerCutOff = (_outerCutOff != NULL) ? _outerCutOff : baseData.outerCutOff;
        constant = (_constant != NULL) ? _constant : baseData.constant;
        linear = (_linear != NULL) ? _linear : baseData.linear;
        quadratic = (_quadratic != NULL) ? _quadratic : baseData.quadratic;
        ambient = (_ambient.x != NULL) ? _ambient : baseData.ambient;
        diffuse = (_diffuse.x != NULL) ? _diffuse : baseData.diffuse;
        specular = (_specular.x != NULL) ? _specular : baseData.specular;
        enabled = _enabled;
    }

    int getID() {
        return ID;
    }
    void setID(int _ID) {
        ID = _ID;
    }
private:
    int ID = -1;
};

class simpleLightingShader : public Shader {
private:
    // light data
    std::vector<PointLightData> pointLightsData;
    std::vector<SpotLightData> spotLightsData;

public:
    // constructor
    using Shader::Shader;

    // getters & setters
    PointLightData& getPointLightData(int index) {
        if ((int)pointLightsData.size() == index) {
            PointLightData newLightData = PointLightData();
            pointLightsData.push_back(newLightData);
            Shader::setInt("pointLightCount", (int)pointLightsData.size());
            pointLightsData[index].setID(index);

            return newLightData;
        }
        else {
            return pointLightsData[index];
        }
    }
    SpotLightData& getSpotLightData(int index) {
        if ((int)spotLightsData.size() == index) {
            SpotLightData newLightData = SpotLightData();
            spotLightsData.push_back(newLightData);
            Shader::setInt("spotLightCount", (int)spotLightsData.size());

            spotLightsData[index].setID(index);
            std::cout << index;

            return newLightData;
        }
        else {
            return spotLightsData[index];
        }
    }

    // counters   (equal to the length of the light data vectors, but I guess this helps with minimzing vector count calls)
    unsigned int pointLightCount = 0;
    unsigned int spotLightCount = 0;

	void setDirLight(DirLightData& data) const {
		Shader::setVec3("dirLight.direction", data.direction);
		Shader::setVec3("dirLight.ambient", data.ambient);
		Shader::setVec3("dirLight.diffuse", data.diffuse);
		Shader::setVec3("dirLight.specular", data.specular);
	}

    std::vector<int> createEmptyPointLights(simpleLightingShader& shader, int amount = 1) const {
        std::vector<int> IDs;
        for (int i = 0; i < amount; i++)
        {
            shader.pointLightsData.push_back(PointLightData());
            int ID = (int)shader.pointLightsData.size() - 1;
            shader.pointLightsData[ID].setID(ID);
            IDs.push_back(ID);
        }
        shader.pointLightCount += amount;
        Shader::setInt("pointLightCount", (int)shader.pointLightsData.size());

        // return the id(s) of the created pointlightdata struct
        return IDs;
    }
    int createPointLight(simpleLightingShader& self, PointLightData& data) const {
        // if the data ID isn't yet set, the point light is new, so the counts should be updated
        if (data.getID() == -1) {
            data.setID(self.pointLightCount);
            self.pointLightCount += 1;
            self.pointLightsData.push_back(data);
            Shader::setInt("pointLightCount", (int)self.pointLightsData.size());
        }
        else {
            self.pointLightsData[data.getID()] = data;
            std::cout << "WARNING: TRIED TO CREATE POINT LIGHT WITH A POINT LIGHT STRUCT THAT ALREADY HAS A VALID ID. pointlightsdata has been updated";
        }

        std::string pointLightUniformName = "pointLights[" + std::to_string(data.getID()) + "]";

        Shader::setVec3(pointLightUniformName + ".position", data.position);
        Shader::setVec3(pointLightUniformName + ".ambient", data.ambient);
        Shader::setVec3(pointLightUniformName + ".diffuse", data.diffuse);
        Shader::setVec3(pointLightUniformName + ".specular", data.specular);
        Shader::setFloat(pointLightUniformName + ".constant", data.constant);
        Shader::setFloat(pointLightUniformName + ".linear", data.linear);
        Shader::setFloat(pointLightUniformName + ".quadratic", data.quadratic);
        Shader::setInt(pointLightUniformName + ".enabled", data.enabled);

        return data.getID();
    }
    void updatePointLight(simpleLightingShader& self, int index) const {
        if (index < 0 || index >= self.pointLightsData.size()) {
            std::cout << "WARNING: GIVEN INDEX IS INVALID -> SimpleLightingShader.setPointLight()" << std::endl;
            return;
        }

        PointLightData data = self.pointLightsData[index];

        std::string pointLightUniformName = "pointLights[" + std::to_string(data.getID()) + "]";

        Shader::setVec3(pointLightUniformName + ".position", data.position);
        Shader::setVec3(pointLightUniformName + ".ambient", data.ambient);
        Shader::setVec3(pointLightUniformName + ".diffuse", data.diffuse);
        Shader::setVec3(pointLightUniformName + ".specular", data.specular);
        Shader::setFloat(pointLightUniformName + ".constant", data.constant);
        Shader::setFloat(pointLightUniformName + ".linear", data.linear);
        Shader::setFloat(pointLightUniformName + ".quadratic", data.quadratic);
        Shader::setInt(pointLightUniformName + ".enabled", data.enabled);


        // no need to return the ID, as it should be the same as the given index
    }

    std::vector<int> createEmptySpotLights(simpleLightingShader& shader, int amount = 1) const {
        std::vector<int> IDs;
        for (int i = 0; i < amount; i++)
        {
            shader.spotLightsData.push_back(SpotLightData());
            int ID = (int)shader.spotLightsData.size() - 1;
            shader.spotLightsData[ID].setID(ID);
            IDs.push_back(ID);
        }
        shader.spotLightCount += amount;
        Shader::setInt("spotLightCount", (int)shader.spotLightsData.size());
        // return the id(s) of the created pointlightdata struct
        return IDs;
    }
    int createSpotLight(simpleLightingShader& self, SpotLightData& data) const {
        // if the data ID isn't yet set, the point light is new, so the counts should be updated
        if (data.getID() == -1) {
            data.setID(self.spotLightCount);
            self.spotLightCount += 1;
            self.spotLightsData.push_back(data);
            Shader::setInt("spotLightCount", (int)self.spotLightsData.size());
        }
        else {
            self.spotLightsData[data.getID()] = data;
            std::cout << "WARNING: TRIED TO CREATE SPOT LIGHT WITH A POINT LIGHT STRUCT THAT ALREADY HAS A VALID ID. spotlightsdata has been updated";
        }

        std::string spotLightUniformName = "spotLights[" + std::to_string(data.getID()) + "]";

        Shader::setVec3(spotLightUniformName + ".position", data.position);
        Shader::setVec3(spotLightUniformName + ".direction", data.direction);
        Shader::setVec3(spotLightUniformName + ".ambient", data.ambient);
        Shader::setVec3(spotLightUniformName + ".diffuse", data.diffuse);
        Shader::setVec3(spotLightUniformName + ".specular", data.specular);
        Shader::setFloat(spotLightUniformName + ".constant", data.constant);
        Shader::setFloat(spotLightUniformName + ".linear", data.linear);
        Shader::setFloat(spotLightUniformName + ".quadratic", data.quadratic);
        Shader::setInt(spotLightUniformName + ".enabled", data.enabled);
        Shader::setFloat(spotLightUniformName + ".cutOff", data.cutOff);
        Shader::setFloat(spotLightUniformName + ".outerCutOff", data.outerCutOff);

        return data.getID();
    }
    void updateSpotLight(simpleLightingShader& self, int index) const {
        if (index < 0 || index >= self.spotLightsData.size()) {
            std::cout << "WARNING: GIVEN INDEX IS INVALID -> SimpleLightingShader.setSpotLight()" << std::endl;
            return;
        }
        SpotLightData data = self.spotLightsData[index];

        

        std::string spotLightUniformName = "spotLights[" + std::to_string(data.getID()) + "]";

        Shader::setVec3(spotLightUniformName + ".position", data.position);
        Shader::setVec3(spotLightUniformName + ".direction", data.direction);
        Shader::setVec3(spotLightUniformName + ".ambient", data.ambient);
        Shader::setVec3(spotLightUniformName + ".diffuse", data.diffuse);
        Shader::setVec3(spotLightUniformName + ".specular", data.specular);
        Shader::setFloat(spotLightUniformName + ".constant", data.constant);
        Shader::setFloat(spotLightUniformName + ".linear", data.linear);
        Shader::setFloat(spotLightUniformName + ".quadratic", data.quadratic);
        Shader::setInt(spotLightUniformName + ".enabled", data.enabled);
        Shader::setFloat(spotLightUniformName + ".cutOff", data.cutOff);
        Shader::setFloat(spotLightUniformName + ".outerCutOff", data.outerCutOff);

        // no need to return the ID, as it should be the same as the given index
    }

};

#endif
