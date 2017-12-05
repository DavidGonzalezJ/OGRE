#pragma once
#include <OgreTrays.h>
#include <Ogre.h>
class ObjectMan;

class UserControl
{
public:
	ObjectMan* getControl() { return object; };
	friend class ObjectMan;
protected:
	UserControl(ObjectMan * obj) : object(obj) { };
	~UserControl() { };
	ObjectMan* object; // ObjectMan: clase raíz de una jerarquía
};

class ObjectMan
{
public:
	ObjectMan(Ogre::SceneNode* scnNode);
	static const Ogre::uint32 MY_QUERY_MASK = 1; // << 0;

	virtual bool mousePicking(const OgreBites::MouseButtonEvent& evt)
	{
		return true;
	};
	virtual void frameRendered(const Ogre::FrameEvent & evt) { };
	virtual void setObjMan(Ogre::MovableObject* mObj);
	virtual ~ObjectMan();
protected:
	Ogre::SceneNode* node = nullptr;
	UserControl* control = nullptr;
//	Entity* ent = nullptr;
};