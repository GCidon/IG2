#include "EntityIG.h"

std::vector<EntityIG*> EntityIG::appListeners = std::vector<EntityIG*>(0, nullptr);

EntityIG::EntityIG(Ogre::SceneNode* nodo) : mNode(nodo) {
	mSM = mNode->getCreator();
}

EntityIG::~EntityIG() {

}

void EntityIG::sendEvent(EntityIG* entidad, int evento) {
	for (EntityIG* e : appListeners)
		e->receiveEvent(this, evento);
}