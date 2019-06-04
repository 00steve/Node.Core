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

	bool registered;

protected:
	
	bool CreateAndSendMessage(Node* receiver, unsigned int code, void* data);
	void CreateAndSendMessageImmediate(Node* receiver, unsigned int code, void* data);
	bool ReceiveMessage(Message newMessage);
	bool SendAMessage(Message newMessage);


public:
	Node();

	Node(std::string name);

	~Node();

	virtual Node* AddChild(Node* newChild);

	virtual void HandleMessage(Message message);

	virtual void HandleMessages();

	unsigned long long Id();

	bool IsRegistered();

	bool Register(std::string name);

	Node* RemoveChild(Node* oldChild);

	Node* SetParent(Node* newParent);

	virtual void Update();

	Node* operator [] (std::string name);
};

