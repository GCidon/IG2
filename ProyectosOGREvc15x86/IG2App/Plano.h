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
	Plano(Ogre::SceneNode* node, Ogre::Camera* cam);
	~Plano();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void receiveEvent(EntityIG* entidad, int evento);

protected:
	Ogre::Entity* planoEnt;

private:
	Ogre::MovablePlane* mpRef;
};

