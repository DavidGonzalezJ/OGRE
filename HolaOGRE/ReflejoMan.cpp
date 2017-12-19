#include "ReflejoMan.h"

using namespace Ogre;

ReflejoMan::ReflejoMan(Ogre::SceneNode* scnMngr) : ObjectMan(scnMngr)
{
	//PLANO
	MeshPtr plane = MeshManager::getSingleton().createPlane("mFondo",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, -5), (Real)node->getCreator()->getCamera("Cam")->getViewport()->getActualWidth(),
		(Real)node->getCreator()->getCamera("Cam")->getViewport()->getActualHeight(),
		10, 10, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	Entity* eFondo = node->getCreator()->createEntity("eFondo", "mFondo");
	eFondo->setQueryFlags(0);

	//TEXTURA
	eFondo->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0) ->
		createTextureUnitState("RustedMetal.jpg");
	Ogre::SceneNode* nodePlano = node->getCreator()->getRootSceneNode()->createChildSceneNode("nFondo");
	nodePlano->attachObject(eFondo);

	//Camara reflejo
	Camera* camRef = node->getCreator()->createCamera("RefCam");
	camRef->setNearClipDistance(node->getCreator()->getCamera("Cam")->getNearClipDistance());
	camRef->setFarClipDistance(node->getCreator()->getCamera("Cam")->getFarClipDistance());
	camRef->setAutoAspectRatio(node->getCreator()->getCamera("Cam")->getAutoAspectRatio());

	camRef->enableReflection(Plane(Vector3::UNIT_Y, -5));
	camRef->enableCustomNearClipPlane(Plane(Vector3::UNIT_Y, -5));
	//se pone el nodo de la otra camara para que se sigan
	node->getCreator()->getCamera("Cam")->getParentSceneNode()->attachObject(camRef);

	
	//TEXTURA REFLEJO
	TexturePtr rttTex = TextureManager::getSingleton().createManual(
		"texRtt",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		(Real)node->getCreator()->getCamera("Cam")->getViewport()->getActualWidth(),
		(Real)node->getCreator()->getCamera("Cam")->getViewport()->getActualHeight(),
		0, PF_R8G8B8, TU_RENDERTARGET);
	
	renderTexture = rttTex->getBuffer()->getRenderTarget();

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


ReflejoMan::~ReflejoMan()
{
	renderTexture->removeListener(this); // en la destructora
	delete renderTexture;
	renderTexture = nullptr;
}
