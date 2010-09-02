#include "TextureManager.h"

std::vector<Texture> tm_textures;

Texture TextureManager::CheckForDuplicates(std::string _path)
{
	for(unsigned i = 0; i<tm_textures.size(); i++)
	{
		Texture cur = tm_textures[i];
		if(cur.path == _path)
		{
			Log::DebugPrint("[TextureManager] Texture already loaded. Using existing copy.");
			return cur;
		}
	}
	Texture blank;
	blank.ptr = NULL;
	return blank;
}

void TextureManager::addTexture(Texture _texture)
{
	tm_textures.push_back(_texture);
}

void TextureManager::clear()
{
	// These should be cleaned up properly by ImageLoader, so no need here.
	for(unsigned i = 0; i<tm_textures.size(); i++)
	{
		tm_textures.pop_back();
	}
}
