#ifndef MESH_H
#define MESH_H

#include<string>
#include<vector>

#include<glad.h>
#include<glfw3.h>

#include<classes/misc/Shortcuts.h>
#include<classes/rendering/Shader.h>
#include<classes/rendering/VAO.h>
#include<classes/rendering/VBO.h>	
#include<classes/rendering/EBO.h>
#include<classes/rendering/Texture.h>
#include<classes/rendering/Camera.h>

class Mesh {
public:
	std::vector<Vertex> verts;
	std::vector<GLuint> inds;
	std::vector<Texture> texs;

	VAO VAO;

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	void Draw(Shader& shader, Camera& camera);
};

#endif