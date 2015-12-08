#include "Cube.h"

Cube::Cube(float size, const std::string vertexShader, const std::string fragmentShader):
shader(vertexShader, fragmentShader) {
	size /= 2;
	float verticesTemp[6 * 2 * 3][3] = { { -size, -size, -size }, { size, -size, -size }, { size, size, -size },
										 { -size, -size, -size }, { -size, size, -size }, { size, size, -size },

										 { size, -size, size }, { size, -size, -size }, { size, size, -size },
										 { size, -size, size }, { size, size, size }, { size, size, -size },

										 { -size, -size, size }, { size, -size, size }, { size, -size, -size },
										 { -size, -size, size }, { -size, -size, -size }, { size, -size, -size },

										 { -size, -size, size }, { size, -size, size }, { size, size, size },
										 { -size, -size, size }, { -size, size, size }, { size, size, size },

										 { -size, -size, -size }, { -size, -size, size }, { -size, size, size },
										 { -size, -size, -size }, { -size, size, -size }, { -size, size, size },

										 { -size, size, size }, { size, size, size }, { size, size, -size },
										 { -size, size, size }, { -size, size, -size }, { size, size, -size } };

	float colorsTemp[6 * 2 * 3][3] = { { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
									   { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },

									   { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
									   { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },

									   { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 },
									   { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 },

									   { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
									   { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },

									   { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
									   { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },

									   { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 },
									   { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 } };

	for(int i = 0; i < 6 * 2 * 3; i++) {
		for(int j = 0; j < 3; j++) {
			vertices[i][j] = verticesTemp[i][j];
			colors[i][j] = colorsTemp[i][j];
		}
	}
}

Cube::~Cube() {}

void Cube::draw(mat4& projection, mat4& modelview) {
	glUseProgram(shader.getProgramID());

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
		glEnableVertexAttribArray(1);

		GLint projectionLocation = glGetUniformLocation(shader.getProgramID(), "projection");
		GLint modelviewLocation = glGetUniformLocation(shader.getProgramID(), "modelview");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(modelviewLocation, 1, GL_FALSE, value_ptr(modelview));

		glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);

	glUseProgram(0);
}