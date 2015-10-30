#include <allegro5/allegro_primitives.h>

#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Vector2D.h"

GraphicsBuffer::GraphicsBuffer()
	:mpBitmap(NULL)
{
}

GraphicsBuffer::GraphicsBuffer( const string& filename )
{
	mpBitmap = al_load_bitmap( filename.c_str() );
}

GraphicsBuffer::GraphicsBuffer( int width, int height, const ALLEGRO_COLOR& color )
{
	mpBitmap = al_create_bitmap( width, height );
	clear( color );
}

GraphicsBuffer::GraphicsBuffer( ALLEGRO_BITMAP* pBitmap )
	:mpBitmap(pBitmap)
{
}

GraphicsBuffer::GraphicsBuffer( const GraphicsBuffer& rhs )
{
	mpBitmap = al_clone_bitmap( rhs.mpBitmap );
}

GraphicsBuffer& GraphicsBuffer::operator=( const GraphicsBuffer& rhs )
{
	if( &rhs == this )//self assignment
	{
		return *this;
	}

	//cleanup
	al_destroy_bitmap( mpBitmap );
	//clone bitmap
	mpBitmap = al_clone_bitmap( rhs.mpBitmap );

	return *this;
}

GraphicsBuffer::~GraphicsBuffer()
{
	al_destroy_bitmap( mpBitmap );
	//printf( " GraphicsBuffer destroyed!\n");
}

void GraphicsBuffer::clear( const ALLEGRO_COLOR& color )
{
	ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap( mpBitmap );
	al_clear_to_color( color );
	GraphicsSystem::switchTargetBitmap( pOldTarget );
}

void GraphicsBuffer::fillRegion( const Vector2D& ul, const Vector2D& lr, const ALLEGRO_COLOR& color )
{
	ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap( mpBitmap );
	al_draw_filled_rectangle( ul.getX(), ul.getY(), lr.getX(), lr.getY(), color );
	GraphicsSystem::switchTargetBitmap( pOldTarget );

}