#include "Plano.h"

#include <OgreMeshManager.h>

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

Plano::Plano(Ogre::SceneNode* mNode_, std::string const& name, std::pair<int, int> size, std::pair<int, int> cuts): EntityIG(mNode_) {
	MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0), size.first, size.second, cuts.first, cuts.second, true,
		1, 1.0, 1.0, Vector3::UNIT_Z);

	mNode->attachObject(mSM->createEntity(name));
}
