#include "SinbadMan.h"
#include <OgreTrays.h>
#include <Ogre.h>
using namespace Ogre;

SinbadMan::SinbadMan(Ogre::SceneNode* scnMngr) : ObjectMan(scnMngr)
{
	ent = node->getCreator()->createEntity("Sinbad", "Sinbad.mesh");
	ent->setQueryFlags(MY_QUERY_MASK);
	setObjMan(ent);
	RunTopState = ent->getAnimationState("RunTop");
	RunTopState->setLoop(true);
	RunTopState->setEnabled(true);

	RunBaseState = ent->getAnimationState("RunBase");
	RunBaseState->setLoop(true);
	RunBaseState->setEnabled(true);

	espada = node->getCreator()->createEntity("espada", "Sword.mesh");
	ent->attachObjectToBone("Handle.L", espada);

	Real duracion = 20;
	Animation * animation = node->getCreator()->createAnimation("animSinbad", duracion);
	NodeAnimationTrack * track = animation->createNodeTrack(0);
	track->setAssociatedNode(node->getCreator()->getSceneNode("nSinbadMan"));


	Vector3 keyframePos(0,0,0);
	Real tamDesplazamiento = 40;
	Real longitudPaso = duracion / 4.0;
	TransformKeyFrame * kf;; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
	kf = track->createNodeKeyFrame(longitudPaso * 0); // Keyframe 0: origen.
	kf->setTranslate(keyframePos); // Origen: Vector3

	kf = track->createNodeKeyFrame(longitudPaso * 1); // Keyframe 1: arriba.
	keyframePos += Ogre::Vector3::UNIT_Z * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Adelante

	kf = track->createNodeKeyFrame(longitudPaso * 2);
	kf->setRotation(Quaternion(Radian(Degree(0)), Vector3(0, 1, 0)));


	kf = track->createNodeKeyFrame(longitudPaso * 4); // Keyframe 2: arriba.
	keyframePos += Ogre::Vector3::UNIT_X * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Derecha
	kf = track->createNodeKeyFrame(longitudPaso * 5);
	kf->setRotation(Quaternion(Radian(Degree(90)), Vector3(0, 1, 0)));

	kf = track->createNodeKeyFrame(longitudPaso * 6); // Keyframe 3: atras.
	keyframePos -= Ogre::Vector3::UNIT_Z * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Atras

	kf = track->createNodeKeyFrame(longitudPaso * 7); // Keyframe : izquierda.
	keyframePos -= Ogre::Vector3::UNIT_X * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Izquierda

	animationState = node->getCreator()->createAnimationState("animSinbad");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}


SinbadMan::~SinbadMan()
{
	delete ent; ent = nullptr;
	delete RunTopState; RunTopState = nullptr;
	delete RunBaseState; RunBaseState = nullptr;
	delete espada; espada= nullptr;
}

bool SinbadMan::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_RIGHT:
		//sinbad->setPosition(sinbad->getPosition().x + 1, sinbad->getPosition().y, sinbad->getPosition().z);
		break;
	case SDLK_LEFT:
		//sinbad->setPosition(sinbad->getPosition().x - 1, sinbad->getPosition().y, sinbad->getPosition().z);
		break;
	case SDLK_UP:
		//sinbad->setPosition(sinbad->getPosition().x, sinbad->getPosition().y, sinbad->getPosition().z - 1);
		break;
	case SDLK_DOWN:
		//sinbad->setPosition(sinbad->getPosition().x, sinbad->getPosition().y, sinbad->getPosition().z + 1);
		break;
	case SDLK_ESCAPE:
		break;
	default:
		break;
	}
	
	return true;
}

bool SinbadMan::mousePressed(const OgreBites::MouseButtonEvent &  evt)
{
	
	return true;
}

bool SinbadMan::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
	//trayMgr->mouseMoved(evt);

	return true;
}
void SinbadMan::frameRendered(const Ogre::FrameEvent & evt) {
	RunBaseState->addTime(evt.timeSinceLastFrame);
	RunTopState->addTime(evt.timeSinceLastFrame);
	animationState->addTime(evt.timeSinceLastFrame);
}