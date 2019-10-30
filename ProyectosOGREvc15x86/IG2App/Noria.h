#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <string>
#include "Aspa.h"
#include "EntityIG.h"
#include <vector>

using namespace std;

class Noria :
	public EntityIG
{
protected:

	std::vector<Ogre::SceneNode*> aspasNode;
	std::vector<Aspa*> aspas;
	Ogre::SceneNode* cilindro;

	int numAspas;
	bool parao = false;

public:
	Noria(Ogre::SceneNode* node, int n);

	~Noria();

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	virtual void receiveEvent(EntityIG* entidad);

	void roll(int grado);

};

