#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <string>
#include "Aspa.h"

using namespace std;

class Noria :
	public OgreBites::InputListener
{
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	Ogre::SceneNode* aspasNode[12];
	Aspa* aspas[12];
	Ogre::SceneNode* cilindro;

public:
	Noria(Ogre::SceneNode* node) : mNode(node) {
		mSM = mNode->getCreator();
		Ogre::Entity* ent;

		int ini = 90;
		int incr = 360 / 12;
		for (int i = 0; i <= 11; i++) {
			aspasNode[i] = mNode->createChildSceneNode("paleta" + to_string(i));
			aspas[i] = new Aspa(aspasNode[i]);
			aspasNode[i]->setPosition(100, 0, 0);
			aspasNode[i]->roll(Ogre::Degree(incr*i));
			aspas[i]->roll(incr*i);
			
		}

		cilindro = mNode->createChildSceneNode("centro");
		ent = mSM->createEntity("fish.mesh");
		cilindro->attachObject(ent);
	}
	~Noria() {}

};

