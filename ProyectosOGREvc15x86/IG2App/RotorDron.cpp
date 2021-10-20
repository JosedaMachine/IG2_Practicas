#include "RotorDron.h"
RotorDron::RotorDron(Ogre::SceneNode * parent, const bool& clockWise, const int& numHelices): numHelices_(numHelices), EntityIG(parent) {

	if (!parent)
		mNode = mSM->getRootSceneNode()->createChildSceneNode();
	else mNode = parent->createChildSceneNode();

	//Esfera
	float radi = 5;
	esferaNode = mNode->createChildSceneNode();
	Ogre::Entity* esfera = mSM->createEntity("sphere.mesh");
	esfera->setMaterialName("Practica1/Brown");
	esferaNode->attachObject(esfera);
	esferaNode->setScale(radi, radi, radi);
	
	//Cilindro
	//SOY idiota tenia que usar el puto AspasMolino y no tener otro array. 
	//Le tengo que pasar un parametro para poner o quitar los adornosQ

	//Helices
	int radio = 500;
	float ang = 90;
	float proportion = 360.0 / numHelices_;

	helicesNode = mNode->createChildSceneNode();

	aspasM = new Helices(helicesNode, false, numHelices);
	aspasM->setClockWise(clockWise);


	float scale = 0.5;
	helicesNode->pitch(Ogre::Degree(90.));
	helicesNode->setScale(scale, scale, scale);
	helicesNode->translate(0, 100 * radi, 0);
}

bool RotorDron::keyPressed(const OgreBites::KeyboardEvent& evt) {
	aspasM->keyPressed(evt);

	return true;
}

void RotorDron::rotate()
{
	aspasM->rotate();
}

RotorDron::~RotorDron() {

	delete mNode;
}
