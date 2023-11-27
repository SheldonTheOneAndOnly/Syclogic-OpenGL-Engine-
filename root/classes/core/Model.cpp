#include<classes/core/Model.h>

vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

string GetInBetweens(string text, string start, string end) {
	string str = text.substr(text.find_first_of(start) + 1, text.find_last_of(end) - text.find_first_of(start) - 1);
	return str;
}

Model::Model(string file) {
	vector<Vertex> verts;

	vector<GLuint> inds;

	vector<Texture> texs;

	cout << "READING SYC DATA OF \"" << file << "\"" << endl;
	ifstream content(file);
	string strContent;

	if (content.is_open()) {
		string line;

		while (getline(content, line)) {
			// Comment Compilation
			if (line.rfind("#", 0) == 0) {
				cout << "Line starts with \"#\", skipping...\n";
			}

			// Vertex Compilation
			if (line.rfind("v", 0) == 0) {
				vec3 pos;
				vec2 uv;
				vec3 nor;
				string lineWithoutPrefix = line.substr(line.find_first_of('p'));
				vector<string> lines = split(lineWithoutPrefix, "; ");

				// For every "vector" in the line (position, UV, and normal vectors)
				for (auto vertLine : lines) {
					// Position
					if (vertLine.rfind("p", 0) == 0) {
						string numList = vertLine.substr(vertLine.find_first_of("p(") + 2, vertLine.find_first_of(")") - 2);
						vector<string> nums = split(numList, ", ");
						pos = vec3(stof(nums[0]), stof(nums[1]), stof(nums[2]));
					}
					
					// UV
					if (vertLine.rfind("u", 0) == 0) {
						string numList = vertLine.substr(vertLine.find_first_of("u(") + 2, vertLine.find_first_of(")") - 2);
						vector<string> nums = split(numList, ", ");
						uv = vec2(stof(nums[0]), stof(nums[1]));
					}

					// Normal
					if (vertLine.rfind("n", 0) == 0) {
						string numList = vertLine.substr(vertLine.find_first_of("n(") + 2, vertLine.find_first_of(")") - 2);
						vector<string> nums = split(numList, ", ");
						nor = vec3(stof(nums[0]), stof(nums[1]), stof(nums[2]));
					}
				}

				// Push back the vertex data
				verts.push_back(Vertex{ pos, vec3(1.0f, 1.0f, 1.0f), uv, nor });
			}

			// Index Compilation
			if (line.rfind("f", 0) == 0) {
				string lineWithoutPrefix = GetInBetweens(line, "(", ")");
				vector<string> lines = split(lineWithoutPrefix, ", ");

				// For every integer in the line
				for (auto line : lines) {
					int num = stoi(line);
					inds.push_back(num);
				}
			}

			// Texture Compilation
			if (line.rfind("t", 0) == 0) {
				string diff;
				string spec;
				string norm;
				vector<int> indices2;

				string lineWithoutPrefix = line.substr(line.find_first_of('f'));
				vector<string> lines = split(lineWithoutPrefix, "; ");

				// For every attribute in material
				for (auto textLine : lines) {
					// Texture name
					if (textLine.rfind("f", 0) == 0) {
						string textLineCompiled = textLine.substr(textLine.find_first_of("f(") + 2, textLine.find_last_of(")") - textLine.find_first_of("f(") - 2);
						vector<string> textLines = split(textLineCompiled, ", ");

						// For every attribute in texture
						for (auto attrib : textLines) {
							if (attrib.rfind("diff=", 0) == 0) {
								string name = GetInBetweens(attrib, "\"", "\"");
								diff = name;
							}
							if (attrib.rfind("spec=", 0) == 0) {
								string name = GetInBetweens(attrib, "\"", "\"");
								spec = name;
							}
							if (attrib.rfind("norm=", 0) == 0) {
								string name = GetInBetweens(attrib, "\"", "\"");
								norm = name;
							}
						}
					}

					// Indices
					if (textLine.rfind("i", 0) == 0) {
						string iList = textLine.substr(textLine.find_first_of("i(") + 2, textLine.find_first_of(")") - 2);
						vector<string> nums = split(iList, ", ");
						for (string num : nums) indices2.push_back(stoi(num));
					}
				}

				string textureDirectory = "root/resources/textures/";

				texs.push_back(Texture((textureDirectory + diff).c_str(), "diff", GL_LINEAR, GL_REPEAT));
				if (!spec.empty()) texs.push_back(Texture((textureDirectory + spec).c_str(), "spec", GL_LINEAR, GL_REPEAT));
				if (!norm.empty()) texs.push_back(Texture((textureDirectory + norm).c_str(), "norm", GL_LINEAR, GL_REPEAT));
			}
		}

		// Mesh Compilation
		for (Vertex vert : verts) {
			cout << vert.pos.x << ", " << vert.pos.y << ", " << vert.pos.z << endl;
			cout << vert.UV.x << ", " << vert.UV.y << endl;
			cout << vert.nor.x << ", " << vert.nor.y << ", " << vert.nor.z << endl;
		}
		meshes.push_back(Mesh(verts, inds, texs));
	}

	cout << "SYC FILE SUCCESSFULLY LOADED" << endl;
}

void Model::Draw(Shader& shader, Camera& camera) {
	for (Mesh m : meshes) m.Draw(shader, camera);
}