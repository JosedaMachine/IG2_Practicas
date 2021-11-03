#include "Enjambre.h"
#include <iostream>



Enjambre::Enjambre(Ogre::SceneNode* _node, Ogre::SceneNode* avionNode) : EntityIG(_node), avionNode_(avionNode) {
	controlDron = new Dron(mNode->createChildSceneNode(), 3, 12);
	controlDron->getMainNode()->scale(0.5, 0.5, 0.5);
	controlDron->getMainNode()->setPosition(0, 3700, 0);
	int numDrones = 20;

	float size = 0.35;
	for (int i = 0; i < numDrones; i++) {
		float degree = Ogre::Math::RangeRandom(0., 360.);
		drons.push_back(new Dron(mNode->createChildSceneNode(), 3, 12, false));
		drons.back()->getCuerpoDron()->setMaterialName("Practica1/happyCursed");
		drons.back()->getMainNode()->scale(size, size, size);

		drons.back()->getMainNode()->yaw(Ogre::Degree((rand() % 360) - 180));
		drons.back()->getMainNode()->roll(Ogre::Degree((rand() % 360) - 180));
		drons.back()->getMainNode()->translate(0, 3700, 0, Ogre::SceneNode::TS_LOCAL);
	}
}

Enjambre::~Enjambre() {
	for (auto en : drons) {
		delete en; en = nullptr;
	}
	drons.clear();
}

bool Enjambre::keyPressed(const OgreBites::KeyboardEvent& evt) {
	return false;
}

void Enjambre::frameRendered(Ogre::FrameEvent const& evt) {
	for (auto dron : drons) {
		dron->EL_TRUCO(0.5);
	}
	
	for (auto dron : drons) {
		Ogre::AxisAlignedBox boxColliderAvion = avionNode_->_getWorldAABB();
		Ogre::AxisAlignedBox  boxDron = dron->getMainNode()->_getWorldAABB();
		if (boxDron.intersection(boxColliderAvion).volume() != 0) {
			delete dron;
			drons.erase(remove(drons.begin(), drons.end(), dron), drons.end());
		}
	}

	if (drons.size() == 0) {
		controlDron->getCuerpoDron()->setMaterialName("Practica1/TrueYellow");
	}
}
