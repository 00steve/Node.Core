#include "Graphics.h"




Graphics::Graphics(){
}

Graphics::~Graphics() {
}

void Graphics::HandleMessage(const Message message) {
	switch (message.code) {
	case MESSAGE_PARENT_SETTINGS_CHANGED:
		switch (message.subCode) {
		case PARENT_SETTINGS_CHANGED_SIZE:
			return;
		}
		return;

	case MESSAGE_SET_RENDER_SETTINGS:
		parentRenderSettings = (RenderSettings*)message.data;
		return;

	case MESSAGE_STARTED_REFERENCE:
		return;

	case MESSAGE_SET_RENDER_SUBJECT: 
		return;

	}//end of switch
	return Node::HandleMessage(message);
}


bool Graphics::SetTarget(Drawable* newTarget) {
	target = newTarget;
	return false;
}
