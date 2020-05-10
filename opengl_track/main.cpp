#include "libs.h"

using namespace std;


void resize_callback(GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
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
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the Window
	GLFWwindow* window = glfwCreateWindow(
		WIDOWN_WIDTH, WINDOW_HEIGHT,
		"OpenGL Track", NULL, NULL
	);

	// Resizable Window
	glfwSetFramebufferSizeCallback(window, resize_callback);

	// Uncomment this, if the window is not resizable
	//// Prepare Framebuffer
	//glfwGetFramebufferSize(
	//	window,
	//	&frameBufferWidth,
	//	&frameBufferHeight
	//);

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