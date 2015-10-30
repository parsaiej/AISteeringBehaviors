#pragma once

#include "Trackable.h"
#include <allegro5/allegro.h>
#include <string>

class Vector2D;

using namespace std;

const ALLEGRO_COLOR BLACK_COLOR = al_map_rgb(0,0,0);

class GraphicsBuffer:public Trackable
{
public:
	GraphicsBuffer();//default
	GraphicsBuffer( const string& filename );//load from a file
	GraphicsBuffer( int width, int height, const ALLEGRO_COLOR& color = BLACK_COLOR  );//create blank with given size
	GraphicsBuffer( ALLEGRO_BITMAP* pBitmap );//create from allegro bitmap
	//copy constructor
	GraphicsBuffer( const GraphicsBuffer& rhs );
	//assignment operator
	GraphicsBuffer& operator=( const GraphicsBuffer& rhs );

	//destructor
	~GraphicsBuffer();

	//set the entire buffer to a certain color
	void clear( const ALLEGRO_COLOR& color = BLACK_COLOR );

	//set a rectangular region to a color
	void fillRegion( const Vector2D& ul, const Vector2D& lr, const ALLEGRO_COLOR& color );

	//accessors
	inline int getWidth() const { return al_get_bitmap_width(mpBitmap); };
	inline int getHeight() const { return al_get_bitmap_height(mpBitmap); };
	inline bool isValid() const { return mpBitmap != NULL; };
	inline void invalidate() { mpBitmap = NULL; };
	inline ALLEGRO_BITMAP* getBitmap() const { return mpBitmap; };

	inline void clearToColor() { al_clear_to_color(al_map_rgb(255, 255, 255)); };


private:
	ALLEGRO_BITMAP* mpBitmap;//never a subBitmap
};