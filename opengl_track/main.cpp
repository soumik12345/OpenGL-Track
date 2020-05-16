#include "libs.h"

using namespace std;
using namespace glm;


Vertex vertices[] =
{
	//Position							//Color						//Texcoords
	vec3(-0.5f, 0.5f, 0.f),				vec3(1.f, 0.f, 0.f),		vec2(0.f, 1.f),
	vec3(-0.5f, -0.5f, 0.f),			vec3(0.f, 1.f, 0.f),		vec2(0.f, 0.f),
	vec3(0.5f, -0.5f, 0.f),				vec3(0.f, 0.f, 1.f),		vec2(1.f, 0.f),
	vec3(0.5f, 0.5f, 0.f),				vec3(1.f, 1.f, 0.f),		vec2(1.f, 1.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0, 1, 2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);


void resize_callback(GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}


bool loadShaders(GLuint& program) {

	char infoLog[512]; // Log of info if the shader linking fails
	GLint success;

	// Vertex Shader {
	string vertex_shader_source = read_file("core.vert");
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertex_source = vertex_shader_source.c_str();
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);
	// Error Handling
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		cout << "Error::main.cpp::Unable to load vertex shader" << endl;
		cout << infoLog << endl;
		return false;
	}
	// }

	// Fragment Shader {
	string fragment_shader_source = read_file("core.frag");
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragment_source = fragment_shader_source.c_str();
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);
	// Error Handling
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		cout << "Error::main.cpp::Unable to load fragment shader" << endl;
		cout << infoLog << endl;
		return false;
	}
	// }

	// Program {
	program = glCreateProgram(); // Create Program
	// Attach Shaders to Programs
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program); // Link Program
	// Error Handling
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cout << "Error::main.cpp::Unable to link progran" << endl;
		cout << infoLog << endl;
		return false;
	}
	// }


	// End {
	glUseProgram(0);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	// }

	return true;
}


void update_input(GLFWwindow* window) {
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


int main() {

	/////////////////////
	// Initialize GLFW //
	/////////////////////
	glfwInit();
	
	/////////////////////
	// Create a Window //
	/////////////////////

	// Define Window Size
	const int WINDOW_HEIGHT = 720;
	const int WIDOWN_WIDTH = 1280;

	// Define Frame Buffer Size
	int frameBufferHeight = 0, frameBufferWidth = 0;

	// Window Settings
	window_settings();

	// Create the Window
	GLFWwindow* window = glfwCreateWindow(
		WIDOWN_WIDTH, WINDOW_HEIGHT,
		"OpenGL Track", NULL, NULL
	);

	//// Resizable Window
	//glfwSetFramebufferSizeCallback(window, resize_callback);

	// Prepare Framebuffer
	glfwGetFramebufferSize(
		window,
		&frameBufferWidth,
		&frameBufferHeight
	);

	//// Prepare Viewport
	//glViewport(0, 0, frameBufferWidth, frameBufferHeight);

	glfwMakeContextCurrent(window);

	/////////////////////
	// Initialize GLEW //
	/////////////////////

	glewExperimental = GL_TRUE;

	// Initialize GLEW

	if (glewInit() != GLEW_OK) {
		cout << "Error::main.cpp::GLEW Initialization Failed" << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	/////////////////
	// Shader Init //
	/////////////////

	// OpenGL options {
	opengl_settings();
	// }
	
	// Shader Init {
	GLuint core_program;
	if (!loadShaders(core_program))
		glfwTerminate();
	// }

	////////////////
	// Model Init //
	////////////////


	/////////////
	// Buffers //
	/////////////
	
	// Vertex Arrau Object {
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// }

	// Vertex Buffer Object {
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// }

	// Element Buffer Object {
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// }

	
	////////////////////
	// Input Assembly //
	////////////////////

	// vertex_position {
	GLuint attribute_location = glGetAttribLocation(core_program, "vertex_position");
	glVertexAttribPointer(
		attribute_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)
	);
	glEnableVertexAttribArray(attribute_location);
	// }

	// vertex_color {
	attribute_location = glGetAttribLocation(core_program, "vertex_color");
	glVertexAttribPointer(
		attribute_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)offsetof(Vertex, color)
	);
	glEnableVertexAttribArray(attribute_location);
	// }

	// vertex_textcoord {
	attribute_location = glGetAttribLocation(core_program, "vertex_textcoord");
	glVertexAttribPointer(
		attribute_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (GLvoid*)offsetof(Vertex, texture_coordinate)
	);
	glEnableVertexAttribArray(attribute_location);
	// }

	glBindVertexArray(0);
	
	///////////////
	// Main Loop //
	///////////////

	while (! glfwWindowShouldClose(window)) {

		// Input {
		glfwPollEvents();
		// }

		// Update {
		update_input(window);
		// }

		// Draw {
		//	clear canvas {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear the canvas with a color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL); // Clear Buffers
		//	}
		// use shader {
		glUseProgram(core_program);
		glBindVertexArray(VAO);
		// }
		//	draw on canvas {
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);
		//	}
		//	end draw {
		glfwSwapBuffers(window);
		glFlush();
		//	}
		// }
	}

	/////////
	// End //
	/////////

	glfwDestroyWindow(window);
	glfwTerminate();

	glDeleteProgram(core_program);

	return 0;
}