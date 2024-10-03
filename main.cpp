#include "source.h"
#include "MATH/Mat.h"
#include "MATH/Vec.h"

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIND_WID, WIND_HEIGT, WIND_TITLE, NULL, NULL);
	if (window == NULL) {
		std::cout << "CONTEXT ERROR:: FIALED TO CREATE WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferCallback);
	
	gladInit();
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShaderString = getShaderFromFile("vertex.shader");
	const char* vertexShaderSource = vertexShaderString.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "SHADER ERROR:: compilation VERTEX SHADER error\n" << infolog << std::endl;;
		return(EXIT_FAILURE);
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderString = getShaderFromFile("fragment.shader");
	const char* fragmentShaderSource = fragmentShaderString.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "SHADER ERROR:: compilation FRAGMENT SHADER error\n" << infolog << std::endl;
		return(EXIT_FAILURE);
	}
	
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "SHADER ERROR:: SHADER PROGRAM linking failed\n" << infolog << std::endl;
		return(EXIT_FAILURE);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo_position;
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	
	unsigned int ebo_position;
	glGenBuffers(1, &ebo_position);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_position);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int vbo_color;
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	vec3 scaleFactor(1.0f, 1.0f, 0.0f);
	vec3 shift_positon(0.0f, 0.0f, 0.0f);
	
	Mat4 rotation = Mat4();
	Mat4 view = Mat4();
	Mat4 result = Mat4();
	Mat4 scale = Mat4();

	float angle = 0; 

	vec3 viewAxis(0.0f, 0.0f, 0.5f);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.4f, 0.6f, 0.4f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		//mathemetical stuff
		
		Mat4 scaleMatrix = scale.scale(scaleFactor);
		Mat4 rotationYMatrix = rotation.rotationYaxisf(angle);
		Mat4 viewMatrix = view.translationMatrixf(viewAxis);
		Mat4 resultMatrix = viewMatrix.multiply(rotationYMatrix);

		unsigned int unl = glGetUniformLocation(shaderProgram, "rotationMatrix");
		glUniformMatrix4fv(unl, 1, GL_FALSE, resultMatrix.mat);
		unsigned int unl2 = glGetUniformLocation(shaderProgram, "scaleMatrix");
		glUniformMatrix4fv(unl2, 1, GL_TRUE, scaleMatrix.mat);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		Input(window,&scaleFactor,&shift_positon,&angle);
		getSecond();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	
	glfwTerminate();
}
