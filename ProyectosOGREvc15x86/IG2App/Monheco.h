#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <string>
#include "Aspa.h"
#include "EntityIG.h"
#include <math.h>
#include <vector>

using namespace std;

class Monheco :
	public EntityIG
{
protected:
	Ogre::SceneNode* cuelloNode;
	Ogre::SceneNode* cabezaNode;
	Ogre::SceneNode* cuerpoNode;
	Ogre::SceneNode* ombligoNode;
	Ogre::Entity* cabezaEnt;
	Ogre::Entity* cuerpoEnt;
	int rotacionCabeza;
	bool auxMov = false;
	bool auxNariz = false;
	bool parao = false;
	float angle = 0;

public:
	Monheco(Ogre::SceneNode* node) : EntityIG(node) {

		Ogre::Entity* ent;

		cuelloNode = mNode->createChildSceneNode("cuello");

		cabezaNode = cuelloNode->createChildSceneNode("cabeza");
		cabezaEnt = mSM->createEntity("sphere.mesh");
		cabezaEnt->setMaterialName("cara");
		cabezaNode->attachObject(cabezaEnt);
		cabezaNode->setScale(0.5, 0.5, 0.5);
		cabezaNode->setPosition(0, 145, 0);


		cuerpoNode = cuelloNode->createChildSceneNode("cuerpo");
		cuerpoEnt = mSM->createEntity("sphere.mesh");
		cuerpoEnt->setMaterialName("ajedrez");
		cuerpoNode->attachObject(cuerpoEnt);
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

	}

	virtual void receiveEvent(EntityIG* entidad) {
		cabezaEnt->setMaterialName("elplan");
		cuerpoEnt->setMaterialName("elplancuerpo");
	}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		double x = cos(angle * 3.1416 / 180);
		double z = -sin(angle * 3.1416 / 180);
		if (evt.keysym.sym == SDLK_q)
		{
			parao = !parao;
		}
		else if (evt.keysym.sym == SDLK_UP) 
		{
			cuelloNode->setPosition(cuelloNode->getPosition() + Ogre::Vector3(x, 0, z) * 10);
			cuerpoNode->roll(Ogre::Degree(-10), Ogre::Node::TS_LOCAL);
		}
		else if (evt.keysym.sym == SDLK_DOWN) 
		{
			cuelloNode->setPosition(cuelloNode->getPosition() + Ogre::Vector3(x, 0, z) * -10);
			cuerpoNode->roll(Ogre::Degree(10), Ogre::Node::TS_LOCAL);
		}
		else if (evt.keysym.sym == SDLK_LEFT) 
		{
			cuelloNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Degree(10));
			angle += 10;
		}
		else if (evt.keysym.sym == SDLK_RIGHT) 
		{
			angle += -10;
			cuelloNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Degree(-10));
		}
		else if (evt.keysym.sym == SDLK_r) 
		{
			sendEvent(this);
		}
		return true;
	}

	~Monheco() {}

};

