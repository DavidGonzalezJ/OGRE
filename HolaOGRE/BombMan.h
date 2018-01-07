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
	enum Animaciones {
		EXPLOTADA, REPOSO
	};
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	virtual void interact(Ogre::String nombre);
	Animaciones estadoActual = REPOSO;
	Ogre::Entity* ent = nullptr;
	float grados = 0;
	Ogre::ParticleSystem* pSys = nullptr;
};

