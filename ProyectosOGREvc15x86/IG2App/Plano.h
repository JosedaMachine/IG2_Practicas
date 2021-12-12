#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "EntityIG.h"
#include <OgreEntity.h>
#include <OgreTimer.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>
#include <OgreViewport.h>
#include <OgreHardwarePixelBuffer.h>

#include <OgreMovablePlane.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>
#include <OgreRenderTargetListener.h>
#pragma once
using namespace Ogre;

class Plano : public EntityIG, RenderTargetListener
{
	const float stopTime = 5000;
public:
	Plano(Ogre::SceneNode* mNode_,
		std::string const& name, 
		std::pair<int, int > size,
		std::pair<int, int > sizeVp = {0,0},
		Vector3 normal = Vector3::UNIT_Y);
	virtual ~Plano() {};

	void setMaterial(std::string name) { plano->setMaterialName(name); }
	void setEspejo(Camera* cam);
	void setReflejo(Camera* cam, Ogre::Real distance);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void frameRendered(Ogre::FrameEvent const& evt);
private:
	Entity* plano;
	Vector3 normal;
	bool dry;

	Ogre::Timer timer; 
	std::pair<int, int> size_;
	std::pair<int, int> sizeVp_;
	//MovablePlanreReflejo, bastante poco intuitivo Joseda
	MovablePlane* mpRef;
	MovablePlane* movablePlaneMirror;
};

