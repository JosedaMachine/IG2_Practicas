#include "Plano.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreMovablePlane.h>

Plano::Plano(Ogre::SceneNode* mNode_, std::string const& name, std::pair<int, int> size, std::pair<int, int> cuts, Vector3 normal_): EntityIG(mNode_) {
	normal = normal_;
	Ogre::MeshPtr ptr =MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(normal, 0), size.first, size.second, cuts.first, cuts.second, true,
		1, 1.0, 1.0, Vector3::UNIT_Z);

	e = mSM->createEntity(name);

	mNode->attachObject(e);


	timer = Ogre::Timer();
	timer.reset();
}

void Plano::setEspejo(Camera* cam){
	


}

void Plano::setReflejo(Camera* camRef){
	MovablePlane* mpRef = new MovablePlane(normal, 0.f);

	mNode->attachObject(mpRef);

	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);
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
		e->setMaterialName("Practica1/LaPiedraJhonson");
}
