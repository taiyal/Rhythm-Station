#include <GL/glew.h> // must be before glfw.h!
#include "Shader.h"

std::string getShaderLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	std::string log;
	
	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		log = infoLog;
		free(infoLog);
	}
	return log;
}

std::string getProgramLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	std::string log;
	
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		log = infoLog;
		free(infoLog);
	}
	return log;
}

Shader::Shader()
{
	program = NULL;
	Log::DebugPrint("[Shader::Shader] Creating a new shader.");
}

Shader::~Shader()
{
	Log::DebugPrint("[Shader::~Shader] Cleaning up shader.");
	this->Unload();
}

void Shader::Load(std::string _vs, std::string _fs)
{
	Log::DebugPrint("[Shader::Load] Loading shader...");
	if ( program )
	{
		Log::DebugPrint("[Shader::Load] Shader already loaded.");
		return; // return if this has already been done.
	}
	
	// create pointers for our vertex and frag shaders
	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);	

	const char *vss = _vs.c_str();
	const char *fss = _fs.c_str();
	
	// set the shader sources
	glShaderSource(vs, 1, &vss, NULL);
	glShaderSource(fs, 1, &fss, NULL);
	
	// compile shaders
	glCompileShader(vs);
	glCompileShader(fs);
	
	// create program, attach shaders, link.
	program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	glLinkProgram(program);
	
	// print out shader logs.
	std::string log = getShaderLog(vs);
	if ( log.size() > 0 )
		Log::Print("Vertex shader log: " + log);
	log = getShaderLog(fs);
	if ( log.size() > 0 )
		Log::Print("Fragment shader log: " + log);
	log = getProgramLog(program);
	if ( log.size() > 0 )
		Log::Print("Shader program log: " + log);
	
	Log::DebugPrint("[Shader::Load] Loaded.");
}

void Shader::Load(GLuint _program)
{
	if ( program )
		return;
	program = _program;
}

void Shader::Unload()
{
	// detach shaders from the program so they can be deleted
	glDetachShader(program, vs);
	glDetachShader(program, fs);
	
	// delete shaders
	glDeleteShader(fs);
	glDeleteShader(vs);
	
	// finally, delete the program.
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
