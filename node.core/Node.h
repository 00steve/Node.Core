#pragma once
#include "DBOUT.h"
#include <sstream>
//
//
//#define DBOUT( s )            \
//{                             \
//   std::ostringstream os_;    \
//   os_ << s;                   \
//   OutputDebugString( os_.str().c_str() );  \
//}


#include "List.h";
#include "Message.h"
#include "Map.h"





class Node{
private:

	List<Node*> children;

	static unsigned long long int currentId;

	/*store a directory of all nodes that deserve
	a name.*/
	static Map<Node*> directory;

	unsigned long long id;

	List<Message> messages;

	Node* parent;

	std::string name;

protected:

	bool ReceiveMessage(Message newMessage);
	bool SendMessage(Node* receiver, unsigned int code, void* data);


public:
	Node();
	~Node();


	Node* AddChild(Node* newChild);

	virtual void HandleMessage(Message message);

	virtual void HandleMessages();

	unsigned long long Id();

	Node* RemoveChild(Node* oldChild);

	bool SetName(std::string name);

	Node* SetParent(Node* newParent);

	virtual void Update();

};

