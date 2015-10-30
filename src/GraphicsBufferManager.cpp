#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"

int GraphicsBufferManager::msNextID = 0;

GraphicsBufferManager::GraphicsBufferManager()
{
}

GraphicsBufferManager::~GraphicsBufferManager()
{
	clear();
}

void GraphicsBufferManager::init()
{
}

void GraphicsBufferManager::clear()
{
	map<IDType,GraphicsBuffer*>::iterator iter;
	for( iter = mBuffers.begin(); iter != mBuffers.end(); ++iter )
	{
		GraphicsBuffer* pBuff = iter->second;
		delete pBuff;
	}

	mBuffers.clear();
	mDescLookup.clear();
}

IDType GraphicsBufferManager::loadBuffer( const IDType& id, const string& filename )
{
	//make sure this isn't already out there
	map<IDDescriptor, IDType>::iterator iter = mDescLookup.find( filename );
	if( iter == mDescLookup.end() )//not already in there
	{
		GraphicsBuffer* pBuffer = new GraphicsBuffer( filename );
		if( pBuffer->isValid() )
		{
			mBuffers[id] = pBuffer;
			mDescLookup[filename] = id;
		}
		else
		{
			delete pBuffer;
		}
	}
	return id;
}

IDType GraphicsBufferManager::loadBuffer( const string& filename )
{
	IDType theID = getNextID();

	return loadBuffer( theID, filename );
}

IDType GraphicsBufferManager::manageBuffer( GraphicsBuffer* pBuffer, const IDDescriptor& desc )
{
	IDType theID = INVALID_ID;

	//make sure this isn't already out there
	map<IDDescriptor, IDType>::iterator iter = mDescLookup.find( desc );
	if( iter == mDescLookup.end() )//not already in there
	{
		theID = getNextID();
		mBuffers[theID] = pBuffer;
		mDescLookup[desc] = theID;
	}
	return theID;
}

void GraphicsBufferManager::deleteBuffer( const IDType& id )
{
	if( id == INVALID_ID )
	{
		return;
	}

	//find the entry
	map<IDType,GraphicsBuffer*>::iterator iter = mBuffers.find( id );
	if( iter != mBuffers.end() )//found!
	{
		GraphicsBuffer* pBuff = iter->second;
		delete pBuff;
		mBuffers.erase( iter );
	}

	//go through the descriptor table and remove id from there too.
	map<IDDescriptor, IDType>::iterator iter2;
	for( iter2 = mDescLookup.begin(); iter2 != mDescLookup.end(); ++iter2 )
	{
		if( iter2->second == id )
		{
			mDescLookup.erase( iter2 );
			break;
		}
	}
}

void GraphicsBufferManager::deleteBufferByDescriptor( const IDDescriptor& desc )
{
	//find the descriptor in the lookup table
	map<IDDescriptor, IDType>::iterator iter = mDescLookup.find( desc );
	if( iter != mDescLookup.end() )//found
	{
		deleteBuffer( iter->second );
	}
}

GraphicsBuffer* GraphicsBufferManager::getBuffer( const IDType& id )
{
	GraphicsBuffer* pReturn = NULL;
	
	map<IDType, GraphicsBuffer*>::iterator iter = mBuffers.find( id );
	if( iter != mBuffers.end() )//found?
	{
		pReturn = iter->second;
	}

	return pReturn;
}

GraphicsBuffer* GraphicsBufferManager::getBufferByDescriptor( const IDDescriptor& desc )
{
	//find the descriptor in the lookup table
	map<IDDescriptor, IDType>::iterator iter = mDescLookup.find( desc );
	if( iter != mDescLookup.end() )//found
	{
		return getBuffer( iter->second );
	}
	return NULL;
}

IDType GraphicsBufferManager::getNextID()
{
	IDType theID = INVALID_ID;

	//find an unused id
	for( int i=msNextID; i<HIGHEST_ID; i++ )
	{
		map<IDType, GraphicsBuffer*>::iterator iter = mBuffers.find( i );
		if( iter == mBuffers.end() )//not in use
		{
			theID = i;
			msNextID = i+1;
			break;
		}
	}
	return theID;
}
