#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include "EntityIG.h"
class Plano :
	public EntityIG
{
public:
	Plano(Ogre::SceneNode* node);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void receiveEvent(EntityIG* entidad);

protected:
	Ogre::Entity* planoEnt;
};

