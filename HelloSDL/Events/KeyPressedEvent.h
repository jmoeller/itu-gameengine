#ifndef ITUENGINE_KEYPRESSEDEVENT_H
#define ITUENGINE_KEYPRESSEDEVENT_H

#include "EventObject.h"
#include "SDL_events.h"

class KeyPressedEvent :
	public EventObject
{
public:
	KeyPressedEvent(SDL_KeyboardEvent *input);
	~KeyPressedEvent(void);

private:
	SDL_KeyboardEvent *input;
};

#endif
