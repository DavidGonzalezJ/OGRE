#pragma once
#include "OgreInput.h"
#include <Ogre.h>
#include "ObjectMan.h"

class KnotFly : public ObjectMan
{
public:
	KnotFly(Ogre::SceneNode* scnMngr);
	~KnotFly();
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	//virtual void frameRendered(const Ogre::FrameEvent & evt);
	Ogre::Vector3 posicion;
	Ogre::Entity* ent = nullptr;
	Ogre::Real grados = 0;
	Ogre::Node* sinbad = nullptr;
};

