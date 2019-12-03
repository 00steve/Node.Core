#pragma once

#include "Node.h"
#include "Drawable.h"
#include "Window.h"
#include "DirectX3DGraphics.h"
#include "Scene.h"
#include "ComponentConfiguration.h"

class Component : public Node {
private:

	ComponentConfiguration properties;

	//camera(s)
	//view(s)
	List<View*> views;
	//window(s)
	List<Window*> windows;

public:

	virtual bool Initialize();
	virtual bool Load();

	Component();
	~Component();

	//ComponentConfiguration Configuration(const ComponentConfiguration configuration);


	/**
	 * Invoked by the registered window when a key is pressed
	 * while the window has focus.
	 */
	//virtual void OnKeyPressed(KeyEventArgs& e);

	/**
	 * Invoked when a key on the keyboard is released.
	 */
	//virtual void OnKeyReleased(KeyEventArgs& e);

	/**
	 * Invoked when the mouse is moved over the registered window.
	 */
	//virtual void OnMouseMoved(MouseMotionEventArgs& e);

	/**
	 * Invoked when a mouse button is pressed over the registered window.
	 */
	//virtual void OnMouseButtonPressed(MouseButtonEventArgs& e);

	/**
	 * Invoked when a mouse button is released over the registered window.
	 */
	//virtual void OnMouseButtonReleased(MouseButtonEventArgs& e);

	/**
	 * Invoked when the mouse wheel is scrolled while the registered window has focus.
	 */
	//virtual void OnMouseWheel(MouseWheelEventArgs& e);

	virtual bool Unload();

};

