#include "libs.h"

using namespace std;


void resize_callback(GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}


bool loadShaders(GLuint &program) {
	
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

	GLuint core_program;
	if (!loadShaders(core_program))
		glfwTerminate();



	///////////////
	// Main Loop //
	///////////////

	while (! glfwWindowShouldClose(window)) {

		// Input {
		glfwPollEvents();
		// }

		// Update {
		//
		// }

		// Draw {
		//	clear canvas {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear the canvas with a color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL); // Clear Buffers
		//	}
		//	draw on canvas {
		//		Nothing as of Now
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
	glfwTerminate();

	return 0;
}