#include "HolaApp.h"
#include <iostream>
using namespace Ogre;
enum QueryFlags {
	MY_QUERY_IGNORE = 1 << 1,
	MY_QUERY_INTERACT = 1 << 0
};
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
	for (int i = 0; i < vecObjMan.size(); ++i){
		vecObjMan[i]->frameRendered(evt);
	}
}

bool HolaApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    mRoot->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_t) {
	  if (camMan->getTarget()->getName() != "nSinbadMan")
		  camMan->setTarget(scnMgr->getSceneNode("nSinbadMan"));
	  else
		  camMan->setTarget(scnMgr->getRootSceneNode());

  }
 
  return true;
}

bool HolaApp::mousePressed(const OgreBites::MouseButtonEvent & evt)
{
	///Rayo donde haces click con el raton
	rayScnQuery->setRay(cam->getCameraToViewportRay(
		evt.x / (Real)mWindow->getViewport(0)->getActualWidth(),
		evt.y / (Real)mWindow->getViewport(0)->getActualHeight()));
	
	rayScnQuery->setSortByDistance(true);
	//Mascara se aplica
	rayScnQuery->setQueryMask(MY_QUERY_INTERACT);
	// coordenadas normalizadas en [0,1]
	RaySceneQueryResult& qryResult = rayScnQuery->execute();
	RaySceneQueryResult::iterator it = qryResult.begin();
	//BIEN

	while (it != qryResult.end()) {
		std::cout << "click" << it->movable->getName() << std::endl;
		//LISTENER
		for each (ObjectMan* var in vecObjMan)
		{
			var->interact(it->movable->getName());
		}
		//it->movable->getParentSceneNode()->translate(10, 10, 10);
		++it;
	//UserControl* pCtrl = any_cast<UserControl*>(it->movable->getUserObjectBindings().getUserAny());
	//pCtrl->getControl()->mousePicking(evt);
	}
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
  scnMgr->destroyQuery(rayScnQuery);

  //delete sinBadMgr; sinBadMgr = nullptr;
  /*for (int i = 0; i < vecObjMan.size(); ++i) {
	  delete vecObjMan[i];
  }*/
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

  Light* spotLight = scnMgr->createLight("SpotLight");
  spotLight->setDiffuseColour(0, 0, 1.0);
  spotLight->setSpecularColour(0, 0, 1.0);
  spotLight->setType(Light::LT_SPOTLIGHT);
  spotLight->setDirection(Vector3::NEGATIVE_UNIT_Z);
  SceneNode* spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  spotLightNode->attachObject(spotLight);
  spotLightNode->setDirection(-1, -1, 0);
  spotLightNode->setPosition(Vector3(200, 200, 0));
  spotLight->setSpotlightRange(Degree(60), Degree(100));


  // also need to tell where we are
  camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->setPosition(0, 0, 100);
  camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_WORLD);

  // create the camera
  cam = scnMgr->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME);  // en material
  camNode->attachObject(cam);
  cam->setQueryFlags(MY_QUERY_IGNORE);
  
  camMan = new OgreBites::CameraMan(camNode);
  camMan->setStyle(OgreBites::CS_ORBIT);
  addInputListener(camMan);


  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  //vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  Ogre::SceneNode* nodeSinbad = scnMgr->getRootSceneNode()->createChildSceneNode("nSinbadMan");
  sinBadMgr = new SinbadMan(nodeSinbad);
  vecObjMan.push_back(sinBadMgr);
  addInputListener(sinBadMgr);

  //Mosca
  Ogre::SceneNode* nodeKnot = nodeSinbad->createChildSceneNode("nKnot");
  knotMgr = new KnotFly(nodeKnot);
  vecObjMan.push_back(knotMgr);

  //Bomba
  Ogre::SceneNode* nodeBomb = scnMgr->getRootSceneNode()->createChildSceneNode("nBomb");
  bombMgr = new BombMan(nodeBomb);
  vecObjMan.push_back(bombMgr);

  //Plano
  Ogre::SceneNode* nodePlane = scnMgr->getRootSceneNode()->createChildSceneNode("nPlane");
  planeMgr = new ReflejoMan(nodeSinbad);
  vecObjMan.push_back(planeMgr);
  //RAYO
  rayScnQuery = scnMgr->createRayQuery(Ray(), MY_QUERY_INTERACT);
  //SKYPLANE
  scnMgr->setSkyPlane(true, Plane(Vector3::UNIT_Z, -20), "mandelbrot1", 1000, 1, true, 0.0, 100, 100);
  // enable, plane, materialName, scale = 1000, tiling = 10, drawFirst,
  // bow = 0, xsegments = 1, ysegments = 1,...
  // RenderQueueGroup->RENDER_QUEUE_SKIES_EARLY

  // scnMgr->setSkyBox(true, "Mandelbrot", );
  // scnMgr->setSkyDome(true, "Mandelbrot", ); 
}