#pragma once

#include<iostream>

#include<fstream>
#include<string>
#include<vector>

#include<glew.h>

#include<glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat2x2.hpp>
#include<mat3x3.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

#include<SOIL2.h>

using namespace std;


string read_file(string);
void window_settings();
void opengl_settings();