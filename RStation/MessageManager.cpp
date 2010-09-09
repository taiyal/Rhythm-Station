#include "MessageManager.h"

#include <set>
#include <map>

typedef std::set<IMessageSubscriber*> SubscribersSet;
static std::map<std::string,SubscribersSet> MessageToSubscribers;

// message
Message::Message(const std::string s)
{
	Name = s;
	Broadcast = false;
}

// message manager
void MessageManager::Subscribe(IMessageSubscriber* pSubscriber, const std::string& Message)
{
	SubscribersSet& subs = MessageToSubscribers[Message];
	subs.insert(pSubscriber);
}
