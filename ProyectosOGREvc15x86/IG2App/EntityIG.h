#pragma once
#include <OgreInput.h>
#include "IG2ApplicationContext.h"
#include <SDL_keycode.h>

class EntityIG : public OgreBites::InputListener
{

public:
	EntityIG();
	
	~EntityIG();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) = 0;

private:
};

