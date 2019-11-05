#pragma once
#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include "EntityIG.h"
#include <iostream>

using namespace std;

class Sinbad :
	public EntityIG
{
private:
	Ogre::Entity* ent;
	Ogre::Entity* swordL;
	Ogre::Entity* swordR;
	Ogre::AnimationState* bailar;
	Ogre::AnimationState* runBase;
	Ogre::AnimationState* runTop;

	Ogre::Animation* vuelta;
	Ogre::NodeAnimationTrack* vueltaTrack;
	Ogre::AnimationState* vueltaState;

	Ogre::Real duracion;

	bool muerto = false;
	bool aux = false;
private:
	void animacionPatrulla();
	void animacionHaciaBomba();

public:
	Sinbad(Ogre::SceneNode* node, Ogre::Real dur);

	virtual void frameRendered(const Ogre::FrameEvent& evt);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void receiveEvent(EntityIG* entidad, int evento);

};

