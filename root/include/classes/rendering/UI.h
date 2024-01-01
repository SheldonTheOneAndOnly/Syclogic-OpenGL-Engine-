#ifndef UI_H
#define UI_H

#include<iostream>
#include<map>

#include<glm/vec2.hpp>
#include<glm/matrix.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<classes/rendering/Shader.h>
#include<classes/rendering/VAO.h>
#include<classes/rendering/VBO.h>

#include<ft2build.h>
#include FT_FREETYPE_H

using namespace glm;
using namespace std;

class UI {
public:
	UI(Window w);

	void Draw(Window w);
};

class Text {
public:
	string font;

	Text(string fn);
	void Draw(Shader s, string tx, vec2 pos, int size, vec3 col);

private:
	struct Char {
		GLuint64 Handle;
		ivec2   Size;
		ivec2   Bearing;
		unsigned int Advance;
	};
	std::map<char, Char> Chars;

	unsigned int VAO, VBO;
	GLuint64 handle;

	void SetCharBindlessHandle(char c, GLuint64 handle) {
		Chars[c].Handle = handle;
	}
};

#endif