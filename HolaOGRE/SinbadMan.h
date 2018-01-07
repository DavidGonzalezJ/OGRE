#pragma once
#include "OgreInput.h"
#include <Ogre.h>
#include "ObjectMan.h"
enum Animaciones {
	BOMBA, CORRER, PARAR, MUERTO
};
class SinbadMan : public ObjectMan,
	public OgreBites::InputListener
{
public:
	SinbadMan(Ogre::SceneNode* scnMngr);
	~SinbadMan();
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool mousePressed(const OgreBites::MouseButtonEvent &  evt);
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	virtual void interact(const Ogre::String nombre);
	//virtual void frameRendered(const Ogre::FrameEvent & evt);
	Ogre::Vector3 posicion;
	Ogre::Entity* ent = nullptr;
	Ogre::AnimationState* RunTopState = nullptr;
	Ogre::AnimationState* RunBaseState = nullptr;
	Ogre::MovableObject* espadaR = nullptr;
	Ogre::MovableObject* espadaL = nullptr;
	Ogre::AnimationState* animationState = nullptr;
	Ogre::AnimationState* animationStateBomb = nullptr;

	
	bool stopAnim = false;
	Animaciones estadoActual = CORRER;

};