#pragma once

// external
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/euler_angles.hpp>

// internal
#include "Model.h"

// std
#include <string>

class EngineObject {
public:
	// model contains all textures, vertices and material properties
	Model model;
	// x, y, z
	glm::vec3 position = glm::vec3(0.f);
	// rotation around x, y, z respectively
	glm::vec3 rotation = glm::vec3(0.f);
	// scaling factors in x, y, z
	glm::vec3 scaleVec = glm::vec3(1.f);
	
	// Initialization / setup functions

	EngineObject(Shader& defaultNonElemShader, Shader& defaultElemShader, std::string const& path, std::map<std::string, int> settings = {}) {
		setSettings(settings);
		model = Model{ path, settings["gamma"]};
		settings["elementary"] = 0;
		elemDefaultShader = defaultElemShader;
		nonElemDefaultShader = defaultNonElemShader;
	}
	EngineObject(Shader& defaultNonElemShader, Shader& defaultElemShader, ElementaryShapes shape, glm::vec3 color = glm::vec3(1), std::map<std::string, int> settings = {}) {
		//setSettings(settings);
		model = Model{ shape, color, 0 };
		//settings["elementary"] = 1;
		elemDefaultShader = defaultElemShader;
		nonElemDefaultShader = defaultNonElemShader;
	}

	void updateGeometryMatrix() {
		geometryMatrix = glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z) * geometryMatrix;
		geometryMatrix = glm::translate(geometryMatrix, position);
		geometryMatrix = glm::scale(glm::mat4(), scaleVec);
	}

	void setSettings(std::map<std::string, int> settings) {
		auto iter = settings.begin();
		while (iter != settings.end()) {
			this->settings.find(iter->first)->second = iter->second;
			iter++;
		}
	}

	void setDefaultShaders(const Shader& defaultNonElemShader, const Shader& defaultElemShader) {
		elemDefaultShader = defaultElemShader;
		nonElemDefaultShader = defaultNonElemShader;
	}

	// Manipulation functions

	void setColor(glm::vec3 color) {
		model.meshes[0].color = color;
	}

	void move(glm::vec3 translation) {
		position += translation;
		geometryMatrix = glm::translate(geometryMatrix, translation);
	}

	void rotate(glm::vec3 axis, float angle) {
		geometryMatrix = glm::rotate(geometryMatrix, angle, axis);
	}
	// Custom implementation of the LookAt function
	void rotate(glm::vec3 direction, glm::vec3 up = glm::vec3(0, 1, 0))
	{
		//glm::vec3 rotVec = (direction + up) / 2.f;
		//rotate(rotVec, glm::radians(180.f));
		rotation = glm::vec3(std::atan(direction.x / -direction.y), 0, std::atan(std::sqrt(std::pow(direction.x,2) + std::pow(direction.y, 2))/direction.z));
	}

	void scale(glm::vec3 scalingVec) {
		scaleVec = scalingVec;
		geometryMatrix = glm::scale(geometryMatrix, scalingVec);
	}
	void scale(float scalingFactor) {
		scaleVec *= scalingFactor;
		geometryMatrix = glm::scale(geometryMatrix, glm::vec3(scalingFactor));
	}

	void draw(Shader& shader) {
		updateGeometryMatrix();
		shader.use();
		shader.setMat4("model", geometryMatrix);
		shader.setMat3("normalMatrix", glm::transpose(glm::inverse(geometryMatrix)));
		model.draw(shader, settings["elementary"]);
	}

	void draw() {
		if (settings["onlyEdges"] == 1) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); } else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
		if (settings["elementary"] == 1) {
			draw(elemDefaultShader);
		}
		else {
			draw(nonElemDefaultShader);
		}
		if (settings["onlyEdges"] == 1) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
	}

private:
	// the resulting matrix from applying the transformations given by the position and rotation
	glm::mat4 geometryMatrix = glm::mat4(1.f);
	std::map<std::string, int> settings = { {"onlyEdges", 0}, {"elementary", 1}, {"gamma", 0}};

	Shader nonElemDefaultShader{"", ""};
	Shader elemDefaultShader{"", ""};
};