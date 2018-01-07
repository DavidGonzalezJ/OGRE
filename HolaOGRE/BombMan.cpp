#include "BombMan.h"
using namespace Ogre;


BombMan::BombMan(Ogre::SceneNode* scnMngr) : ObjectMan(scnMngr)
{
	ent = node->getCreator()->createEntity("eBomb", "uv_sphere.mesh");
	ent->setMaterialName("Bomb");
	node->setScale(Vector3(0.012, 0.012, 0.012));
	ent->setQueryFlags(MY_QUERY_INTERACT);
	setObjMan(ent);

	pSys = node->getCreator()->createParticleSystem("parSys", "Smoke");
	
	node->attachObject(pSys);
	pSys->setEmitting(false);
}


BombMan::~BombMan()
{
}
void BombMan::frameRendered(const Ogre::FrameEvent & evt)
{
	grados += 0.1;
	node->setPosition(node->getPosition().x,node->getPosition().y + 0.1*sin(grados),
		node->getPosition().z);
	pSys->getEmitter(0)->setPosition(node->getPosition());
}

void BombMan::interact(Ogre::String nombre)
{
	if (nombre == "eBomb" && estadoActual != EXPLOTADA) {
		estadoActual = EXPLOTADA;
		pSys->setEmitting(true);
	}
}

