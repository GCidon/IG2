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
	int rotacionCabeza;
	bool auxMov = false;
	bool auxNariz = false;
	bool parao = false;

public:
	Monheco(Ogre::SceneNode* node) : EntityIG(node) {

		Ogre::Entity* ent;

		cuelloNode = mNode->createChildSceneNode("cuello");

		cabezaNode = cuelloNode->createChildSceneNode("cabeza");
		ent = mSM->createEntity("sphere.mesh");
		ent->setMaterialName("carne");
		cabezaNode->attachObject(ent);
		cabezaNode->setScale(0.5, 0.5, 0.5);
		narizNode = cabezaNode->createChildSceneNode("nariz");
		ent = mSM->createEntity("sphere.mesh");
		ent->setMaterialName("nariz");
		narizNode->attachObject(ent);
		narizNode->setPosition(0, 0, 100);
		narizNode->setScale(0.1, 0.1, 0.1);
		cabezaNode->setPosition(0, 145, 0);


		cuerpoNode = cuelloNode->createChildSceneNode("cuerpo");
		ent = mSM->createEntity("sphere.mesh");
		ent->setMaterialName("carne");
		cuerpoNode->attachObject(ent);
		ombligoNode = cuerpoNode->createChildSceneNode("ombligo");
		ent = mSM->createEntity("sphere.mesh");
		ent->setMaterialName("ombligo");
		ombligoNode->attachObject(ent);
		ombligoNode->setPosition(100, 0, 0);
		ombligoNode->setScale(0.1, 0.1, 0.1);
		cuerpoNode->setPosition(0, 0, 0);
	}

	virtual void frameRendered(const Ogre::FrameEvent& evt) {
		if (!parao) {
			if (!auxMov) {
				cuelloNode->setPosition(cuelloNode->getPosition() + Ogre::Vector3(-3, 0, 0));
				cuerpoNode->roll(Ogre::Degree(3));
			}
			else {
				cuerpoNode->roll(Ogre::Degree(-3));
				cuelloNode->setPosition(cuelloNode->getPosition() + Ogre::Vector3(3, 0, 0));
			}
			if (cuelloNode->getPosition().x < -1500) auxMov = true;
			else if (cuelloNode->getPosition().x > 500) auxMov = false;
		}
		if (!auxNariz) {
			cabezaNode->yaw(Ogre::Degree(3));
			rotacionCabeza += 3;
		}
		else {
			cabezaNode->yaw(Ogre::Degree(-3));
			rotacionCabeza -= 3;
		}
		if (rotacionCabeza > 90) auxNariz = true;
		else if (rotacionCabeza < -90) auxNariz = false;

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

