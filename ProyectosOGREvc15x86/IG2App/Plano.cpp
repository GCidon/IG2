#include "Plano.h"

using namespace Ogre;

//Le pasamos el TexturePtr por que el nWindow no lo tenemos aqui, si no en IG2App.cpp
Plano::Plano(Ogre::SceneNode* node, Camera* cam): EntityIG(node) {
	
	planoEnt = mSM->createEntity("mallaplano");

	TexturePtr rttRef = TextureManager::getSingleton().createManual("rttReflejo", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		(Real)cam->getViewport()->getActualWidth(),
		(Real)cam->getViewport()->getActualHeight(),
		0, PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
	Viewport* vpt = renderTexture->addViewport(mSM->getCamera("RefCam"));
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(ColourValue::White);

	planoEnt->setMaterialName("reflejo"); //Primero hay que darle el matrial antes de darle la textura del reflejo (rttReflejo)

	TextureUnitState* tu = planoEnt->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->
		createTextureUnitState("rttReflejo");
	tu->setColourOperation(LBO_MODULATE);

	tu->setProjectiveTexturing(true, mSM->getCamera("RefCam"));

	mpRef = new MovablePlane(Vector3(0, 1, 0), Vector3(0, 0, 0));
	mNode->attachObject(mpRef);

	mSM->getCamera("RefCam")->enableReflection(mpRef);
	mSM->getCamera("RefCam")->enableCustomNearClipPlane(mpRef);

	mNode->attachObject(planoEnt);
}

Plano::~Plano()
{
	delete mpRef;
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
