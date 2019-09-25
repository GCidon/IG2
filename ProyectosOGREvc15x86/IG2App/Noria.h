#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <string>
#include "Aspa.h"
#include <vector>

using namespace std;

class Noria :
	public OgreBites::InputListener
{
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;
	std::vector<Ogre::SceneNode*> aspasNode;
	std::vector<Aspa*> aspas;
	Ogre::SceneNode* cilindro;

	int numAspas;

public:
	Noria(Ogre::SceneNode* node, int n) : mNode(node), numAspas(n) {
		mSM = mNode->getCreator();
		Ogre::Entity* ent;
		int incr = 360 / n;
		for (int i = 0; i <= n-1; i++) {
			aspasNode.push_back(mNode->createChildSceneNode("paleta" + to_string(i)));
			aspas.push_back(new Aspa(aspasNode[i]));
			aspasNode[i]->roll(Ogre::Degree(incr*i));
			aspas[i]->roll(incr*i);
		}

		cilindro = mNode->createChildSceneNode("centro");
		ent = mSM->createEntity("Barrel.mesh");
		cilindro->attachObject(ent);
		cilindro->setScale(30, 30, 30);
		cilindro->pitch(Ogre::Degree(90));
	}

	~Noria() {
		for (auto& aspa : aspas)
		{
			delete aspa;
			aspa = nullptr;
		}
	}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		if (evt.keysym.sym == SDLK_q) {
			roll(3);
		}
		return true;
	}

	void roll(int grado) {
		mNode->roll(Ogre::Degree(grado));
		for (auto &aspa:aspas)
		{
			aspa->roll(grado);
		}
		cilindro->yaw(Ogre::Degree(-grado));
		//cilindro->pitch(Ogre::Degree(grado));
	}

};

