#include "StateParser.h"

/*
	Example:

	<?xml version="1.0" ?>
	<STATES>
		<MENU>
			<TEXTURES>
			  <texture filename="assets/button.png" ID="playbutton"/>
			  <texture filename="assets/exit.png" ID="exitbutton"/>
			</TEXTURES>
			<OBJECTS>
			  <object type="MenuButton" x="100" y="100" width="400"
			  height="100" textureID="playbutton" numFrames="0"
			  callbackID="1"/>
			  <object type="MenuButton" x="100" y="300" width="400"
			  height="100" textureID="exitbutton" numFrames="0"
			  callbackID="2"/>
			</OBJECTS>
		</MENU>
		<PLAY>
		</PLAY>
		<GAMEOVER>
		</GAMEOVER>
	</STATES>
*/

bool StateParser::parseState(const char *stateFile, std::string stateID,
	std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs)
{
	// create the XML document
	tinyxml2::XMLDocument xmlDoc;

	if(xmlDoc.LoadFile(stateFile) != 0) {
		std::cout << xmlDoc.ErrorName() << "\n";
		xmlDoc.PrintError();
		return false;
	}

	tinyxml2::XMLElement* pRoot = xmlDoc.RootElement(); // E.x: <STATES>
	tinyxml2::XMLElement* pStateRoot = 0;

	// get this states root node and assign it to pStateRoot
	for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement()) {

		if(e->Value() == stateID) {
			pStateRoot = e;
		}
	}

	debugXML("pStateRoot:", pStateRoot);

	// Textures

	tinyxml2::XMLElement* pTextureRoot = 0;

	// get the root of the texture elements
	for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement()) {

		if(e->Value() == std::string("TEXTURES"))
		{
		  pTextureRoot = e;
		}
	}

	debugXML("pTextureRoot: ", pTextureRoot);

	// now parse the textures
	parseTextures(pTextureRoot, pTextureIDs);

	// Objects

	// pre declare the object root node
	tinyxml2::XMLElement* pObjectRoot = 0;

	// get the root node and assign it to pObjectRoot
	for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement()) {

		if(e->Value() == std::string("OBJECTS")) {
			pObjectRoot = e;
		}
	}

	debugXML("pObjectRoot: ", pObjectRoot);

	// now parse the objects
	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(tinyxml2::XMLElement* pStateRoot,
	std::vector<std::string> *pTextureIDs)
{
	for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement()) {

		std::string filenameAttr = e->Attribute("filename");
		std::string idAttr = e->Attribute("ID");

		debugXML("parseTextures e: ", e);

		pTextureIDs->push_back(idAttr);

		TheTextureManager::Instance()->load(filenameAttr, idAttr,
			TheGame::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(tinyxml2::XMLElement* pStateRoot,
	std::vector<GameObject* > *pObjects)
{
	for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement()) {

		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->QueryIntAttribute("x", &x);
		e->QueryIntAttribute("y", &y);
		e->QueryIntAttribute("width",&width);
		e->QueryIntAttribute("height", &height);
		e->QueryIntAttribute("numFrames", &numFrames);
		e->QueryIntAttribute("callbackID", &callbackID);
		e->QueryIntAttribute("animSpeed", &animSpeed);

		textureID = e->Attribute("textureID");

		std::cout << e->Attribute("type") << endl;

		GameObject* pGameObject = TheGameObjectFactory::Instance()
			->create(e->Attribute("type"));

		pGameObject->load(new LoaderParams(x,y,width,height,textureID,numFrames,
			callbackID, animSpeed));

		pObjects->push_back(pGameObject);
	}
}

void StateParser::debugXML(std::string s, tinyxml2::XMLElement* e)
{
	std::cout << s << endl;
	tinyxml2::XMLPrinter printer;
	e->Accept(&printer);
	std::string stringBuffer = printer.CStr();
	std::cout << stringBuffer.c_str() << endl;
}