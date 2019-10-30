#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* node) : EntityIG(node) {
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

void Aspa::roll(int grado) {
	cubo->roll(Ogre::Degree(-grado));
}
