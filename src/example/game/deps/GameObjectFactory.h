#ifndef GAMEOBJECTFACTORY_H_DEFINED
#define GAMEOBJECTFACTORY_H_DEFINED

#include "BaseCreator.h"
#include <map>

/*
	The approach we will take is to have
	the factory contain std::map that maps a string (the type of our object) to a small
	class called Creator whose only purpose is the creation of a specific object.
*/

class GameObjectFactory
{

public:

	static GameObjectFactory* Instance();

	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it =
			m_creators.find(typeID);

		if(it != m_creators.end()) {
			delete pCreator;
			return false;
		}

		m_creators[typeID] = pCreator;

		return true;
	}

	GameObject* create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it =
			m_creators.find(typeID);

		if(it == m_creators.end()) {
			printf("Could not find type: \n", typeID);
			return NULL;
		}

		// For example, (*it).first will give you the key and (*it).second will give you the value.
		// These are equivalent to it->first and it->second.
		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();
	}

private:

	static GameObjectFactory* s_pInstance;

	std::map<std::string, BaseCreator*> m_creators;

};

typedef GameObjectFactory TheGameObjectFactory;

#endif
