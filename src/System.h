#pragma once

#include <String>

/* System - holds game and graphics system.  Should also hold other systems that don't necessarily belong in the Game class.
	Also has some global functions that are of some use.

	Dean Lawson
	Champlain College
	2011
*/

//forward declarations
class GraphicsSystem;
class Game;
class System;

extern System* gpSystem;//global variable used to get the system object

class System 
{
public:
	System();
	~System();

	void writeToConsole( const std::string& message ) const;

	Game* getGame() { return mpGame; };
	GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; };

private:
	GraphicsSystem* mpGraphicsSystem;
	Game* mpGame;
};

void abort_on_error(const char *message);
float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern System* gpSystem;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

//macros to make accessing common things a bit less ugly
#define GAME gpSystem->getGame()
#define MESSAGE_MANAGER gpSystem->getGame()->getMessageManager()
#define GRAPHICS_SYSTEM gpSystem->getGraphicsSystem()
