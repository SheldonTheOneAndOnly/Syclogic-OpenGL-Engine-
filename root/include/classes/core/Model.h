#ifndef MODEL_H
#define MODEL_H

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

#include<glm/gtx/string_cast.hpp>

#include<classes/core/Mesh.h>

using namespace std;
using namespace glm;

class Model {
public:
	vector<Mesh> meshes;

	Model(string file);
	void Draw(Shader& shader, Camera& camera);
};

#endif