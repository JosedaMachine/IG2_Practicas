#include "RotorDron.h"
RotorDron::RotorDron(Ogre::SceneManager* mSM, const int& numHelices, Ogre::SceneNode* parent): numHelices_(numHelices) {

	if (!parent)
		mNode = mSM->getRootSceneNode()->createChildSceneNode();
	else mNode = parent->createChildSceneNode();

	//Esfera
	float radi = 5;
	esferaNode = mNode->createChildSceneNode();
	Ogre::Entity* esfera = mSM->createEntity("sphere.mesh");
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

	aspasM = new Helices(mSM, false, numHelices, helicesNode);

	float scale = 0.5;
	helicesNode->pitch(Ogre::Degree(90.));
	helicesNode->setScale(scale, scale, scale);
	helicesNode->translate(0, 100 * radi, 0);
}

bool RotorDron::keyPressed(const OgreBites::KeyboardEvent& evt) {
	aspasM->keyPressed(evt);

	return true;
}

RotorDron::~RotorDron() {

	delete mNode;
}
