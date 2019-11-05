#pragma once

#include <Ogre.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <vector>

using namespace std;

enum Eventos{ Explosion, Parar };

class EntityIG : public OgreBites::InputListener {

public:
	EntityIG(Ogre::SceneNode* node);
	~EntityIG();

	static std::vector<EntityIG*> appListeners;
	static void addListener(EntityIG* entidad) {
		appListeners.push_back(entidad);
	}

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		return false;
	}

	virtual void frameRendered(const Ogre::FrameEvent& evt) {}

	void sendEvent(EntityIG* entidad, int evento);
	virtual void receiveEvent(EntityIG* entidad, int evento) {}

};

