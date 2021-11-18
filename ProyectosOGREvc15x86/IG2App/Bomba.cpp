#include "Bomba.h"
#include <OgreEntity.h>
#include <iostream>

//TODO: El rio no se detiene 5s despues de darle a la T
Bomba::Bomba(Ogre::SceneNode* _node) : EntityIG(_node) {
	Ogre::Entity* bomba = mSM->createEntity("Barrel.mesh");
	bomba->setMaterialName("Practica1/Wings");

	animationNode = mNode->createChildSceneNode();
	animationNode->attachObject(bomba);

	float duracion = 2.f;
	float longDesplazamiento = 20.f;

	//TODO Animation
	Ogre::Animation* animation = mSM->createAnimation("animVV", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(animationNode);
	//TODO Pos Inicial , Orientacion y duraciones
	Ogre::Vector3 keyframePosAux(0.0);
	Ogre::Vector3 src(0, 0, 1); // posici�n y orientaci�n iniciales
	Ogre::Real durPaso = duracion / 4.0;  // uniformes

	//TODO KEYFRAMES -> Usaremos un solo keyframe para settear la pos y rot en cada momento
	Ogre::TransformKeyFrame* kfAux;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	//! Keyframe 0: origen
	kfAux = track->createNodeKeyFrame(durPaso * 0);
	kfAux->setTranslate(keyframePosAux);
	//! Keyframe 1: Abajo
	kfAux = track->createNodeKeyFrame(durPaso * 1);
	keyframePosAux += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kfAux->setTranslate(keyframePosAux);  // Abajo  
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 1))); // Yaw(45) 
	//! Keyframe 2: Arriba
	kfAux = track->createNodeKeyFrame(durPaso * 3);
	keyframePosAux += Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kfAux->setTranslate(keyframePosAux);  // Arriba
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1))); // Yaw(-45)
	//! Keyframe 3: origen
	kfAux = track->createNodeKeyFrame(durPaso * 4); //durPaso = duracion/4.0 -> durPaso * 4 = 1.0

	//TODO Relacionar la animaci�n con un Estado 
	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

Bomba::~Bomba() {
}

void Bomba::frameRendered(Ogre::FrameEvent const& evt)
{
	if (!stopped)animationState->addTime(evt.timeSinceLastFrame);
}

bool Bomba::keyPressed(const OgreBites::KeyboardEvent& evt) {

	return false;
}

void Bomba::receiveEvent(Message mes, EntityIG* entidad) {
	if (mes.m == Messages::SamirExplota && !stopped) {
		std::cout << "Pasaaaaaaaaaaaaa\n";
		ex = mSM->createParticleSystem("PedroPicaPiedra2", "IG2App/bombSmoke");
		ex->setEmitting(true);
		animationNode->attachObject(ex);
		animationNode->setVisible(false);
		ex->setVisible(true);
		stopped = true;
	}
}
