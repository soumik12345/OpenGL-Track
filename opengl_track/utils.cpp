#include "libs.h"

using namespace std;

string read_file(string file_name) {
	string temp = "", source = "";
	ifstream input_file;
	input_file.open(file_name);
	if (input_file.is_open()) {
		while (getline(input_file, temp))
			source += temp + "\n";
	}
	else {
		cout << "Error::main.cpp::Unable to read file " << file_name << endl;
	}
	input_file.close();
	return source;
}


void window_settings() {
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}


void opengl_settings() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}