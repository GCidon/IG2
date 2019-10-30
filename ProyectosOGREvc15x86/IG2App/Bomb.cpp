#include "Bomb.h"

Bomb::Bomb(Ogre::SceneNode* node, Ogre::Real dur) : EntityIG(node) {
	ent = mSM->createEntity("uv_sphere.mesh");
	mNode->attachObject(ent);
	ent->setMaterialName("bomb");

	duracion = dur;

	vaiven = mSM->createAnimation("vaiven", duracion);
	vaivenTrack = vaiven->createNodeTrack(0);
	vaivenTrack->setAssociatedNode(mNode);

	Ogre::Vector3 keyFramePos = Ogre::Vector3(0., 0., 200.);
	Ogre::Vector3 src = Ogre::Vector3(0, 0, 1);
	Ogre::Real durPaso = duracion/4.0;

	Ogre::TransformKeyFrame* kf;
	kf = vaivenTrack->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyFramePos);
	kf = vaivenTrack->createNodeKeyFrame(durPaso * 1);
	keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_Y * 40;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 1)));
	kf = vaivenTrack->createNodeKeyFrame(durPaso * 3);
	keyFramePos += Ogre::Vector3::UNIT_Y * 80;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1)));
	kf = vaivenTrack->createNodeKeyFrame(durPaso * 4);
	keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_Y * 40;
	kf->setTranslate(keyFramePos);

	vaivenState = mSM->createAnimationState("vaiven");
	vaivenState->setLoop(true);
	vaivenState->setEnabled(true);
}

void Bomb::frameRendered(const Ogre::FrameEvent& evt) {
	if(aux)
		vaivenState->addTime(evt.timeSinceLastFrame);
}

bool Bomb::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_b) {
		aux = !aux;
	}
	return true;
}