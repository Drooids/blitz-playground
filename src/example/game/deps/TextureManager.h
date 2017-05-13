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

	
private:

}