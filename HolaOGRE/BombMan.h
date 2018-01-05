#pragma once
#include "OgreInput.h"
#include <Ogre.h>
#include "ObjectMan.h"

class BombMan :
	public ObjectMan
{
public:
	BombMan(Ogre::SceneNode* scnMngr);
	~BombMan();
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	Ogre::Entity* ent = nullptr;
	float grados = 0;
};

