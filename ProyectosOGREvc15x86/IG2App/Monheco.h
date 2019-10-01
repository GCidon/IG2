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

class Monheco :
	public EntityIG
{
protected:
	Ogre::SceneNode* cuelloNode;
	Ogre::SceneNode* cabezaNode;
	Ogre::SceneNode* cuerpoNode;
	Ogre::SceneNode* narizNode;
	Ogre::SceneNode* ombligoNode;

	bool auxMov = false;
	bool auxNariz = false;
	bool parao = false;

public:
	Monheco(Ogre::SceneNode* node) : EntityIG(node) {

		Ogre::Entity* ent;

		cuelloNode = mNode->createChildSceneNode("cuello");

		cabezaNode = cuelloNode->createChildSceneNode("cabeza");
		ent = mSM->createEntity("sphere.mesh");
		cabezaNode->attachObject(ent);
		cabezaNode->setScale(0.5, 0.5, 0.5);
		narizNode = cabezaNode->createChildSceneNode("nariz");
		ent = mSM->createEntity("sphere.mesh");
		narizNode->attachObject(ent);
		narizNode->setPosition(0, 0, 100);
		narizNode->setScale(0.1, 0.1, 0.1);
		cabezaNode->setPosition(0, 145, 0);

		cuerpoNode = cuelloNode->createChildSceneNode("cuerpo");
		ent = mSM->createEntity("sphere.mesh");
		cuerpoNode->attachObject(ent);
		ombligoNode = cuerpoNode->createChildSceneNode("ombligo");
		ent = mSM->createEntity("sphere.mesh");
		ombligoNode->attachObject(ent);
		ombligoNode->setPosition(0, 0, 100);
		ombligoNode->setScale(0.1, 0.1, 0.1);
		cuerpoNode->setPosition(0, 0, 0);
	}

	virtual void frameRendered(const Ogre::FrameEvent& evt) {
		if (!parao) {
			if (!auxMov) {
				cuelloNode->setPosition(cuelloNode->getPosition() + Ogre::Vector3(-3, 0, 0));
			}
			else {
				cuelloNode->setPosition(cuelloNode->getPosition() + Ogre::Vector3(3, 0, 0));
			}
			if (cuelloNode->getPosition().x < -1500) auxMov = true;
			else if (cuelloNode->getPosition().x > 500) auxMov = false;
		}
	}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		if (evt.keysym.sym == SDLK_q)
		{
			parao = !parao;
		}
		return true;
	}

	~Monheco() {}

};

