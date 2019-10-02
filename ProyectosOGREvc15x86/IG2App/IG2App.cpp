#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <string>

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_w) {

	  //rotatecabeza();
	  //rotateroll("clockNode");
	  //rotateposition("clockNode");
  }
  else if (evt.keysym.sym == SDLK_q) {
	  //avance();
  }
  else if (evt.keysym.sym == SDLK_e) {
	  //retroceso();
  }
  
  return true;
}

void IG2App::shutdown()
{
	delete noria;
	delete monheco;

  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  //vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(1.0, 1.0, 1.0);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(-0.5, -0.75, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);

  //------------------------------------------------------------------------

  // finally something to render

  scene4();

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------


}

void IG2App::rotateroll(string node) {
	mSM->getSceneNode(node)->roll(Ogre::Degree(-3));
	for (int i = 0; i <= 11; i++) {
		mSM->getSceneNode("cubo_" + to_string(i))->roll(Ogre::Degree(3));
	}
}

void IG2App::rotateposition(string node) {
	int ini = 90;
	int incr = 360 / 12;
	for (int i = 0; i <= 11; i++) {
		//mSM->getSceneNode("cubo_" + to_string(i))->setPosition(mSM->getSceneNode("cubo_" + to_string(i))->getPosition().x + 1, mSM->getSceneNode("cubo_" + to_string(i))->getPosition().y + 1, 0);
		mSM->getSceneNode("cubo_" + to_string(i))->setPosition(Ogre::Math::Cos(Ogre::Degree(ini + incr * i - incrX)) * 300 , Ogre::Math::Sin(Ogre::Degree(ini + incr * i - incrX)) * 300, 0);
	}
	incrX++;
}

void IG2App::rotatecabeza() {
	mSM->getSceneNode("cabeza")->yaw(Ogre::Degree(2));
}

void IG2App::avance() {
	mSM->getSceneNode("monheco")->setPosition(incrX, 0, incrX);
	incrX++;

	mSM->getSceneNode("cuerpo")->rotate(Vector3(1, 0, -1), Ogre::Degree(2));
}

void IG2App::retroceso() {
	mSM->getSceneNode("monheco")->setPosition(incrX, 0, incrX);
	incrX--;

	mSM->getSceneNode("cuerpo")->rotate(Vector3(1, 0, -1), Ogre::Degree(-2));
}

void IG2App::scene1() {
	clockNode = mSM->getRootSceneNode()->createChildSceneNode("clockNode");
	knotNode = mSM->getRootSceneNode()->createChildSceneNode("knotNode");

	Ogre::Entity* ent;
	Ogre::Entity* nudo;
	int ini = 90;
	int incr = 360 / 12;

	for (int i = 0; i <= 11; i++) {
		aspasNode[i] = clockNode->createChildSceneNode("cubo_" + to_string(i));
		ent = mSM->createEntity("cube.mesh");
		aspasNode[i]->attachObject(ent);
		if (i % 2 == 0)
			mSM->getSceneNode("cubo_" + to_string(i))->setScale(0.5, 0.5, 0.5);
		aspasNode[i]->setPosition(Ogre::Math::Cos(Ogre::Degree(ini + incr * i)) * 300, Ogre::Math::Sin(Ogre::Degree(ini + incr * i)) * 300, 0);
	}
	nudo = mSM->createEntity("knot.mesh");
	knotNode->attachObject(nudo);
	knotNode->setScale(1, 1, 1);
	clockNode->setScale(1, 1, 1);

	//clockNode->yaw(Ogre::Degree(-90));
	clockNode->showBoundingBox(true);
	knotNode->showBoundingBox(true);
	//clockNode->setVisible(false);
}
void IG2App::scene2() {
	clockNode = mSM->getRootSceneNode()->createChildSceneNode("clockNode");
	Ogre::Entity* ent;
	int ini = 90;
	int incr = 360 / 12;
	for (int i = 0; i <= 11; i++) {
		aspasNode[i] = clockNode->createChildSceneNode("cubo_" + to_string(i));
		ent = mSM->createEntity("cube.mesh");
		aspasNode[i]->attachObject(ent);
		aspasNode[i]->setPosition(Ogre::Math::Cos(Ogre::Degree(ini + incr * i)) * 300, Ogre::Math::Sin(Ogre::Degree(ini + incr * i)) * 300, 0);
		
		aspasNode[i] = clockNode->createChildSceneNode("aspa1_" + to_string(i));
		ent = mSM->createEntity("cube.mesh");
		aspasNode[i]->attachObject(ent);
		aspasNode[i]->setPosition(Ogre::Math::Cos(Ogre::Degree(ini + incr * i)) * 150, Ogre::Math::Sin(Ogre::Degree(ini + incr * i)) * 150, 50);
		aspasNode[i]->roll(Ogre::Degree(ini + incr * i));
		aspasNode[i]->setScale(3, 0.5, 0.1);

		aspasNode[i] = clockNode->createChildSceneNode("aspa2_" + to_string(i));
		ent = mSM->createEntity("cube.mesh");
		aspasNode[i]->attachObject(ent);
		aspasNode[i]->setPosition(Ogre::Math::Cos(Ogre::Degree(ini + incr * i)) * 150, Ogre::Math::Sin(Ogre::Degree(ini + incr * i)) * 150, -50);
		aspasNode[i]->roll(Ogre::Degree(ini + incr * i));
		aspasNode[i]->setScale(3, 0.5, 0.1);
	}

	clockNode->setScale(1, 1, 1);
	clockNode->showBoundingBox(true);
}
void IG2App::scene3() {
	monhecoNode = mSM->getRootSceneNode()->createChildSceneNode("monheco");
	Ogre::Entity* ent;

	cabezaNode = monhecoNode->createChildSceneNode("cabeza");
	ent = mSM->createEntity("sphere.mesh");
	cabezaNode->attachObject(ent);
	cabezaNode->setScale(0.5, 0.5, 0.5);
	narizNode = cabezaNode->createChildSceneNode("nariz");
	ent = mSM->createEntity("sphere.mesh");
	narizNode->attachObject(ent);
	narizNode->setPosition(75, 0, 75);
	narizNode->setScale(0.1, 0.1, 0.1);
	cabezaNode->setPosition(0, 145, 0);

	cuerpoNode = monhecoNode->createChildSceneNode("cuerpo");
	ent = mSM->createEntity("sphere.mesh"); 
	cuerpoNode->attachObject(ent);
	ombligoNode = cuerpoNode->createChildSceneNode("ombligo");
	ent = mSM->createEntity("sphere.mesh");
	ombligoNode->attachObject(ent);
	ombligoNode->setPosition(75, 0, 75);
	ombligoNode->setScale(0.1, 0.1, 0.1);
	cuerpoNode->setPosition(0, 0, 0);
	
}

void IG2App::scene4() {
	MeshManager::getSingleton().createPlane("mallaplano",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		3000, 3000, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	planoNode = mSM->getRootSceneNode()->createChildSceneNode("plano");
	plano = new Plano(planoNode);
	addInputListener(plano);

	noriaNode = planoNode->createChildSceneNode("noria");
	noria = new Noria(noriaNode, 13);
	addInputListener(noria);
	
	monhecoNode = planoNode->createChildSceneNode("monheco");
	monheco = new Monheco(monhecoNode);
	monhecoNode->setPosition(500, 80, 500);
	addInputListener(monheco);

}


