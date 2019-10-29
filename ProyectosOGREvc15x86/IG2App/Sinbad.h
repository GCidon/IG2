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

	bool aux = false;

public:
	Sinbad(Ogre::SceneNode* node) : EntityIG(node) {
		ent = mSM->createEntity("Sinbad.mesh");
		mNode->attachObject(ent);
		mNode->setScale(50, 50, 50);
		mNode->setPosition(1000, 250, -1000);

		swordL = mSM->createEntity("Sword.mesh");
		swordR = mSM->createEntity("Sword.mesh");

		ent->attachObjectToBone("Handle.R", swordR);
		ent->attachObjectToBone("Sheath.L", swordL);


		bailar = ent->getAnimationState("Dance");
		bailar->setLoop(true);

		runBase = ent->getAnimationState("RunBase");
		runBase->setLoop(true);

		runTop = ent->getAnimationState("RunTop");
		runTop->setLoop(true);

		/*system("CLS");

		Ogre::AnimationStateSet* aux1 = ent->getAllAnimationStates();
		auto it = aux1->getAnimationStateIterator().begin();
		while (it != aux1->getAnimationStateIterator().end()) {
			auto s = it->first;
			cout << it->first << "\n";
			++it;
		}

		auto skeleton = ent->getMesh()->getSkeleton();
		auto numBones = skeleton->getNumBones();
		for (int i = 0; i < numBones; i++) { cout << skeleton->getBone(i)->getName() << "\n"; }*/
	}

	virtual void frameRendered(const Ogre::FrameEvent& evt) {
		if (aux) {
			runBase->setEnabled(false);
			runTop->setEnabled(false);
			bailar->setEnabled(true);
			bailar->addTime(evt.timeSinceLastFrame);
		}
		else {
			bailar->setEnabled(false);
			runBase->setEnabled(true);
			runTop->setEnabled(true);
			runBase->addTime(evt.timeSinceLastFrame);
			runTop->addTime(evt.timeSinceLastFrame);
		}
	}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		if (evt.keysym.sym == SDLK_c)
		{
			aux = !aux;
			ent->detachObjectFromBone(swordR);
			ent->detachObjectFromBone(swordL);
			if (aux) {
				ent->attachObjectToBone("Sheath.R", swordR);
				ent->attachObjectToBone("Sheath.L", swordL);
			}
			else {
				ent->attachObjectToBone("Handle.R", swordR);
				ent->attachObjectToBone("Sheath.L", swordL);
			}
		}
		return true;
	}

};

