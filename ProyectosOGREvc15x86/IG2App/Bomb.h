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
	Ogre::ParticleSystem* pSys;

	Ogre::Animation* vaiven;
	Ogre::NodeAnimationTrack* vaivenTrack;
	Ogre::AnimationState* vaivenState;

	Ogre::Real duracion;

public:
	Bomb(Ogre::SceneNode* node, Ogre::Real dur);

	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void receiveEvent(EntityIG* entidad, int evento);
};

