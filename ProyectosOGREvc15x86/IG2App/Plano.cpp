#include "Plano.h"

Plano::Plano(Ogre::SceneNode* node) : EntityIG(node) {
	planoEnt = mSM->createEntity("mallaplano");
	planoEnt->setMaterialName("reflejo");
	planoEnt->getSubEntities()[0]->getMaterial()->
		getTechniques()[0]->getPasses()[0]->
		createTextureUnitState("tusk.jpg");
	mNode->attachObject(planoEnt);
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_p) {
		mNode->yaw(Ogre::Degree(3));
	}
	return true;
}

void Plano::receiveEvent(EntityIG* entidad) {
	planoEnt->setMaterialName("reflejo");
}
