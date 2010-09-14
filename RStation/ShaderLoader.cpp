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
	shader.ptr = NULL;
}

ShaderLoader::~ShaderLoader()
{
	this->Unbind();
	this->Unload();
}

void ShaderLoader::Load(std::string _vs, std::string _fs, bool reload)
{
	shader.path = _vs + "+" + _fs;
	Shader dupe = ShaderManager::CheckForDuplicates(shader.path);

	if (dupe.ptr)
	{
		this->shader = dupe;
		this->Bind();
		return;
	}

	if (shader.ptr && !reload)
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
	shader.vs = glCreateShader(GL_VERTEX_SHADER);
	shader.fs = glCreateShader(GL_FRAGMENT_SHADER);	

	const char *vss = _vs.c_str();
	const char *fss = _fs.c_str();

	// set the shader sources
	glShaderSource(shader.vs, 1, &vss, NULL);
	glShaderSource(shader.fs, 1, &fss, NULL);

	// compile shaders
	glCompileShader(shader.vs);
	glCompileShader(shader.fs);

	// create program, attach shaders, link.
	shader.ptr = glCreateProgram();

	glAttachShader(shader.ptr, shader.vs);
	glAttachShader(shader.ptr, shader.fs);

	glLinkProgram(shader.ptr);

	// print out shader logs.
	std::string log = getShaderLog(shader.vs);
	if ( log.size() > 0 )
		Log::Print("Vertex shader log: " + log);
	log = getShaderLog(shader.fs);
	if ( log.size() > 0 )
		Log::Print("Fragment shader log: " + log);
	log = getProgramLog(shader.ptr);
	if ( log.size() > 0 )
		Log::Print("Shader program log: " + log);

	glUseProgram(shader.ptr);
	ShaderManager::addShader(shader);
}

void ShaderLoader::Load(GLuint _program)
{
	if ( shader.ptr == _program )
		return;
	shader.ptr = _program;
	glUseProgram(shader.ptr);
}

void ShaderLoader::Unload()
{
	// detach shaders from the program so they can be deleted
	glDetachShader(shader.ptr, shader.vs);
	glDetachShader(shader.ptr, shader.fs);

	// delete shaders
	glDeleteShader(shader.fs);
	glDeleteShader(shader.vs);

	// finally, delete the program.
	glDeleteProgram(shader.ptr);

	// ready to reload
	shader.ptr = NULL;
}

void ShaderLoader::Bind()
{
	if ( shader.ptr )
		glUseProgram(shader.ptr);
}

void ShaderLoader::Unbind()
{
	glUseProgram(0);
}
