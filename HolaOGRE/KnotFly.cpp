#include "KnotFly.h"

using namespace Ogre;

KnotFly::KnotFly(Ogre::SceneNode* scnMngr) : ObjectMan(scnMngr)
{
	ent = node->getCreator()->createEntity("Knot", "knot.mesh");
	ent->setMaterialName("Knot");
	ent->setQueryFlags(MY_QUERY_INTERACT);
	node->setScale(Vector3(0.012, 0.012, 0.012));
	setObjMan(ent);
	node->setPosition(0, 8 , 0);
}


KnotFly::~KnotFly()
{
}

void KnotFly::frameRendered(const Ogre::FrameEvent & evt)
{
	node->rotate(Quaternion(Degree(5), Vector3::UNIT_Y));
	//node->setPosition(sinbad->getPosition().x, sinbad->getPosition().y + 8, sinbad->getPosition().z);

}
