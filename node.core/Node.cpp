#include "Node.h"


unsigned long long Node::currentId = 0;
Map<Node*> Node::directory = Map<Node*>();


Node* Node::AddChild(Node* newChild) {
	children.Push(newChild);
	return newChild;
}

bool Node::CreateAndSendMessage(Node* receiver, unsigned int code, void* data) {
	Message newMessage = Message();
	newMessage.receiver = receiver;
	newMessage.code = code;
	newMessage.data = data;
	bool success = SendAMessage(newMessage);
	return success;
}

Node::Node() : 
	id(currentId++),
	registered(false) {
}

Node::Node(std::string name) :
	id(currentId++) {
	Register(name);
}

Node::~Node(){
	int i = children.Count();
	while (i-- > 0) {
		delete children[i]; //<-- kill the children
	}
}

void Node::HandleMessage(const Message message) {

}

void Node::HandleMessages() {
	unsigned int i = messages.Count();
	while (i --> 0) {
		HandleMessage(messages[i]);
	}
	messages.Empty();
}

unsigned long long Node::Id() {
	return id;
}

bool Node::IsRegistered() {
	return registered;
}

bool Node::ReceiveMessage(const Message newMessage) {
	messages.Push(newMessage);
	return true;
}

bool Node::Register(const std::string name) {
	registered = directory.Add(name, this);
	this->name = registered ? name : "";
	return registered;
}

Node* Node::RemoveChild(Node* oldChild) {
	int i = children.Count();
	while (i --> 0) {
		if (children[i] != oldChild) continue;
		return children.Cut(i);
	}
	return NULL;
}

bool Node::SendAMessage(const Message newMessage) {
	if (!newMessage.receiver) return false;
	return newMessage.receiver->ReceiveMessage(newMessage);
}


Node* Node::SetParent(Node* newParent) {
	if (parent != NULL) {
		parent->RemoveChild(this);
	}
	return parent = newParent;
}

void Node::Update() {
	HandleMessages();
	unsigned int i = children.Count();
	while (i-- > 0) {
		children[i]->Update();
	}
}

Node* Node::operator [] (const std::string name) {
	return directory[name];
}