#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <string>
#include "Aspa.h"
#include "EntityIG.h"
#include <math.h>
#include <vector>

using namespace std;

class Monheco :
	public EntityIG
{
protected:
	Ogre::SceneNode* cuelloNode;
	Ogre::SceneNode* cabezaNode;
	Ogre::SceneNode* cuerpoNode;
	Ogre::SceneNode* ombligoNode;
	Ogre::Entity* cabezaEnt;
	Ogre::Entity* cuerpoEnt;
	int rotacionCabeza;
	bool auxMov = false;
	bool auxNariz = false;
	bool parao = false;
	float angle = 0;

public:
	Monheco(Ogre::SceneNode* node);
	~Monheco() {}

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	virtual void receiveEvent(EntityIG* entidad, int evento);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	

};

