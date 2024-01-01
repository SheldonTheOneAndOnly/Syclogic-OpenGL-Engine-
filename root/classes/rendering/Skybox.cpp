#include<classes/rendering/skybox.h>

Skybox::Skybox(string name) : shader(Shader("root/shaders/lighting/skybox", false)) {
	vector<Vertex>vertices(verts, verts + sizeof(verts) / sizeof(Vertex));
	vector<unsigned int>indices(inds, inds + sizeof(inds) / sizeof(unsigned int));
	VAO.Bind();

	VBO VBO(vertices, GL_STATIC_DRAW);
	EBO EBO(indices);

	VAO.Link(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	string names[6] = {
		"_PX",
		"_NX",
		"_PY",
		"_NY",
		"_PZ",
		"_NZ"
	};

	string extension = name.substr(name.find_last_of("."));
	string rawName = name.substr(0, name.find_last_of("."));

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < 6; i++) {
		int width, height, numColCh;
		unsigned char* bytes = stbi_load(("root/resources/textures/sky/" + rawName + names[i] + extension).c_str(), &width, &height, &numColCh, 0);
		if (bytes) {
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
			stbi_image_free(bytes);
		}
		else {
			cout << "ERROR: Skybox texture failed to load!" << endl;
			stbi_image_free(bytes);
		}
	}
	handle = glGetTextureHandleARB(ID);

	shader.Activate();
	glUniformHandleui64ARB(glGetUniformLocation(shader.ID, "skybox"), handle);
}

void Skybox::Draw(Camera cam) {
	glDepthFunc(GL_LEQUAL);

	shader.Activate();
	mat4 view = mat4(1.0f);
	mat4 proj = mat4(1.0f);
	view = mat4(mat3(lookAt(cam.position, cam.position + cam.angle, cam.upDirection)));
	proj = perspective(radians(cam.FOV), (float)cam.width / cam.height, cam.nearZ, cam.farZ);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camView"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMat"), 1, GL_FALSE, value_ptr(proj));

	VAO.Bind();
	glMakeTextureHandleResidentARB(handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	VAO.Unbind();

	glDepthFunc(GL_LESS);
}