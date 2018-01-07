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

	virtual bool mousePicking(const OgreBites::MouseButtonEvent& evt)
	{
		return true;
	};
	virtual void frameRendered(const Ogre::FrameEvent & evt) { };
	virtual void setObjMan(Ogre::MovableObject* mObj);
	virtual void interact(Ogre::String nombre) { };
	virtual ~ObjectMan();
	enum QueryFlags {
		MY_QUERY_IGNORE = 1 << 1,
		MY_QUERY_INTERACT = 1 << 0
	};
protected:
	Ogre::SceneNode* node = nullptr;
	UserControl* control = nullptr;
//	Entity* ent = nullptr;
};