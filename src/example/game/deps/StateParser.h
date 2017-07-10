#ifndef STATEPARSER_H_DEFINED
#define STATEPARSER_H_DEFINED

#include <vector>
#include <string>
#include "tinyxml2.h"

#include "Game.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

class StateParser
{
public:
	bool parseState(const char *stateFile, std::string stateID,
		std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs);

private:
	void parseObjects(tinyxml2::XMLElement* pStateRoot,
		std::vector<GameObject*> *pGameObject);

	void debugXML(std::string s, tinyxml2::XMLElement * e);

	void parseTextures(tinyxml2::XMLElement* pStateRoot,
		std::vector<std::string> *pTextureIDs);
};

#endif
