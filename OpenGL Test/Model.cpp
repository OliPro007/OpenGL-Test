#include "Model.h"

Model::Model(const std::string obj, const std::string mtl, const std::string vertexShader, const std::string fragmentShader) :
vertices(), faces(), normals(), uvs(), vboID(0), vaoID(0), material(), shader(vertexShader, fragmentShader) {
	std::ifstream file(obj);
	if(!file.fail()) {
		std::vector<unsigned> vertexIndices, normalIndices, uvIndices;
		std::vector<vec3> tmpVertices;
		std::vector<vec3> tmpNormals;
		std::vector<vec2> tmpUvs;

		std::string line;
		Material* currentMaterial = nullptr;
		while(std::getline(file, line)) {
			if(line.substr(0, 2) == "v ") {
				std::istringstream stream(line.substr(2));
				vec3 vertex;
				stream >> vertex.x >> vertex.y >> vertex.z;
				tmpVertices.push_back(vertex);
			} else if(line.substr(0, 2) == "vt") {
				std::istringstream stream(line.substr(3));
				vec2 uv;
				stream >> uv.x >> uv.y;
				tmpUvs.push_back(uv);
			} else if(line.substr(0, 2) == "vn") {
				std::istringstream stream(line.substr(3));
				vec3 normal;
				stream >> normal.x >> normal.y >> normal.z;
				tmpNormals.push_back(normal);
			} else if(line.substr(0, 2) == "f ") {
				std::istringstream dataGroup(line.substr(2));
				std::string vertex1, vertex2, vertex3;
				dataGroup >> vertex1 >> vertex2 >> vertex3;

				std::istringstream data;
				std::string index;
				vec3 face;
				data.str(vertex1);
				std::getline(data, index, '/');
				face.x = (float)atoi(index.c_str());
				vertexIndices.push_back(atoi(index.c_str()));
				std::getline(data, index, '/');
				uvIndices.push_back(atoi(index.c_str()));
				std::getline(data, index);
				normalIndices.push_back(atoi(index.c_str()));

				data.clear();
				data.str(vertex2);
				std::getline(data, index, '/');
				face.y = (float)atoi(index.c_str());
				vertexIndices.push_back(atoi(index.c_str()));
				std::getline(data, index, '/');
				uvIndices.push_back(atoi(index.c_str()));
				std::getline(data, index);
				normalIndices.push_back(atoi(index.c_str()));

				data.clear();
				data.str(vertex3);
				std::getline(data, index, '/');
				face.z = (float)atoi(index.c_str());
				vertexIndices.push_back(atoi(index.c_str()));
				std::getline(data, index, '/');
				uvIndices.push_back(atoi(index.c_str()));
				std::getline(data, index);
				normalIndices.push_back(atoi(index.c_str()));

				faces.push_back(face);
			} else if(line.substr(0, 3) == "mtl") {
				readMTL(mtl);
			}/* else if(line.substr(0, 7) == "usemtl ") {
				std::string name = line.substr(7);
				for(Material& material : materials) {
					if(material.name == name)
						currentMaterial = &material;
				}
			}*/
		}

		for(size_t i = 0; i < vertexIndices.size(); i++) {
			vec3 vertex = tmpVertices[vertexIndices[i] - 1];
			vertices.push_back(vertex);
			vec2 uv = tmpUvs[uvIndices[i] - 1];
			uvs.push_back(uv);
			vec3 normal = tmpNormals[normalIndices[i] - 1];
			normals.push_back(normal);
		}

		file.close();

		loadBuffers();
	} else {
		std::cerr << "Error reading " << obj << std::endl;
	}
}

Model::~Model() {
	vertices.clear();
	uvs.clear();
	normals.clear();
	faces.clear();
	glDeleteBuffers(1, &vboID);
	glDeleteVertexArrays(1, &vaoID);
}

