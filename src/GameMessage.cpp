#include "GameMessage.h"


GameMessage::GameMessage(MessageType type)
:mType(type)
,mSubmittedTime(0)
,mScheduledTime(0)
{
}


GameMessage::~GameMessage()
{
}
