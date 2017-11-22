#pragma once
#include "OgreInput.h"
#include <Ogre.h>

class Sinbad :
	public OgreBites::InputListener
{
public:
	Sinbad(Ogre::SceneNode* _sinbad);
	~Sinbad();
	Ogre::SceneNode* sinbad = nullptr;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool mousePressed(const OgreBites::MouseButtonEvent &  evt);
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
	//virtual void frameRendered(const Ogre::FrameEvent &  evt);
	Ogre::Vector3 posicion;
};

