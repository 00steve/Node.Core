#include "View.h"


bool View::AdjustRenderSettings() {
	if (!parentRenderSettings) return false;
	//for now, just adopt the parent settings
	renderSettings = *parentRenderSettings;
	//DBOUT("view" << Node::Id() << ":adjust render settings\n");
	return true;
}

void View::Draw() {
	//OutputDebugString("Draw from view\n");
}

void View::HandleMessage(const Message message) {
	switch (message.code) {
	case MESSAGE_PARENT_SETTINGS_CHANGED:
		switch(message.subCode){
		case PARENT_SETTINGS_CHANGED_SIZE:
			AdjustRenderSettings();
			return;
		}
		return;

	case MESSAGE_SET_RENDER_SETTINGS: 
		parentRenderSettings = (RenderSettings*)message.data;
		return;
	
	case MESSAGE_SET_RENDER_SUBJECT: {
		Message reply;
		reply.code = MESSAGE_AM_RENDER_SUBJECT;
		reply.sender = this;
		reply.receiver = message.sender;
		Node::SendAMessage(message);
		return;
	}

	default:
		return Node::HandleMessage(message);
	}//end of switch
}

bool View::SetGraphics(Graphics* newGraphics) {
	if (graphics) {
		//do something with the old graphics
	}
	bool initialized = newGraphics->Initialize();
	graphics = initialized ? newGraphics : NULL;
	return initialized;
}

void View::Update() {
	//specific stuff that the default node update doesn't do
	Node::Update();
}

View::View(){
}


View::~View(){
}
