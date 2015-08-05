#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "LoadShader.h"

enum VAO_IDs {Triagnle, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init(void)
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triagnle]);

	GLfloat vertices[NumVertices][2] = {
		{-0.90f, -0.90f},
		{ 0.85f, -0.90f},
		{-0.90f,  0.85f},
		{ 0.90f, -0.85f},
		{ 0.90f,  0.90f},
		{-0.85f,  0.90f},
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "D:\\Work\\OpenGL\\trunk\\src\\tutorial01\\triangles.vert"},
		{GL_FRAGMENT_SHADER, "D:\\Work\\OpenGL\\trunk\\src\\tutorial01\\triangles.frag"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShader(shaders);
	glValidateProgram(program);
	glUseProgram(program);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triagnle]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(512, 512);
    glutCreateWindow(argv[0]);

	GLenum res = glewInit();
    if (GLEW_OK != res) {
		cerr << "Error:" << glewGetErrorString(res) << endl;
		cerr << "Failed to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
    }
	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);

    glutMainLoop();

    return 0;
}