#pragma once

#include <map>
#include <string>
#include "Trackable.h"
#include "Defines.h"

using namespace std;

class GraphicsBuffer;

const IDType STARTING_SEQUENTIAL_ID = 0;
const IDType ENDING_SEQUENTIAL_ID = 999;

class GraphicsBufferManager:public Trackable
{
public:
	GraphicsBufferManager();
	~GraphicsBufferManager();

	void init();
	void clear();

	//load buffer with a predetermined id - must be outside range STARTING_SEQUENTIAL_ID -> ENDING_SEQUENTIAL_ID
	IDType loadBuffer( const IDType& id, const string& filename );
	//load the buffer and assign a sequential id
	IDType loadBuffer( const string& filename );
	IDType manageBuffer( GraphicsBuffer* pBuffer, const IDDescriptor& desc ); 

	void deleteBuffer( const IDType& id );
	void deleteBufferByDescriptor( const IDDescriptor& desc );

	GraphicsBuffer* getBuffer( const IDType& id );
	GraphicsBuffer* getBufferByDescriptor( const IDDescriptor& desc );
private:
	IDType getNextID();

	map<IDType, GraphicsBuffer*> mBuffers;
	map<IDDescriptor, IDType> mDescLookup;
	static int msNextID;
};