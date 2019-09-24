#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "Aspa.h"
#include "Noria.h"

using namespace std;


class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();
  void scene1();
  void scene2();
  void scene3();
  void scene4();
  void rotateroll(string node);
  void rotateposition(string node);
  void rotatecabeza();
  void avance();
  void retroceso();

  int incrX = 0;

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* clockNode = nullptr;
  Ogre::SceneNode* knotNode = nullptr;
  Ogre::SceneNode* aspasNode[12];
  OgreBites::CameraMan* mCamMgr = nullptr;

  Ogre::SceneNode* monhecoNode = nullptr;
  Ogre::SceneNode* cabezaNode = nullptr;
  Ogre::SceneNode* cuerpoNode = nullptr;
  Ogre::SceneNode* narizNode = nullptr;
  Ogre::SceneNode* ombligoNode = nullptr;


 
};

#endif
