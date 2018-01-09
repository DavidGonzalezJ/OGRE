#include "SinbadMan.h"
#include <OgreTrays.h>
#include <Ogre.h>
#include <iostream>

using namespace Ogre;

SinbadMan::SinbadMan(Ogre::SceneNode* scnMngr) : ObjectMan(scnMngr)
{
	ent = node->getCreator()->createEntity("Sinbad", "Sinbad.mesh");
	ent->setQueryFlags(MY_QUERY_INTERACT);
	setObjMan(ent);

	RunTopState = ent->getAnimationState("RunTop");
	RunTopState->setLoop(true);
	RunTopState->setEnabled(true);

	RunBaseState = ent->getAnimationState("RunBase");
	RunBaseState->setLoop(true);
	RunBaseState->setEnabled(true);

	SwordState = ent->getAnimationState("DrawSwords");
	SwordState->setLoop(true);
	SwordState->setEnabled(false);

	espadaL = node->getCreator()->createEntity("espadaL", "Sword.mesh");
	ent->attachObjectToBone("Handle.L", espadaL);

	espadaR = node->getCreator()->createEntity("espadaR", "Sword.mesh");
	ent->attachObjectToBone("Sheath.R", espadaR);

	//ANIMACION CUADRADO
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
	if (estadoActual==CORRER) {
		RunBaseState->addTime(evt.timeSinceLastFrame);
		RunTopState->addTime(evt.timeSinceLastFrame);
		animationState->addTime(evt.timeSinceLastFrame);
	}
	else if (estadoActual == BOMBA) {
		if (!animationStateBomb->hasEnded()) {
			SwordState->addTime(evt.timeSinceLastFrame);
			RunBaseState->addTime(evt.timeSinceLastFrame);
			RunTopState->addTime(evt.timeSinceLastFrame);
			animationStateBomb->addTime(evt.timeSinceLastFrame);
		}
		else {
			RunBaseState->setEnabled(false);
			RunTopState->setEnabled(false);
			animationStateBomb->setEnabled(false);
			estadoActual = MUERTO;
			node->pitch(Degree(-90));
			node->translate(Vector3(0, -4, 0));
		}
	}
	else if (estadoActual == MUERTO) {
		node->translate(Vector3(0, 0, -0.03));
	}
}

void SinbadMan::interact(const Ogre::String nombre)
{
	//Parar o empezar a correr en el cuadrado
	if (nombre == "Sinbad" && estadoActual != BOMBA && estadoActual!=MUERTO) {
		estadoActual = (estadoActual == PARAR) ? CORRER : PARAR;
		bool toggle = !animationState->getEnabled();
		RunBaseState->setEnabled(toggle);
		RunTopState->setEnabled(toggle);
		animationState->setEnabled(toggle);
	}
	//Ir a la bomba
	else if (nombre == "eBomb") {
		estadoActual = BOMBA;
		ent->detachObjectFromBone(espadaR);
		ent->attachObjectToBone("Handle.R", espadaR);
		animationState->setEnabled(false);
		SwordState->setEnabled(true);
		
		Quaternion antes = node->getOrientation();
		node->lookAt(Vector3(node->getCreator()->getSceneNode("nBomb")->getPosition().x, node->getPosition().y, node->getCreator()->getSceneNode("nBomb")->getPosition().z),
			Node::TS_WORLD
			);
		node->rotate(Quaternion(Degree(180),Vector3::UNIT_Y));
		Quaternion despues = node->getOrientation();

		node->setOrientation(antes);
		//ANIMACION BOMBA
		Real duracion = 8;
		Animation * animationBomb = node->getCreator()->createAnimation("animSinbadBomb", duracion);
		NodeAnimationTrack * track = animationBomb->createNodeTrack(0);
		track->setAssociatedNode(node->getCreator()->getSceneNode("nSinbadMan"));

		Vector3 keyframePos(node->getPosition());
		TransformKeyFrame * kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)

		kf = track->createNodeKeyFrame(0); // Keyframe 0: origen.
		kf->setRotation(antes);
		kf->setTranslate(node->getPosition()); // Origen: Vector3

		kf = track->createNodeKeyFrame(duracion/2); // Keyframe 0: origen.
		
		Vector3 mDirection = node->getCreator()->getSceneNode("nBomb")->getPosition()-node->getPosition();

		Ogre::Vector3 src = node->getOrientation() * Ogre::Vector3::UNIT_X;
		Ogre::Quaternion quat = src.getRotationTo(mDirection,node->getOrientation().yAxis());
		kf->setRotation(despues);
		kf->setTranslate(node->getPosition()); // Origen: Vector3

		kf = track->createNodeKeyFrame(duracion); // Keyframe 0: origen.
		kf->setRotation(node->getOrientation());
		kf->setRotation(despues);
		kf->setTranslate(Vector3(node->getCreator()->getSceneNode("nBomb")->getPosition())); // Origen: Vector3

		animationStateBomb = node->getCreator()->createAnimationState("animSinbadBomb");
		animationStateBomb->setLoop(false);
		animationStateBomb->setEnabled(true);
		
	}
}