void Model::readMTL(const std::string path) {
	std::ifstream file(path);
	if(!file.fail()) {
		std::string line;
		while(std::getline(file, line)) {
			if(line.substr(0, 7) == "newmtl ") {
				material.name = line.substr(7);
			} else if(line.substr(0, 3) == "Ns ") {
				material.ns = (float)atof(line.substr(3).c_str());
			} else if(line.substr(0, 3) == "Ni ") {
				material.ni = (float)atof(line.substr(3).c_str());
			} else if(line.substr(0, 2) == "d ") {
				material.d = (float)atof(line.substr(2).c_str());
			} else if(line.substr(0, 6) == "illum ") {
				material.illum = atoi(line.substr(6).c_str());
			} else if(line.substr(0, 3) == "Ks ") {
				std::istringstream stream(line.substr(3));
				vec3 ks;
				stream >> ks.x >> ks.y >> ks.z;
				material.ks = ks;
			} else if(line.substr(0, 3) == "Ka ") {
				std::istringstream stream(line.substr(3));
				vec3 ka;
				stream >> ka.x >> ka.y >> ka.z;
				material.ka = ka;
			} else if(line.substr(0, 3) == "Kd ") {
				std::istringstream stream(line.substr(3));
				vec3 kd;
				stream >> kd.x >> kd.y >> kd.z;
				material.kd = kd;
			} else if(line.substr(0, 7) == "map_Kd ") {
				material.texture.setImage(line.substr(7));
			}
		}
	}
}

void Model::loadBuffers() {
	if(glIsBuffer(vboID) == GL_TRUE)
		glDeleteBuffers(1, &vboID);

	size_t verticesSize = vertices.size() * sizeof(vec3);
	size_t texSize = uvs.size() * sizeof(vec2);
	size_t normalsSize = normals.size() * sizeof(vec3);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, verticesSize + texSize + normalsSize, 0, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, &vertices[0]);
		if(material.texture.isLoaded()) { //Transfer both texture and normals
			glBufferSubData(GL_ARRAY_BUFFER, verticesSize, texSize, &uvs[0]);
			glBufferSubData(GL_ARRAY_BUFFER, verticesSize + texSize, normalsSize, &normals[0]);
		} else { //Transfer only normals
			glBufferSubData(GL_ARRAY_BUFFER, verticesSize, normalsSize, &normals[0]);
		}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if(glIsVertexArray(vaoID) == GL_TRUE)
		glDeleteVertexArrays(1, &vaoID);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);
			if(material.texture.isLoaded()) { //Enable both texture and normals
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(verticesSize));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(verticesSize + texSize));
				glEnableVertexAttribArray(3);
			} else { //Enable only normals
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(verticesSize));
				glEnableVertexAttribArray(3);
			}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::updateVBO(void* data, int size, int offset) {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	void* vboAddress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if(vboAddress == nullptr) {
		std::cerr << "Error getting vbo address" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return;
	}

	memcpy((char*)vboAddress + offset, data, size);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	vboAddress = nullptr;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::draw(mat4& projection, mat4& modelview) {
	glUseProgram(shader.getProgramID());

	glBindVertexArray(vaoID);
		GLint projectionLocation = glGetUniformLocation(shader.getProgramID(), "projection");
		GLint modelviewLocation = glGetUniformLocation(shader.getProgramID(), "modelview");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(modelviewLocation, 1, GL_FALSE, value_ptr(modelview));

		GLint ambiantLocation = glGetUniformLocation(shader.getProgramID(), "ambiant");
		GLint diffuseLocation = glGetUniformLocation(shader.getProgramID(), "diffuse");
		GLint specularLocation = glGetUniformLocation(shader.getProgramID(), "specular");
		glUniform3fv(ambiantLocation, 1, value_ptr(material.ka));
		glUniform3fv(diffuseLocation, 1, value_ptr(material.kd));
		glUniform3fv(specularLocation, 1, value_ptr(material.ks));

		GLint lightLocation = glGetUniformLocation(shader.getProgramID(), "light");
		glUniform3f(lightLocation, 0, 0, -100.0);

		if(material.texture.isLoaded()) {
			glBindTexture(GL_TEXTURE_2D, material.texture.getID());
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());
			glBindTexture(GL_TEXTURE_2D, 0);
		} else {
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		}		
	glBindVertexArray(0);

	glUseProgram(0);
}
