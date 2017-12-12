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

	espada = node->getCreator()->createEntity("espada", "Sword.mesh");
	ent->attachObjectToBone("Handle.L", espada);
}


SinbadMan::~SinbadMan()
{
	delete ent; ent = nullptr;
	delete RunTopState; RunTopState = nullptr;
	delete RunBaseState; RunBaseState = nullptr;
	delete espada; espada= nullptr;
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

}