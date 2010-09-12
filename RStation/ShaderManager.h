#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include "RStation.h"
#include <GL/glfw.h>

class ShaderLoader;

struct Shader
{
	GLuint ptr, vs, fs;
	std::string path, vertSource, fragSource;

	ShaderLoader *loader;
};

namespace ShaderManager
{
	Shader CheckForDuplicates(std::string _path);

	void addShader(Shader _shader);
	void clear();
}

#endif
