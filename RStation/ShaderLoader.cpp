#include <GL/glew.h> // must be before glfw.h!
#include "ShaderLoader.h"
#include "ShaderManager.h"
#include "FileManager.h"

std::string getShaderLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	std::string log;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = new char[infologLength];
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		log = infoLog;
		delete[] infoLog;
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
		infoLog = new char[infologLength];
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		log = infoLog;
		delete[] infoLog;
	}
	return log;
}

ShaderLoader::ShaderLoader()
{
	program = NULL;
}

ShaderLoader::~ShaderLoader()
{
	this->Unbind();
	this->Unload();
}

void ShaderLoader::Load(std::string _vs, std::string _fs, bool reload)
{
	if ( program && !reload)
	{
		if ( !reload )
		{
			Log::DebugPrint("[ShaderLoader::Load] Shader already loaded.");
			return; // return if this has already been done.
		}
		else
		{
			this->Unload(); // unload everything if reloading.
			Log::DebugPrint("[ShaderLoader::Load] Reloading shader.");
		}
	}
	_vs = "GameData/Shaders/" + _vs;
	_fs = "GameData/Shaders/" + _fs;
	
	// expand the file paths for vs and fs.
	_vs = FileManager::GetFile(_vs);
	_fs = FileManager::GetFile(_fs);

	// load up the files
	_vs = FileManager::GetFileContents(_vs);
	_fs = FileManager::GetFileContents(_fs);
	
	// bad paths!
	if(_vs.size() == 0 || _fs.size() == 0)
		return;
	
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

	glUseProgram(program);
}

void ShaderLoader::Load(GLuint _program)
{
	if ( program )
		return;
	program = _program;
	glUseProgram(program);
}

void ShaderLoader::Unload()
{
	// detach shaders from the program so they can be deleted
	glDetachShader(program, vs);
	glDetachShader(program, fs);

	// delete shaders
	glDeleteShader(fs);
	glDeleteShader(vs);

	// finally, delete the program.
	glDeleteProgram(program);

	// ready to reload
	program = NULL;
}

void ShaderLoader::Bind()
{
	if ( program )
		glUseProgram(program);
}

void ShaderLoader::Unbind()
{
	glUseProgram(0);
}

GLuint ShaderLoader::getProgram()
{
	return program;
}
