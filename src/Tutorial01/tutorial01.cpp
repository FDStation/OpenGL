#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"

#include "LoadShader.h"
#include "FileUtils.h"


enum VAO_IDs {Triagnle, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};
enum Uniform_IDs {Scale, TransformMat, NumUniforms};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint Uniforms[NumUniforms];

const GLuint NumVertices = 6;

void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

	char vertFilePath[256] = {0};
	char fragFilePath[256] = {0};
	getFullPath("src/Tutorial01/triangles.vert", vertFilePath, sizeof(vertFilePath));
	getFullPath("src/Tutorial01/triangles.frag", fragFilePath, sizeof(fragFilePath));

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, vertFilePath},
		{GL_FRAGMENT_SHADER, fragFilePath},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShader(shaders);
	glValidateProgram(program);
	glUseProgram(program);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);

	Uniforms[Scale] = glGetUniformLocation(program, "gScale");
	Uniforms[TransformMat] = glGetUniformLocation(program, "gWorld");
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	static float gScale = 0.0f;

	gScale += 0.01f;

	Matrix4f World;
	World.m[0][0] = sinf(gScale);			World.m[0][1] = 0.0f;			World.m[0][2] = 0.0f;		World.m[0][3] = 0;
	World.m[1][0] = 0.0f;		World.m[1][1] = sinf(gScale);		World.m[1][2] = 0.0f;		World.m[1][3] = 0.0f;
	World.m[2][0] = 0.0f;		World.m[2][1] = 0.0f;		World.m[2][2] = sinf(gScale);		World.m[2][3] = 0.0f;
	World.m[3][0] = 0.0f;		World.m[3][1] = 0.0f;		World.m[3][2] = 0.0f;		World.m[3][3] = 1.0f;

	glUniform1f(Uniforms[Scale], sin(gScale));
	glUniformMatrix4fv(Uniforms[TransformMat], 1, GL_TRUE, &World.m[0][0]);

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