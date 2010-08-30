#include <GL/glew.h> // must be before glfw.h!
#include "Shader.h"

void Shader::Load(std::string _vs, std::string _fs)
{
	if ( program )
		return; // already generated.
	
	// create pointers for our vertex and frag shaders
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);	
	
	// set the shader sources
	glShaderSource(vs, 1, (const GLchar**)_vs.c_str(), NULL);
	glShaderSource(fs, 1, (const GLchar**)_fs.c_str(), NULL);
	
	// compile shaders
	glCompileShader(vs);
	glCompileShader(fs);
	
	// create program, attach shaders, link.
	program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	glLinkProgram(program);
}

void Shader::Load(GLuint _program)
{
	if ( program )
		return;
	program = _program;
}

void Shader::Unload()
{
	glDeleteProgram(program);
}

void Shader::Bind()
{
	if ( program )
		glUseProgram(program);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

GLuint Shader::GetProgram()
{
	return program;
}
