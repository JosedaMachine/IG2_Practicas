#include "Bomba.h"
#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

Bomba::Bomba(Ogre::SceneNode* _node) : EntityIG(_node) {
    Ogre::Entity* bomba = mSM->createEntity("Barrel.mesh");
    bomba->setMaterialName("Practica1/Wings");

	timer = Ogre::Timer();
	timer.reset();

	animationNode = mNode->createChildSceneNode();
    animationNode->attachObject(bomba);

	float duracion = 1;
	Ogre::Animation* animation = mSM->createAnimation("animVV", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(animationNode);
	Ogre::Vector3 keyframePos(-10., 0., 100.);
	Ogre::Real durPaso = duracion / 4.0;  // uniformes
	Ogre::TransformKeyFrame* kf;              // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
	kf = track->createNodeKeyFrame(durPaso * 0);  // Keyframe 0: origen
	kf->setTranslate(keyframePos); // Origen: Vector3
	//... // -> ->
	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);

	//! Continuacion no se que sube y baja como la marea y gira gira
	float longDesplazamiento = 20;

	Ogre::Vector3 keyframePosAux(0.0); 
	Ogre::Vector3 src(0, 0, 1); // posición y orientación iniciales
	Ogre::TransformKeyFrame* kfAux;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	kfAux = track->createNodeKeyFrame(durPaso * 0);   // Keyframe 0: origen
	kfAux = track->createNodeKeyFrame(durPaso * 1);   // Keyframe 1: abajo
	keyframePosAux += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kfAux->setTranslate(keyframePosAux);  // Abajo  
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 1))); // Yaw(45) 
	kfAux = track->createNodeKeyFrame(durPaso * 3); // Keyframe 2: arriba
	keyframePosAux += Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kfAux->setTranslate(keyframePosAux);  // Arriba
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1))); // Yaw(-45)
	kfAux = track->createNodeKeyFrame(durPaso * 4);  // Keyframe 3: origen
}

Bomba::~Bomba(){
}

void Bomba::frameRendered(Ogre::FrameEvent const& evt)
{
	if(!stopped)animationState->addTime(evt.timeSinceLastFrame);

	if (stopped && timer.getMilliseconds() >= stopTime ) {
		stopped = false;
		timer.reset();
	}
}

bool Bomba::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_t) stopped = true;

    return false;
}
