#ifndef MATERIAL_H
#define MATERIAL_H

#include<string>

#include<classes/rendering/Texture.h>

class Material {
public:
	GLuint ID;
	Texture diffuse;
	Texture normal;
	Texture specular;
	Texture displacement;

	Material(Texture* dif, Texture* nor = NULL, Texture* spec = NULL, Texture* disp = NULL);
	void SetMaterial(std::string textureType, const char* file);
};

#endif#pragma once
