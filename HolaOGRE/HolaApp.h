#ifndef __HolaApp_H__
#define __HolaApp_H__

#include "MyApplicationContext.h"
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "Sinbad.h"


class HolaApp :
	public MyApplicationContext, public OgreBites::InputListener, public Ogre::RenderTargetListener
{
public:
  explicit HolaApp() : MyApplicationContext("HolaApp") { };
  virtual ~HolaApp(){ };   // delete ... los elementos creado con m�todos factoria (create...) se destruyen autom�ticamente 
  
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupInput();
  virtual void setupScene();
  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
  virtual bool mousePressed(const OgreBites::MouseButtonEvent &  evt);
  virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
  virtual void frameRendered(const Ogre::FrameEvent &  evt);

  // ocultar el panel y poner luz ambiente
  virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
  // restablecer los cambios
  virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

  OgreBites::CameraMan* camMan = nullptr;
  Sinbad* sinBadMgr = nullptr;

  Ogre::SceneManager* scnMgr = nullptr;
  //Gestor de paneles
  OgreBites::TrayManager* trayMgr = nullptr;
  Ogre::SceneNode* lightNode = nullptr;
  Ogre::SceneNode* camNode = nullptr;
  Ogre::RaySceneQuery * rayScnQuery = nullptr;
  Ogre::Camera* cam = nullptr;

};


#endif
