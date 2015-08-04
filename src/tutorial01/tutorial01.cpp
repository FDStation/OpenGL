#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

enum VAO_IDs {Triagnle, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init(void)
{
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

}




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(argv[0]);

	GLenum res = glewInit();
    if (GLEW_OK != res) {
		cerr << "Error:" << glewGetErrorString(res) << endl;
		cerr << "Failed to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
    }
    glutMainLoop();

    return 0;
}