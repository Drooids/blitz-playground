#ifndef TEXTURE_H_DEFINED
#define TEXTURE_H_DEF

class TextureManager
{
public:

	TextureManager();
	~TextureManager();

	static TextureManager* Instance();

	bool load(std::string fileName, std::string id,
	SDL_Renderer* pRenderer);

	void draw(std:string id, int x, int y, int width, int heght,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std:string id, int x, int y, int width, int heght,
	int currentRow, SDL_Renderer* pRenderer,
	SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

	std::map<std::string, SDL_Texture*> m_textureMap;

}