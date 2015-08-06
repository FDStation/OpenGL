#ifndef __FD_LOADSHADER_H__
#define	__FD_LOADSHADER_H__

#include <iostream>
using namespace std;
#include "GL/glew.h"

typedef struct {
	GLenum	tpye;
	char*		name;
	GLuint		shader;
} ShaderInfo;


GLuint LoadShader(ShaderInfo*	shaderInfo);

const char* ReadShader(const char* file);


#endif // !__FD_LOADSHADER_H__