#include "View.h"


Node* View::AddChild(Node* newNode) {
	if (dynamic_cast<Graphics*>(newNode)) {
		SetGraphics((Graphics*)newNode);
	}
	return Node::AddChild(newNode);
}

bool View::AdjustRenderSettings() {
	if (!parentRenderSettings) return false;
	RenderSettings oldRenderSettings = renderSettings;
	//for now, just adopt the parent settings
	renderSettings = *parentRenderSettings;
	//a window handle has been added, do what needs to be done
	if (!oldRenderSettings.Window && renderSettings.Window) {
		DBOUT("view: rendersettings now has window handle");
		if (graphics) {
			SetGraphics(graphics);
		}
	}
	//DBOUT("view" << Node::Id() << ":adjust render settings\n");
	return true;
}

void View::Draw() {
	if (graphics) {
		graphics->Draw();
	}
	//OutputDebugString("Draw from view\n");
}

void View::HandleMessage(const Message message) {
	switch (message.code) {
	case MESSAGE_PARENT_SETTINGS_CHANGED:
		switch(message.subCode){
		case PARENT_SETTINGS_CHANGED_SIZE:
			if (graphics) {
				Message forward;
				forward.code = MESSAGE_PARENT_SETTINGS_CHANGED;
				forward.subCode = PARENT_SETTINGS_CHANGED_SIZE;
				forward.receiver = graphics;
				Node::SendAMessage(forward);
			}
		}
		AdjustRenderSettings();
		return;

	case MESSAGE_SET_RENDER_SETTINGS: 
		parentRenderSettings = (RenderSettings*)message.data;
		DBOUT("View:set render settings\n");
		DBOUT("\t- window handle :" << (parentRenderSettings->Window ? "true" : "false") << "\n");
		AdjustRenderSettings();
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
		Node::CreateAndSendMessage(graphics, MESSAGE_ENDED_REFERENCE, NULL);
	}
	if (graphics != newGraphics) {
		Node::CreateAndSendMessage(newGraphics, MESSAGE_STARTED_REFERENCE, NULL);
		DBOUT("\t- window handle :" << (renderSettings.Window ? "true" : "false") << "\n");
		Node::CreateAndSendMessageImmediate(newGraphics, MESSAGE_SET_RENDER_SETTINGS, (void*)&renderSettings);
		DBOUT("view:set the reference for the graphics to the render settings\n");
	}

	//set the new graphics object whether it fails to initialize or is successful
	//we really don't care. It can always try again later.
	graphics = newGraphics;

	if (!newGraphics->Initialize()) {
		DBOUT("View graphics failed to initialize\n");
		graphics = NULL;
		return false;
	}
	return true;
}

void View::Update() {
	//specific stuff that the default node update doesn't do
	Node::Update();
}

View::View(){
}


View::~View(){
}
