#include <allegro5/allegro.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"

GraphicsSystem::GraphicsSystem()
	:mpDisplay(NULL)
	,mpBackBuffer(NULL)
	,mWidth(0)
	,mHeight(0)
{
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

bool GraphicsSystem::init( int width, int height )
{
	mWidth = width;
	mHeight = height;

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);

	mpDisplay = al_create_display(width, height);
	if(!mpDisplay) 
	{
		fprintf(stderr, "GraphicsSystem::failed to create display!\n");
		return false;
	}
		
	//get the backbuffer
	ALLEGRO_BITMAP* pBackBuffer = al_get_backbuffer( mpDisplay );

	//set the back buffer as the target bitmap
	al_set_target_bitmap( pBackBuffer );

	//create the GraphicsBuffer backbuffer
	mpBackBuffer = new GraphicsBuffer( pBackBuffer );

	//al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgb(255,255,255));

	return true;
}

void GraphicsSystem::cleanup()
{
	al_destroy_display( mpDisplay );
	mpDisplay = NULL;

	mpBackBuffer->invalidate();
	delete mpBackBuffer;
	mpBackBuffer = NULL;
}

void GraphicsSystem::swap()
{
	al_flip_display();
}

void GraphicsSystem::wrapCoordinates( Vector2D& vector )
{
	if( vector.getX() < 0.0f )
	{
		vector.setX( getWidth() - 1.0f );
	}
	else if( vector.getX() >= getWidth() )
	{
		vector.setX( 0.0f );
	}

	if( vector.getY() < 0.0f )
	{
		vector.setY( getHeight() - 1.0f );
	}
	else if( vector.getY() >= getHeight() )
	{
		vector.setY( 0.0f );
	}
}

//static function
ALLEGRO_BITMAP* GraphicsSystem::switchTargetBitmap( ALLEGRO_BITMAP* pNewTarget )
{
	//get old target bitmap
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	//set dest to be the target
	al_set_target_bitmap( pNewTarget );

	return pOldTarget;
}
