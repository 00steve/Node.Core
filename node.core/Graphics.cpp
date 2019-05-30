#include "Graphics.h"




Graphics::Graphics(){
}

Graphics::~Graphics() {
}

bool Graphics::SetTarget(Drawable* newTarget) {
	target = newTarget;
	return false;
}
