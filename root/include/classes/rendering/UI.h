#ifndef UI_H
#define UI_H

#include<iostream>
#include<map>

#include<glm/vec2.hpp>
#include<glm/matrix.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<classes/rendering/Shader.h>

#include<ft2build.h>
#include FT_FREETYPE_H

using namespace glm;
using namespace std;

class UI {
private:
	FT_Library ft;
	FT_Face f;
public:
	GLuint VAO;
	GLuint VBO;
	struct FTChar {
		unsigned int ID;
		ivec2 Size;
		ivec2 Bearing;
		unsigned int Advance;
	};

	map<char, FTChar> Chars;
	UI(GLFWwindow* window);

	void DrawText(Window w, Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);
};

#endif