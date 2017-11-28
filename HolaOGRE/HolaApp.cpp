#include "HolaApp.h"

using namespace Ogre;

// ocultar el panel y poner luz ambiente
void HolaApp::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt){
	scnMgr->setAmbientLight(ColourValue(1, 1, 1));
	scnMgr->getEntity("eFondo")->setVisible(false);
};
// restablecer los cambios
void HolaApp::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt){
	scnMgr->setAmbientLight(ColourValue(0, 0, 0));
	scnMgr->getEntity("eFondo")->setVisible(true);
};

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

  camMan->setTarget(node);

  //PLANO
  //  Plane plane(Vector3::UNIT_Y, 0);
  MeshPtr plane = MeshManager::getSingleton().createPlane("mFondo",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  Plane(Vector3::UNIT_Z, 0),
	  (Real)mWindow->getViewport(0)->getActualWidth(),
	  (Real)cam->getViewport()->getActualHeight(),
	  10, 10, true, 1, 1.0, 1.0, Vector3::UNIT_Y);

  Entity* eFondo = scnMgr->createEntity("eFondo", "mFondo");

  //TEXTURA
  eFondo->getSubEntity(0)->getMaterial()->
	  getTechnique(0)->getPass(0) ->
	  createTextureUnitState("RustedMetal.jpg");
  Ogre::SceneNode* nodePlano = scnMgr->getRootSceneNode()->createChildSceneNode("nFondo");
  nodePlano->attachObject(eFondo);
 
  //Camara reflejo
  Camera* camRef = scnMgr->createCamera("RefCam");
  camRef->setNearClipDistance(cam->getNearClipDistance());
  camRef->setFarClipDistance(cam->getFarClipDistance());
  camRef->setAutoAspectRatio(cam->getAutoAspectRatio());

  camRef->enableReflection(Plane(Vector3::UNIT_Z, 0));
  camRef->enableCustomNearClipPlane(Plane(Vector3::UNIT_Z, 0));
  //se pone el nodo de la otra camara para que se sigan
  camNode->attachObject(camRef);

 //TEXTURA REFLEJO
 TexturePtr rttTex = TextureManager::getSingleton().createManual(
	 "texRtt",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	 TEX_TYPE_2D,
	 (Real)mWindow->getViewport(0)->getActualWidth(),
	 (Real)cam->getViewport()->getActualHeight(),
	 0, PF_R8G8B8, TU_RENDERTARGET);
 RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
 
 Viewport * v = renderTexture->addViewport(camRef);
 v->setClearEveryFrame(true);
 v->setBackgroundColour(ColourValue::Black);
 TextureUnitState* t = eFondo->getSubEntity(0)->getMaterial()->
	 getTechnique(0)->getPass(0)->
	 createTextureUnitState("texRtt");
 t->setColourOperation(LBO_ADD); // backgroundColour -> black
 // LBO_MODULATE / LBO_REPLACE / LBO_ALPHA_BLEND;
 t->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
 t->setProjectiveTexturing(true, camRef);
 renderTexture->addListener(this);
}

