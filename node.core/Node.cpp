#include "Node.h"


unsigned long long Node::currentId = 0;
Map<Node*> Node::directory = Map<Node*>();


Node* Node::AddChild(Node* newChild) {
	children.Push(newChild);
	return newChild;
}

Node::Node() : 
	id(currentId++) {
}

Node::~Node(){
	int i = children.Count();
	while (i-- > 0) {
		delete children[i]; //<-- kill the children
	}
}

void Node::HandleMessage(Message message) {

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

bool Node::ReceiveMessage(Message newMessage) {
	messages.Push(newMessage);
	return true;
}

Node* Node::RemoveChild(Node* oldChild) {
	int i = children.Count();
	while (i --> 0) {
		if (children[i] != oldChild) continue;
		return children.Cut(i);
	}
	return NULL;
}

bool Node::SendMessage(Node* receiver, unsigned int code, void* data) {
	return false;
}

bool Node::SetName(std::string name) {
	//bool hasNode = directory.KeyExists(name);
	//if (hasNode) return false;
	//this->name = name;
	bool newName = directory.Add(name, this);
	this->name = newName ? name : "";
	return newName;
	//return true;
}

Node* Node::SetParent(Node* newParent) {
	if (parent != NULL) {
		parent->RemoveChild(this);
	}
	return parent = newParent;
}

void Node::Update() {

}