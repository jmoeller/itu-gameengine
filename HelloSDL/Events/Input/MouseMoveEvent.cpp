#include "MouseMoveEvent.h"


MouseMoveEvent::MouseMoveEvent(SDL_MouseMotionEvent *input, short eventtype) : EventObject(eventtype)
{
	this->input = input;
}

MouseMoveEvent::~MouseMoveEvent(void)
{
}

SDL_MouseMotionEvent* MouseMoveEvent::GetInput()
{
	return input;
}
