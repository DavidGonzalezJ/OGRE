#pragma once

#include <Ogre.h>
#include "ObjectMan.h"

class ReflejoMan: public ObjectMan,
	public Ogre::RenderTargetListener
{
public:
	ReflejoMan(Ogre::SceneNode* scnMngr);
	~ReflejoMan();
	Ogre::RenderTexture* renderTexture = nullptr;
};

