#ifndef MODEL_H
#define MODEL_H

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

#include<classes/core/Mesh.h>

using namespace std;
using namespace glm;

class Model {
public:
	Model(string file);

	void Draw(Shader& shader, Camera& camera);

private:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	vector<Mesh> meshes;
};

#endif