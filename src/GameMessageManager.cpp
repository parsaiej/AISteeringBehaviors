#include <list>

#include "Game.h"
#include "GameMessageManager.h"
#include "GameMessage.h"

using namespace std;

GameMessageManager::GameMessageManager()
{
}

GameMessageManager::~GameMessageManager()
{
	list<GameMessage*>::iterator iter;
	for( iter = mMessages.begin(); iter != mMessages.end(); ++iter )
	{
		delete (*iter);
	}
}

void GameMessageManager::processMessagesForThisframe()
{
	double currentTime = gpGame->getCurrentTime();

	list<GameMessage*>::iterator iter = mMessages.begin();
	while( iter != mMessages.end() )
	{
		if( (*iter)->getScheduledTime() <= currentTime )
		{
			(*iter)->process();
			delete (*iter);
			iter = mMessages.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void GameMessageManager::addMessage( GameMessage* pMessage, int delay )
{
	double currentTime = gpGame->getCurrentTime();

	//set frame numbers
	pMessage->mSubmittedTime = currentTime;
	pMessage->mScheduledTime = currentTime + delay;

	//put it in the message list
	mMessages.push_back( pMessage );
}