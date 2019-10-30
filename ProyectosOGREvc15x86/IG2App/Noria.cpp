#include "Noria.h"

Noria::Noria(Ogre::SceneNode* node, int n) : EntityIG(node), numAspas(n) {

	Ogre::Entity* ent;
	int incr = 360 / n;
	for (int i = 0; i <= n - 1; i++) {
		aspasNode.push_back(mNode->createChildSceneNode("paleta" + to_string(i)));
		aspas.push_back(new Aspa(aspasNode[i]));
		aspasNode[i]->roll(Ogre::Degree(incr * i));
		aspas[i]->roll(incr * i);
	}

	cilindro = mNode->createChildSceneNode("centro");
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("piedra");
	cilindro->attachObject(ent);
	cilindro->setScale(30, 30, 30);
	cilindro->pitch(Ogre::Degree(90));
}

Noria::~Noria() {
	for (auto& aspa : aspas)
	{
		delete aspa;
		aspa = nullptr;
	}
}

void Noria::frameRendered(const Ogre::FrameEvent& evt) {
	if (!parao)
		roll(1);
}

void Noria::receiveEvent(EntityIG* entidad) {
	parao = !parao;
}

void Noria::roll(int grado) {
	mNode->roll(Ogre::Degree(grado));
	for (auto& aspa : aspas)
	{
		aspa->roll(grado);
	}
	cilindro->yaw(Ogre::Degree(-grado));
}
