#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include "EntityIG.h"
#include <string>

class Aspa :
	public EntityIG
{
protected:
	Ogre::SceneNode* aspa1;
	Ogre::SceneNode* aspa2;
	Ogre::SceneNode* cubo;

	int incrX = 0;

public:
	Aspa(Ogre::SceneNode* node) : EntityIG(node) {
		Ogre::Entity* ent;

		cubo = mNode->createChildSceneNode();
		ent = mSM->createEntity("cube.mesh");
		ent->setMaterialName("cabina");
		cubo->attachObject(ent);
		cubo->setPosition(700, 0, 0);
		cubo->setScale(1, 1, 1);

		aspa1 = mNode->createChildSceneNode();
		ent = mSM->createEntity("cube.mesh");
		ent->setMaterialName("aspa");
		aspa1->attachObject(ent);
		aspa1->setPosition(350, 0, 50);
		aspa1->setScale(7, 0.5, 0.1); 

		aspa2 = mNode->createChildSceneNode();
		ent = mSM->createEntity("cube.mesh");
		ent->setMaterialName("aspa");
		aspa2->attachObject(ent);
		aspa2->setPosition(350, 0, -50);
		aspa2->setScale(7, 0.5, 0.1);
	}
	~Aspa() {

	}

	void roll(int grado) {
		cubo->roll(Ogre::Degree(-grado));
	}

};

