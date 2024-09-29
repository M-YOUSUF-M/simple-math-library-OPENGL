#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <chrono>
#include <cmath>
#include "MATH/Vec.h"
#include "MATH/Vec.h"

#define WIND_WID 800
#define WIND_HEIGT 800
#define WIND_TITLE "OPENGL"


const float vertices[] = {
    -0.5f, -0.5f, 0.0f, // Bottom left
     0.5f, -0.5f, 0.0f, // Bottom right
    -0.5f, 0.5f,  0.0f, // Top left
	 0.5f, 0.5f,  0.0f  // Top right

};

unsigned int indices[] = {
	0, 1, 2,
	1, 2, 3
};

const float color[] = {
	1.0f, 0.0f, 0.0f, //red
	0.0f, 1.0f, 0.0f, //blue
	0.0f, 0.0f, 1.0f  //green
};

void frameBufferCallback(GLFWwindow* window, int xscale, int yscale) {
	glViewport(0, 0, xscale, yscale);
}

float getSecond() {
	auto now = std::chrono::steady_clock::now();

    // Get the time in seconds as a float
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    float seconds = duration / 10.0f; // convert milliseconds to seconds
	return seconds;
}

void Input(GLFWwindow* window ,vec3* scaleVec3, vec3* positionScale, float *angle) {
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwTerminate();
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		scaleVec3->x += 0.001;
		scaleVec3->y += 0.001;
		scaleVec3->z += 0.001;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		scaleVec3->x -= 0.001;
		scaleVec3->y -= 0.001;
		scaleVec3->z -= 0.001;
		
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		positionScale->x -= 0.001;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		positionScale->x += 0.001;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		*angle += 0.001;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		*angle -= 0.001;
	}

}
void printVec3(vec3& vec) {
	std::cout << "{ ";
	std::cout << vec.x;
	std::cout << " , ";
	std::cout << vec.y;
	std::cout << " , ";
	std::cout << vec.z;
	std::cout << " }" ; 
	std::cout << std::endl;
}

int gladInit() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD::FAILD TO LOAD GLAD" << std::endl;
		return(EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}

std::string getShaderFromFile(std::string filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "CAN'T OPENG THE '" << filename << "'" << std::endl;
	}
	std::string line;
	std::string data = "";
	
	while (std::getline(file, line)) {
		data+= (line+"\n");
	}
	std::cout << data;
	return data;

}
