#pragma once
#include "EntityIG.h"
#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>

class Bomb :
	public EntityIG
{
private:
	Ogre::Entity* ent;

	Ogre::Animation* vaiven;
	Ogre::NodeAnimationTrack* vaivenTrack;
	Ogre::AnimationState* vaivenState;

	Ogre::Real duracion;

	bool aux = true;

public:
	Bomb(Ogre::SceneNode* node, Ogre::Real dur);

	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

