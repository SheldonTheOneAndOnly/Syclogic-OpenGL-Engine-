#ifndef MATERIAL_H
#define MATERIAL_H

#include<string>
#include<vector>

#include<classes/rendering/Texture.h>

class Material {
public:
	vector<Texture> textures;
	Material(const char* sycmat);
};

#endif
