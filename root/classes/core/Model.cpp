#include<classes/core/Model.h>

Model::Model(string file) {
	vector<vec3> positions;
	vector<vec3> colors;
	vector<vec2> UVs;
	vector<vec3> normals;

	vector<GLuint> inds;

	vector<Texture> texs;

	cout << "READING SYC DATA OF \"" << file << "\"" << endl;
	ifstream content(file);
	string strContent;

	if (content.is_open()) {
		string line;
		bool inVertex = false;
		bool inPos = false;
		bool inCol = false;
		bool inUV = false;
		bool inNor = false;

		bool inIndex = false;

		bool inTexture = false;
		vector<const char*> types;
		GLuint textureSlot = 0;

		while (getline(content, line)) {
			// Get what header the line is
			if (line == "VERTEX") {
				inVertex = true;
			}
			else if (line == "INDEX") {
				inVertex = false;
				inNor = false;
				inIndex = true;
			}
			else if (line == "TEXTURE") {
				inIndex = false;
				inTexture = true;
			}

			// Process vertex data
			if (inVertex) {
				// Get what sub-header the line is for the vertex data
				if (line == "\tPOSITIONS") {
					inPos = true;
				}
				else if (line == "\tCOLORS") {
					inPos = false;
					inCol = true;
				}
				else if (line == "\tUV") {
					inCol = false;
					inUV = true;
				}
				else if (line == "\tNORMALS") {
					inUV = false;
					inNor = true;
				}
				else if (line == "") {
					inPos = false;
					inCol = false;
					inUV = false;
					inNor = false;
				}

				// Process each data
				string stringVec;

				if (inPos) {
					if (line == "\tPOSITIONS") continue;
					stringVec = line.substr(2, line.find_last_not_of("\t"));

					string s;
					stringstream ss(stringVec);

					vector<float> v;

					while (getline(ss, s, ' ')) {
						float val = atof(s.c_str());
						v.push_back(val);
					}

					vec3 vec = vec3(v[0], v[1], v[2]);

					positions.push_back(vec);
				}
				else if (inCol) {
					if (line == "\tCOLORS") continue;
					stringVec = line.substr(2, line.find_last_not_of("\t"));

					string s;
					stringstream ss(stringVec);

					vector<float> v;

					while (getline(ss, s, ' ')) {
						float val = atof(s.c_str());
						v.push_back(val);
					}

					vec3 vec = vec3(v[0], v[1], v[2]);

					colors.push_back(vec);
				}
				else if (inUV) {
					if (line == "\tUV") continue;
					stringVec = line.substr(2, line.find_last_not_of("\t"));

					string s;
					stringstream ss(stringVec);

					vector<float> v;

					while (getline(ss, s, ' ')) {
						float val = atof(s.c_str());
						v.push_back(val);
					}

					vec2 vec = vec2(v[0], v[1]);

					UVs.push_back(vec);
				}
				else if (inNor) {
					if (line == "\tNORMALS") continue;
					stringVec = line.substr(2, line.find_last_not_of("\t"));

					string s;
					stringstream ss(stringVec);

					vector<float> v;

					while (getline(ss, s, ' ')) {
						float val = atof(s.c_str());
						v.push_back(val);
					}

					vec3 vec = vec3(v[0], v[1], v[2]);

					normals.push_back(vec);
				}
			}

			// Process index data
			if (inIndex) {
				if (line == "INDEX" || line == "") continue;
				string stringVec = line.substr(1);

				string s;
				stringstream ss(stringVec);

				vector<GLuint> v;

				while (getline(ss, s, ' ')) {
					GLuint val = atoi(s.c_str());
					inds.push_back(val);
				}
			}

			// Process texture data
			if (inTexture) {
				if (line == "TEXTURE") continue;
				string typeStr = line.substr(1, line.find_first_of('"') - 2);

				auto start = line.find_first_of('"') + 1;
				auto end = line.find_last_of('"');
				string textureName = line.substr(start, end - start);

				for (auto& chara : typeStr) {
					chara = tolower(chara);
				}

				texs.push_back(Texture(("root/resources/textures/" + textureName).c_str(), typeStr.c_str(), textureSlot, GL_LINEAR, GL_REPEAT));
				textureSlot++;
			}
		}
	}

	for (unsigned int i = 0; i < positions.size(); i++) {
		vertices.push_back(Vertex{ positions[i], colors[i], UVs[i], normals[i] });
	}

	for (unsigned int i = 0; i < inds.size(); i++) {
		indices.push_back(inds[i]);
	}

	for (unsigned int i = 0; i < texs.size(); i++) {
		textures.push_back(texs[i]);
	}

	meshes.push_back(Mesh(vertices, indices, textures));

	for (unsigned int i = 0; i < meshes.size(); i++) {
		// Vertex
		for (unsigned int j = 0; j < meshes[i].verts.size(); j++) {
			cout << "Vertex{Pos: (";
			for (unsigned int k = 0; k < meshes[i].verts[j].pos.length(); k++) {
				cout << meshes[i].verts[j].pos[k] << ", ";
			}
			cout << "), Col: (";
			for (unsigned int k = 0; k < meshes[i].verts[j].col.length(); k++) {
				cout << meshes[i].verts[j].col[k] << ", ";
			}
			cout << "), UV: (";
			for (unsigned int k = 0; k < meshes[i].verts[j].UV.length(); k++) {
				cout << meshes[i].verts[j].UV[k] << ", ";
			}
			cout << "), Nor: (";
			for (unsigned int k = 0; k < meshes[i].verts[j].nor.length(); k++) {
				cout << meshes[i].verts[j].nor[k] << ", ";
			}
			cout << ")}" << endl;
		}
	}
}

void Model::Draw(Shader& shader, Camera& camera) {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader, camera);
	}
}