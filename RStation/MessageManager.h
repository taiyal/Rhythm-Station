#ifndef _Message_Manager_H_
#define _Message_Manager_H_

#include <string>
#include <vector>

// A message.
struct Message
{
	Message(const std::string);

private:
	std::string Name;
	bool Broadcast;
};

// Message subscriber interface
class IMessageSubscriber
{
public:
	virtual ~IMessageSubscriber() { }
	virtual void HandleMessage( const Message &msg ) { };
	void ClearMessages(const std::string Message = "");

private:
	friend class MessageManager;
};

// Message subscriber implementation
class MessageSubscriber: public IMessageSubscriber
{
public:
	MessageSubscriber() {}
	MessageSubscriber(const MessageSubscriber &cpy);
	MessageSubscriber &operator=(const MessageSubscriber &cpy);

	void SbuscribeToMessage(const std::string MessageName); // auto-unsubscribes
	void UnsubscribeAll();

private:
	std::vector<std::string> SubscribedTo;
};

// Message manager
class MessageManager
{
public:
	// we don't need these yet...
	//MessageManager();
	//~MessageManager();

	void Subscribe(IMessageSubscriber* pSubscriber, const std::string& Message);
	void Unsubscribe(IMessageSubscriber* pSubscriber, const std::string& Message);
	void Broadcast(Message &msg) const;
	void Broadcast(const std::string& Message ) const;
	bool IsSubscribedToMessage(IMessageSubscriber* pSubscriber, const std::string &sMessage) const;
};

#endif