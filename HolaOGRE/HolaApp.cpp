#include "HolaApp.h"

using namespace Ogre;

void HolaApp::frameRendered(const FrameEvent &  evt)
{
  //trayMgr->frameRendered(evt);
}

bool HolaApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    mRoot->queueEndRendering();
  }
 
  return true;
}

bool HolaApp::mousePressed(const OgreBites::MouseButtonEvent &  evt)
{
  //if (trayMgr->mousePressed(evt)) return true;
  return true;
}

bool HolaApp::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
  //trayMgr->mouseMoved(evt);
  
  return true;
}

void HolaApp::setupInput()
{
  // do not forget to call the base first
  MyApplicationContext::setupInput(); 
  // register for input events
  addInputListener(this);
}

void HolaApp::shutdown()
{
  scnMgr->removeRenderQueueListener(mOverlaySystem);
  delete trayMgr;  trayMgr = nullptr;
  delete sinBadMgr; sinBadMgr = nullptr;
  // do not forget to call the base 
  MyApplicationContext::shutdown();
}

void HolaApp::setup(void)
{
  // do not forget to call the base first
  MyApplicationContext::setup();

  scnMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(scnMgr);

  scnMgr->addRenderQueueListener(mOverlaySystem);

  trayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow);
  trayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  //Añadimos el objeto a la lista de observdores
  addInputListener(trayMgr);

  setupScene();
}

void HolaApp::setupScene(void)
{
  // without light we would just get a black screen    
  Light* light = scnMgr->createLight("Light");
  light->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z); // !!! opngl <-> dirección a la fuente de luz
  lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  lightNode->setPosition(0, 0, 100);
  lightNode->attachObject(light);

  // also need to tell where we are
  camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->setPosition(0, 0, 100);
  camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_WORLD);

  // create the camera
  Camera* cam = scnMgr->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME);  // en material
  camNode->attachObject(cam);

  camMan = new OgreBites::CameraMan(camNode);
  camMan->setStyle(OgreBites::CS_ORBIT);
  addInputListener(camMan);


  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  //vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  // finally something to render
  Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
  Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
  //node->setPosition(0, 0, 25);
  node->scale(5, 5, 5);
  //node->showBoundingBox(true);
  //node->roll(Ogre::Degree(-45));
  node->attachObject(ent);
  sinBadMgr = new Sinbad(node);
  addInputListener(sinBadMgr);

  //SINBAD 2
  Ogre::Entity* ent1 = scnMgr->createEntity("Sinbad.mesh");
  Ogre::SceneNode* node1 = scnMgr->getRootSceneNode()->createChildSceneNode();
  node1->setPosition(0, 0, 25);
  node1->scale(5, 5, 5);

  //node->showBoundingBox(true);
  //node->roll(Ogre::Degree(-45));
  node1->attachObject(ent1);
  camMan->setTarget(node);

}

