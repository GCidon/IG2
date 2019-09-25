#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <string>
#include "Aspa.h"
#include <vector>

using namespace std;

class Monheco :
	public OgreBites::InputListener
{
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	Ogre::SceneNode* cuelloNode;
	Ogre::SceneNode* cabezaNode;
	Ogre::SceneNode* cuerpoNode;
	Ogre::SceneNode* narizNode;
	Ogre::SceneNode* ombligoNode;

public:
	Monheco(Ogre::SceneNode* node) : mNode(node) {
		mSM = mNode->getCreator();
		Ogre::Entity* ent;

		cuelloNode = mNode->createChildSceneNode("cuello");

		cabezaNode = cuelloNode->createChildSceneNode("cabeza");
		ent = mSM->createEntity("sphere.mesh");
		cabezaNode->attachObject(ent);
		cabezaNode->setScale(0.5, 0.5, 0.5);
		narizNode = cabezaNode->createChildSceneNode("nariz");
		ent = mSM->createEntity("sphere.mesh");
		narizNode->attachObject(ent);
		narizNode->setPosition(75, 0, 75);
		narizNode->setScale(0.1, 0.1, 0.1);
		cabezaNode->setPosition(0, 145, 0);

		cuerpoNode = cuelloNode->createChildSceneNode("cuerpo");
		ent = mSM->createEntity("sphere.mesh");
		cuerpoNode->attachObject(ent);
		ombligoNode = cuerpoNode->createChildSceneNode("ombligo");
		ent = mSM->createEntity("sphere.mesh");
		ombligoNode->attachObject(ent);
		ombligoNode->setPosition(75, 0, 75);
		ombligoNode->setScale(0.1, 0.1, 0.1);
		cuerpoNode->setPosition(0, 0, 0);
	}

	~Monheco() {}

};

