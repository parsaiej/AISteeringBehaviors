#include "Sprite.h"
#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"

Sprite::Sprite( GraphicsBuffer* pBuffer, float sx, float sy, float sw, float sh )
	:mpBitmap(NULL)
	,mWidth(sw)
	,mHeight(sh)
{
	if( pBuffer->isValid() )
	{
		mpBitmap = al_create_sub_bitmap( pBuffer->getBitmap(), sx, sy, sw, sh );
	}
}

Sprite::~Sprite()
{
	//nothing to do right now as the bitmap is always a subBitmap
}

void Sprite::draw( GraphicsBuffer& dest, float dx, float dy, float rotationInRadians, int flags )
{
	if( mpBitmap != NULL && dest.getBitmap() != NULL )
	{
		//set new target
		ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap( dest.getBitmap() );
		//draw
		if( rotationInRadians != 0.0f )//need to rotate
		{
			float centerX = al_get_bitmap_width(mpBitmap)/2;
			float centerY = al_get_bitmap_height(mpBitmap)/2;
			al_draw_rotated_bitmap( mpBitmap, centerX, centerY, dx, dy, rotationInRadians, flags );
		}
		else//no need to rotate
		{
			al_draw_bitmap( mpBitmap, dx, dy, flags );
		}
		//restore old target
		GraphicsSystem::switchTargetBitmap( pOldTarget );
	}
}

/*void Sprite::drawScaled( GraphicsBuffer& dest, float dx, float dy, float dw, float dh, int flags )
{
	if( mpBitmap != NULL && dest.getBitmap() != NULL )
	{
		//set new target
		ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap( dest.getBitmap() );
		//draw
		al_draw_scaled_bitmap( mpBitmap, 0, 0, mWidth, mHeight, dx, dy, dw, dh, flags );
		//restore old target
		GraphicsSystem::switchTargetBitmap( pOldTarget );
	}
}*/



/*void Sprite::draw(GraphicsBuffer *pDestBuffer, int destX, int destY, float rotationInRadians)
{
	mpBuffer->copy( pDestBuffer, destX, destY, 0, 0, mWidth, mHeight, rotationInRadians );
}*/