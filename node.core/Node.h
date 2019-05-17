#pragma once

#include <sstream>

#include "List.h";
#include "Message.h"


#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}






class Node{
private:

	List<Node*> children;

	static unsigned long long int currentId;

	unsigned long long int id;

	List<Message> messages;
	Node* parent;

protected:

	bool ReceiveMessage(Message newMessage);
	bool SendMessage(Node* receiver, unsigned int code, void* data);


public:
	Node();
	~Node();


	Node* AddChild(Node* newChild);

	virtual void HandleMessage(Message message);

	virtual void HandleMessages();

	unsigned long long int Id();

	Node* RemoveChild(Node* oldChild);

	Node* SetParent(Node* newParent);

	virtual void Update();

};

