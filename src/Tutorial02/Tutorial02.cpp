#include <iostream>
using namespace std;

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "LoadShader.h"
#include "FileUtils.h"

enum VAO_IDs {Tetrahedron, NumVAOs};
enum Buffer_IDs {ArrayBuffer, IndiceBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};
enum Uniform_IDs {uWorld, NumUniforms};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint Uniforms[NumUniforms];

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Tetrahedron]);

	GLfloat vertecies[4][3] = {
		{-0.50f, -0.50f, -0.50f},
		{ 0.50f, -0.50f, -0.50f},
		{ 0.00f,  0.50f,  0.00f},
		{ 0.00f, -0.50f,  0.50f}
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

	GLuint indices[] = {
		//1, 2, 3, 2, 3, 4, 1, 3, 4, 1, 2, 4
		0, 1, 2, 1, 2, 3, 0, 2, 3, 0, 1, 3
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[IndiceBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	char vertFilePath[256] = {0};
	char fragFilePath[256] = {0};
	getFullPath("src/Tutorial02/Tetrahedron.vert", vertFilePath, sizeof(vertFilePath));
	getFullPath("src/Tutorial02/Tetrahedron.frag", fragFilePath, sizeof(fragFilePath));

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, vertFilePath},
		{GL_FRAGMENT_SHADER, fragFilePath},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShader(shaders);
	glValidateProgram(program);
	glUseProgram(program);

	Uniforms[uWorld] = glGetUniformLocation(program, "uWorld");
	 
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static GLfloat scale = 0.0f;
	scale += 0.01f;

	GLfloat m[4][4];
	m[0][0] = 1.0f;				m[0][1] = 0.0f;					m[0][2] = 0.0f;				m[0][3] = 0.0f;
	m[1][0] = 0.0f;				m[1][1] = cosf(scale);			m[1][2] = sinf(scale);		m[1][3] = 0.0f;
	m[2][0] = 0.0f;				m[2][1] = -sinf(scale);		m[2][2] = cosf(scale);		m[2][3] = 0.0f;
	m[3][0] = 0.0f;				m[3][1] = 0.0f;					m[3][2] = 0.0f;				m[3][3] = 1.0f;
	glUniformMatrix4fv(Uniforms[uWorld], 1, GL_TRUE, &m[0][0]);

	glBindVertexArray(VAOs[Tetrahedron]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[IndiceBuffer]);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Failed to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}