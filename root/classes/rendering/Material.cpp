#include<classes/rendering/Material.h>

Material::Material(const char* sycmat) {
	ifstream content(sycmat);

	if (content.is_open()) {
		string line, diffContent, specContent, normContent, filtContent, mfiltContent, extContent;

		while (getline(content, line)) {

			if (line.rfind("diffuse = ", 0) == 0) {
				diffContent = line.substr(10);
			}

			if (line.rfind("specular = ", 0) == 0) {
				specContent = line.substr(11);
			}

			if (line.rfind("normal = ", 0) == 0) {
				normContent = line.substr(9);
			}

			if (line.rfind("filter = ", 0) == 0) {
				filtContent = line.substr(9);
			}

			if (line.rfind("mipmapfilter = ", 0) == 0) {
				mfiltContent = line.substr(15);
			}

			if (line.rfind("extension = ", 0) == 0) {
				extContent = line.substr(12);
			}
		}

		int count = 1;
		if (!specContent.empty() && normContent.empty() || specContent.empty() && !normContent.empty()) {
			count = 2;
		}
		else if (!specContent.empty() && !normContent.empty()) {
			count = 3;
		}

		for (int i = 0; i < count; i++) {
			string content;
			const char* type;
			if (i == 0) {
				content = diffContent;
				type = "diff";
			}
			else if (i == 1) {
				content = specContent;
				type = "spec";
			}
			else {
				content = normContent;
				type = "norm";
			}

			GLint filter;

			if (mfiltContent == "none") {
				if (filtContent == "linear") filter = GL_LINEAR;
				else if (filtContent == "nearest") filter = GL_NEAREST;
			}
			else if (mfiltContent == "linear") {
				if (filtContent == "linear") filter = GL_LINEAR_MIPMAP_LINEAR;
				else if (filtContent == "nearest") filter = GL_NEAREST_MIPMAP_LINEAR;
			}
			else if (mfiltContent == "nearest") {
				if (filtContent == "linear") filter = GL_LINEAR_MIPMAP_NEAREST;
				else if (filtContent == "nearest") filter = GL_NEAREST_MIPMAP_NEAREST;
			}

			GLint extension;
			if (extContent == "repeat") {
				extension = GL_REPEAT;
			}
			else if (extContent == "mirrored") {
				extension = GL_MIRRORED_REPEAT;
			}
			else if (extContent == "edge") {
				extension = GL_CLAMP_TO_EDGE;
			}
			else if (extContent == "border") {
				extension = GL_CLAMP_TO_BORDER;
			}

			cout << content << endl;
			Texture texture(content.c_str(), type, filter, extension);
			textures.push_back(texture);
		}
	}
}