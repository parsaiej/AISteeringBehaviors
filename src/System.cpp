#include <allegro.h>
#include "System.h"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "GraphicsSystem.h"
#include "Game.h"

using namespace std;

System::System()
{
	//initialize and install all the Allegro systems
	if (allegro_init() != 0)
		exit(-1);

	//install a digital sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) 
    {
        abort_on_error("Error initializing sound system");
    }

	install_keyboard(); 
	install_mouse();
	install_timer();
	show_os_cursor(MOUSE_CURSOR_ARROW);//turn on mouse cursor

	srand(time(0));//seed random number generator

	//create graphics system and game
	mpGraphicsSystem = new GraphicsSystem();
	mpGame = new Game();
}

System::~System()
{
	delete mpGraphicsSystem;
	delete mpGame;
}

void abort_on_error(const char *message)
{
	if (screen != NULL)
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

	allegro_message("%s.\nLast Allegro error ‘%s’\n", message, allegro_error);
	exit(-1);
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

void System::writeToConsole( const std::string& message ) const
{
	cout << message << "\n";
}
