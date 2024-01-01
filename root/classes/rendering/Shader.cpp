#include<classes/rendering/Shader.h>

Shader::Shader(std::string name, bool hasGeo) {
	cout << name << endl;
	std::string vertCode = GetFileContents((name + "_vertex.glsl").c_str());
	std::string geoCode;
	if (hasGeo) geoCode = GetFileContents((name + "_geometry.glsl").c_str());
	std::string fragCode = GetFileContents((name + "_fragment.glsl").c_str());

	const char* vertSource = vertCode.c_str();
	const char* geoSource;
	if (hasGeo) { geoSource = geoCode.c_str(); }
	const char* fragSource = fragCode.c_str();

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, NULL);
	glCompileShader(vertShader);

	GLuint geoShader;
	if (hasGeo) {
		geoShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geoShader, 1, &geoSource, NULL);
		glCompileShader(geoShader);
	}

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "Vertex Shader Compilation Failed!\n" << infoLog << std::endl;
	}

	if (hasGeo) {
		glGetShaderiv(geoShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(geoShader, 512, NULL, infoLog);
			std::cout << "Geometry Shader Compilation Failed!\n" << infoLog << std::endl;
		}
	}

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "Fragment Shader Compilation Failed!\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertShader);
	if (hasGeo) { glAttachShader(ID, geoShader); }
	glAttachShader(ID, fragShader);

	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Shader Program Compilation Failed!\n" << infoLog << std::endl;
	}

	glDeleteShader(vertShader);
	if (hasGeo) { glDeleteShader(geoShader); }
	glDeleteShader(fragShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Destroy() {
	glDeleteProgram(ID);
}