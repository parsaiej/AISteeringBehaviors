#include "CoordinatesFollowMouseMessage.h"
#include <sstream>

CoordinatesFollowMouseMessage::CoordinatesFollowMouseMessage(ALLEGRO_MOUSE_STATE mouseState)
	:GameMessage(COORDINATES_FOLLOW_MOUSE),
	mMouseState(mouseState)
{
}

CoordinatesFollowMouseMessage::~CoordinatesFollowMouseMessage()
{
}

void CoordinatesFollowMouseMessage::process()
{
	//create mouse text
	std::stringstream mousePos;
	mousePos << "[" << mMouseState.x << ":" << mMouseState.y << "]";

	//write text at mouse position
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mMouseState.x, mMouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());
}
