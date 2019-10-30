#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include "EntityIG.h"
#include <string>

class Aspa :
	public EntityIG
{
protected:
	Ogre::SceneNode* aspa1;
	Ogre::SceneNode* aspa2;
	Ogre::SceneNode* cubo;

	int incrX = 0;

public:
	Aspa(Ogre::SceneNode* node);
	~Aspa() {}

	void roll(int grado);

};

