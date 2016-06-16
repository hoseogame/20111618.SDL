#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <iostream>
#include <map>
#include <SDL_image.h>

class TextureManager
{
private:
	TextureManager() {}
	static TextureManager* s_pInstance;
	std::map<std::string, SDL_Texture*> m_textureMap;
public:
	static TextureManager* Instance()
	{
		
		if ( s_pInstance == 0 )
		{
			s_pInstance = new TextureManager();
		}
		return s_pInstance;
	}

	~TextureManager();

	bool load( std::string fileName, std::string id, SDL_Renderer* pRenderer );

	void draw( std::string id, int x, int y, int width, int height,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void drawAngle( std::string id, int x, int y, int width, int height, double angle,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void drawFrame( std::string id, int x, int y, int width, int height,
		int currentRow, int currentFrame , SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void drawAngleFrame( std::string id, int x, int y, int width, int height, double angle,
		int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void clearFromTextureMap(std::string id);
} typedef TheTextureManager;

#endif // !_TEXTUREMANAGER_H_