#include "Sinbad.h"


Sinbad::Sinbad(Ogre::SceneNode* node, Ogre::Real dur) : EntityIG(node) {
	ent = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(ent);
	mNode->setScale(50, 50, 50);
	mNode->setInitialState();
	mNode->setPosition(1000, 250, -1000);

	swordL = mSM->createEntity("Sword.mesh");
	swordR = mSM->createEntity("Sword.mesh");

	ent->attachObjectToBone("Handle.R", swordR);
	ent->attachObjectToBone("Sheath.L", swordL);

	bailar = ent->getAnimationState("Dance");
	bailar->setLoop(true);

	runBase = ent->getAnimationState("RunBase");
	runBase->setLoop(true);

	runTop = ent->getAnimationState("RunTop");
	runTop->setLoop(true);

	duracion = dur;
	animacionPatrulla();

}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_c && !muerto)
	{
		aux = !aux;
		ent->detachObjectFromBone(swordR);
		ent->detachObjectFromBone(swordL);
		if (aux) {
			ent->attachObjectToBone("Sheath.R", swordR);
			ent->attachObjectToBone("Sheath.L", swordL);
		}
		else {
			ent->attachObjectToBone("Handle.R", swordR);
			ent->attachObjectToBone("Sheath.L", swordL);
		}
	}
	if (evt.keysym.sym == SDLK_h)
	{
		ent->detachObjectFromBone(swordR);
		ent->detachObjectFromBone(swordL);
		ent->attachObjectToBone("Handle.R", swordR);
		ent->attachObjectToBone("Handle.L", swordL);
		sendEvent(this, Explosion);
	}

	return true;
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt) {
	if (aux) {
		runBase->setEnabled(false);
		runTop->setEnabled(false);
		bailar->setEnabled(true);
		vueltaState->setEnabled(false);
		bailar->addTime(evt.timeSinceLastFrame);
	}
	else {
		bailar->setEnabled(false);
		runBase->setEnabled(true);
		runTop->setEnabled(true);
		vueltaState->setEnabled(true);
		runBase->addTime(evt.timeSinceLastFrame);
		runTop->addTime(evt.timeSinceLastFrame);
		vueltaState->addTime(evt.timeSinceLastFrame);
		if (muerto && vueltaState->getTimePosition() > ((duracion / (1.5 * 2.0)) * 0.60)) {
			runBase->setEnabled(false);
			runTop->setEnabled(false);
		}
	}
}

void Sinbad::receiveEvent(EntityIG* entidad, int evento) {
	switch (evento)
	{
	case Explosion:
		if (!muerto) {
			vueltaState->setEnabled(false);
			animacionHaciaBomba();
			muerto = true;
		}
		break;
	default:
		break;
	}
}
void Sinbad::animacionPatrulla()
{
	vuelta = mSM->createAnimation("vuelta", duracion);
	vueltaTrack = vuelta->createNodeTrack(0);
	vueltaTrack->setAssociatedNode(mNode);

	Ogre::Vector3 keyFramePos = Ogre::Vector3(1000, 250, -1000);
	Ogre::Vector3 src = Ogre::Vector3(0, 0, 1);
	Ogre::Real durPaso = duracion / 5.0;

	Ogre::TransformKeyFrame* kf;

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyFramePos);

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 1);
	keyFramePos += Ogre::Vector3::UNIT_Z * 2000;
	kf->setTranslate(keyFramePos);

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 1.25);
	keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * 100;
	keyFramePos += Ogre::Vector3::UNIT_Z * 100;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 0)));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 2.25);
	keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * 2000;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 0)));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 2.5);
	keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_X * 100;
	keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_Z * 100;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, -1)));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 3.5);
	keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_Z * 2000;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, -1)));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 3.75);
	keyFramePos += Ogre::Vector3::UNIT_X * 100;
	keyFramePos += Ogre::Vector3::NEGATIVE_UNIT_Z * 100;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 0)));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 4.75);
	keyFramePos += Ogre::Vector3::UNIT_X * 2000;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 0)));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 5.0);
	keyFramePos += Ogre::Vector3::UNIT_X * 100;
	keyFramePos += Ogre::Vector3::UNIT_Z * 100;
	kf->setTranslate(keyFramePos);


	vueltaState = mSM->createAnimationState("vuelta");
	vueltaState->setLoop(true);
}

void Sinbad::animacionHaciaBomba() {
	vuelta = mSM->createAnimation("bomba", duracion/2.0);
	vueltaTrack = vuelta->createNodeTrack(0);
	vueltaTrack->setAssociatedNode(mNode);

	Ogre::Vector3 keyFramePos = mNode->getPosition();

	Ogre::Vector3 src = Ogre::Vector3(0., 0., 1.);
	Ogre::Real durPaso = duracion / (1.5*2.0);
	Ogre::Vector3 r = Ogre::Vector3(0., 250., 200.) - keyFramePos;

	Ogre::TransformKeyFrame* kf;

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(r));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 0.5);
	keyFramePos += (Ogre::Vector3(0., 250., 200.) - keyFramePos);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(r));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 0.55);
	keyFramePos += Ogre::Vector3(0., 300., 0.);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(r));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 0.60);
	keyFramePos -= Ogre::Vector3(0., 550., 0.);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(r));
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0., 1000., 0.)));

	kf = vueltaTrack->createNodeKeyFrame(durPaso * 1.5);
	keyFramePos += Ogre::Vector3(1000., 0., 0.);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(r));
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0., 1000., 0.)));

	vueltaState = mSM->createAnimationState("bomba");
	vueltaState->setLoop(false);

}
