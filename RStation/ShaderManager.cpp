#include "ShaderManager.h"
#include "ShaderLoader.h"

std::vector<Shader> sm_shaders;

Shader ShaderManager::CheckForDuplicates(std::string _path)
{
	for(unsigned i = 0; i<sm_shaders.size(); i++)
	{
		Shader cur = sm_shaders[i];
		if(cur.path == _path)
		{
			Log::DebugPrint("[ShaderManager] Shader already loaded. Using existing program.");
			return cur;
		}
	}
	Shader blank;
	blank.ptr = NULL;
	return blank;
}

void ShaderManager::addShader(Shader _shader)
{
	sm_shaders.push_back(_shader);
}

void ShaderManager::clear()
{
	while(!sm_shaders.empty())
	{
		sm_shaders.back().loader->Unload();
		sm_shaders.pop_back();
	}
}
