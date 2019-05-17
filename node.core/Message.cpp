#include "Message.h"


Message::Message() {
}

Message::Message(Node* receiver, unsigned int code, void* data) :
	receiver(receiver),
	code(code),
	data(data) {
}


Message::~Message()
{
}
