#include "Plano.h"

Plano::Plano(Ogre::SceneNode* node) : EntityIG(node) {
	Ogre::Entity* ent = mSM->createEntity("mallaplano");
	mNode->attachObject(ent);
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_p) {
		mNode->yaw(Ogre::Degree(3));
	}
	return true;
}
