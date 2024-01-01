#include<classes/core/Mesh.h>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) {
	verts = vertices;
	inds = indices;
	texs = textures;

	VAO.Bind();

	VBO VBO(vertices, GL_STATIC_DRAW);
	EBO EBO(indices);

	VAO.Link(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
	VAO.Link(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.Link(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.Link(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(8 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera) {
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffs = 0;
	unsigned int numSpecs = 0;
	unsigned int numNors = 0;

	for (unsigned int i = 0; i < texs.size(); i++) {
		std::string num;
		std::string type = texs[i].texType;
		if (type == "diff") {
			num = std::to_string(numDiffs++);
		}
		else if (type == "spec") {
			num = std::to_string(numSpecs++);
		}
		else if (type == "norm") {
			num = std::to_string(numNors++);
		}
		texs[i].TextureUnit(shader, (type + num).c_str());
		texs[i].Bind();
	}
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
	camera.Mat(shader);

	glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, 0);
}