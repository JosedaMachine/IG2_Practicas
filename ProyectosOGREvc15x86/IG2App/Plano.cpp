#include "Plano.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>


Plano::Plano(Ogre::SceneNode* mNode_, std::string const& name, std::pair<int, int> size, std::pair<int, int> cuts, Vector3 normal_): EntityIG(mNode_) {
	normal = normal_;
	size_ = size;
	Ogre::MeshPtr ptr =MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(normal, 0), size.first, size.second, cuts.first, cuts.second, true,
		1, 1.0, 1.0, Vector3::UNIT_Z);

	plano = mSM->createEntity(name);

	mNode->attachObject(plano);


	timer = Ogre::Timer();
	timer.reset();
}

void Plano::setEspejo(Camera* cam){
	


}

void Plano::setReflejo(Camera* camRef, Ogre::Real distance){
	mpRef = new MovablePlane(-1 * normal, distance);

	mNode->attachObject(mpRef);

	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);

	//Textura para usar como RenderTarget
	TexturePtr rttTex = TextureManager::getSingleton().createManual("rttReflejo", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D,
		size_.first, size_.second, 0, PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
	Viewport* vpt = renderTexture->addViewport(camRef);
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(ColourValue::Black);

	TextureUnitState* tu = plano->getSubEntities()[0]->getMaterial()->getTechniques()[0]->getPasses()[0]->createTextureUnitState("rttReflejo");
						// LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE
	tu->setColourOperation(LBO_MODULATE); // black background
	tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);

	tu->setProjectiveTexturing(true, camRef);

	renderTexture->addListener(this);
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_t && !dry) {
		dry = true;
		timer.reset();
	}

	return false;
}

void Plano::frameRendered(Ogre::FrameEvent const& evt)
{
	if (dry && timer.getMilliseconds() >= stopTime)
		plano->setMaterialName("Practica1/LaPiedraJhonson");
}
