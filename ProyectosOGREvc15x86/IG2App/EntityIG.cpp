#include "EntityIG.h"

#include <iostream>
std::vector<EntityIG*> EntityIG::appListeners = std::vector<EntityIG*>(0, nullptr);


EntityIG::EntityIG(Ogre::SceneNode* node): mNode(node), mSM(mNode->getCreator()) {
}

EntityIG::~EntityIG() {
}

void EntityIG::sendEvent(Message mes, EntityIG* entidad)
{
	for (EntityIG* e : appListeners)
		e->receiveEvent(mes);
}
