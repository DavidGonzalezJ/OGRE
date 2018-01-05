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

	espadaL = node->getCreator()->createEntity("espadaL", "Sword.mesh");
	ent->attachObjectToBone("Handle.L", espadaL);

	espadaR = node->getCreator()->createEntity("espadaR", "Sword.mesh");
	ent->attachObjectToBone("Sheath.R", espadaR);


	Real duracion = 24;
	Animation * animation = node->getCreator()->createAnimation("animSinbad", duracion);
	NodeAnimationTrack * track = animation->createNodeTrack(0);
	track->setAssociatedNode(node->getCreator()->getSceneNode("nSinbadMan"));


	Real tamDesplazamiento = 40;
	node->setPosition(node->getPosition().x - tamDesplazamiento / 2,
		node->getPosition().y, node->getPosition().z - tamDesplazamiento / 2);
	Vector3 keyframePos(-20,0,-20);
	Real longitudPaso = 20 / 4.0;
	Real longitudPasoGiro = 4 / 4;
	Real pasoActual=0;
	TransformKeyFrame * kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
	
	kf = track->createNodeKeyFrame(pasoActual); // Keyframe 0: origen.
	kf->setTranslate(keyframePos); // Origen: Vector3

	pasoActual += longitudPaso;
	kf = track->createNodeKeyFrame(pasoActual); // Keyframe 1: arriba.
	keyframePos += Ogre::Vector3::UNIT_Z * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Adelante

	pasoActual += longitudPasoGiro;
	kf = track->createNodeKeyFrame(pasoActual);
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Adelante

	pasoActual += longitudPaso;
	kf = track->createNodeKeyFrame(pasoActual); // Keyframe 2: arriba.
	kf->setRotation(Quaternion(Degree(90), Vector3(0, 1, 0)));
	keyframePos += Ogre::Vector3::UNIT_X * tamDesplazamiento;
	kf->setTranslate(keyframePos); // Derecha

	pasoActual += longitudPasoGiro;
	kf = track->createNodeKeyFrame(pasoActual);
	kf->setRotation(Quaternion(Degree(180), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Derecha

	pasoActual += longitudPaso;
	kf = track->createNodeKeyFrame(pasoActual); // Keyframe 3: atras.
	keyframePos -= Ogre::Vector3::UNIT_Z * tamDesplazamiento;
	kf->setRotation(Quaternion(Degree(180), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Atras

	pasoActual += longitudPasoGiro;
	kf = track->createNodeKeyFrame(pasoActual); // Keyframe : izquierda.
	kf->setRotation(Quaternion(Degree(270), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Izquierda

	pasoActual += longitudPaso;
	kf = track->createNodeKeyFrame(pasoActual); // Keyframe 3: atras.
	keyframePos -= Ogre::Vector3::UNIT_X * tamDesplazamiento;
	kf->setRotation(Quaternion(Degree(270), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Atras

	pasoActual += longitudPasoGiro;
	kf = track->createNodeKeyFrame(pasoActual); // Keyframe : izquierda.
	kf->setRotation(Quaternion(Degree(360), Vector3(0, 1, 0)));
	kf->setTranslate(keyframePos); // Izquierda

	animationState = node->getCreator()->createAnimationState("animSinbad");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}


SinbadMan::~SinbadMan()
{
	delete ent; ent = nullptr;
	delete espadaL; espadaL = nullptr;
	delete espadaR; espadaR= nullptr;
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