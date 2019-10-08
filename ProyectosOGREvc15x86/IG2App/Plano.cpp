#include "Plano.h"

Plano::Plano(Ogre::SceneNode* node) : EntityIG(node) {
	planoEnt = mSM->createEntity("mallaplano");
	planoEnt->setMaterialName("water");
	mNode->attachObject(planoEnt);
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_p) {
		mNode->yaw(Ogre::Degree(3));
	}
	return true;
}

void Plano::receiveEvent(EntityIG* entidad) {
	planoEnt->setMaterialName("aguaparao");
}
