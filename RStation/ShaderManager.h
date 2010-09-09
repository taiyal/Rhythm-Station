#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include "RStation.h"
#include <GL/glfw.h>

class ShaderLoader;

struct Shader
{
	std::string path;
	GLuint ptr;

	ShaderLoader *loader;
};

namespace ShaderManager
{
	Shader CheckForDuplicates(std::string _path);

	void addShader(Shader _shader);
	void clear();
}

#endif
