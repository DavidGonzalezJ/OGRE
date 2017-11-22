#include "Sinbad.h"


Sinbad::Sinbad(Ogre::SceneNode* _sinbad): sinbad(_sinbad)
{
	posicion = sinbad->getPosition();
}


Sinbad::~Sinbad()
{
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_RIGHT:
		sinbad->setPosition(sinbad->getPosition().x + 1, sinbad->getPosition().y, sinbad->getPosition().z);
		break;
	case SDLK_LEFT:
		sinbad->setPosition(sinbad->getPosition().x - 1, sinbad->getPosition().y, sinbad->getPosition().z);
		break;
	case SDLK_UP:
		sinbad->setPosition(sinbad->getPosition().x, sinbad->getPosition().y, sinbad->getPosition().z - 1);
		break;
	case SDLK_DOWN:
		sinbad->setPosition(sinbad->getPosition().x, sinbad->getPosition().y, sinbad->getPosition().z + 1);
		break;
	case SDLK_ESCAPE:
		break;
	default:
		break;
	}
	
	return true;
}

bool Sinbad::mousePressed(const OgreBites::MouseButtonEvent &  evt)
{
	
	return true;
}

bool Sinbad::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
	//trayMgr->mouseMoved(evt);

	return true;
}