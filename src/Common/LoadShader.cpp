#include "LoadShader.h"



GLuint LoadShader(ShaderInfo* shaderInfo)
{
	if (! shaderInfo)
	{
		cerr << "ShaderInfo shoudn't be NULL" << endl;
		return 0;
	}
	GLuint program = glCreateProgram();

	ShaderInfo* entry = shaderInfo;

	while (entry->tpye != GL_NONE)
	{
		GLuint shader = glCreateShader(entry->tpye);

		entry->shader = shader;

		const GLchar* source = ReadShader(entry->name);

		if (! source)
		{
			for (entry = shaderInfo; entry->tpye != GL_NONE; ++entry)
			{
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}
			return 0;
		}
		glShaderSource(shader, 1, &source, NULL);

		delete [] source;

		glCompileShader(shader);

		GLint compiled;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (! compiled)
		{
#ifdef _DEBUG
			GLsizei length;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			GLchar* log = new GLchar[length + 1];

			glGetShaderInfoLog(shader, length, &length, log);

			cerr << "Shader compilation failed: " << log << endl;

			delete [] log;
#endif // _DEBUG
			return 0;
		}
		glAttachShader(program, shader);

		++ entry;
	}
	glLinkProgram(program);

	GLint linked;

	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (! linked)
	{
#ifdef _DEBUG
		GLint length;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		GLchar* log = new GLchar[length + 1];

		glGetProgramInfoLog(program, length, &length, log);

		cerr << "Shader linking failed: " << log << endl;

		delete [] log;
#endif	//_DEBUG
		for (entry = shaderInfo; entry->tpye != GL_NONE; ++entry)
		{
			glDeleteShader(entry->shader);
			entry->shader = 0;
		}
		return 0;
	}
	return program;
}

const char* ReadShader(const char* file)
{
	FILE* pFile;

	fopen_s(&pFile, file, "rb");

	if (! pFile)
	{
		cerr << "Unable to open file '" << file << "'" << endl;

		return NULL;
	}
	fseek(pFile, 0, SEEK_END);

	int len = ftell(pFile);

	fseek(pFile, 0, SEEK_SET);

	GLchar* source = new GLchar[len + 1];

	fread(source, 1, len, pFile);

	fclose(pFile);

	source [len] = 0;

	return source;
}
