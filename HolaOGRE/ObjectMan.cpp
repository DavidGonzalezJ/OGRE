#include "ObjectMan.h"
using namespace Ogre;

ObjectMan::ObjectMan(Ogre::SceneNode* scnNode) : node(scnNode){
	control = new UserControl(this);
}

ObjectMan::~ObjectMan() {
	
	UserControl* pCtrl = any_cast<UserControl*>(node->getAttachedObject(0)->getUserObjectBindings().getUserAny());
	delete pCtrl;
}
void ObjectMan::setObjMan(MovableObject* mObj) {
	if (node->numChildren() == 0){
		node->attachObject(mObj);
		node->getAttachedObject(0)->getUserObjectBindings().setUserAny(Any(control));
	}
}