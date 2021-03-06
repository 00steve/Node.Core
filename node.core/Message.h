#pragma once

#define MESSAGE_UNDEFINED 			0
/*node level functions 10-29*/
#define MESSAGE_FINISHED 			10
#define MESSAGE_STARTED 			11
#define MESSAGE_SET_PARENT          12
#define MESSAGE_UNSET_PARENT        13
#define MESSAGE_PARENT_SETTINGS_CHANGED	14//sent from parent to child as a trigger that some of the parent's settings have changed
#define			PARENT_SETTINGS_CHANGED_SIZE 1
#define			PARENT_SETTINGS_CHANGED_STATUS 2
#define MESSAGE_STARTED_REFERENCE	15//sent from a node to another node when it will start referencing the receiving node
#define MESSAGE_ENDED_REFERENCE		16//sent from a node to another node when it will no longer reference the receiving node

/*drawable level functions 30-49*/
#define MESSAGE_ADD_DRAWABLE 		30
#define MESSAGE_ADD_PHYSICAL 		31

#define MESSAGE_REMOVE_DRAWABLE 	40
#define MESSAGE_REMOVE_PHYSICAL 	41

#define MESSAGE_SET_CAMERA 				50 //mostly used by views, but it's here and stuff for things
#define MESSAGE_SET_TARGET 				51 //mostly used by cameras that point at things, but whatevs
#define MESSAGE_SET_POSITION_REFERENCE 	52
#define MESSAGE_SET_ROTATION_REFERENCE 	53
#define MESSAGE_ADD_VIEW                54//used by the window object to set a view to use
#define MESSAGE_ENABLE_VIEW             55
#define MESSAGE_DISABLE_VIEW            56
#define MESSAGE_SET_RENDER_SUBJECT      57//used by views to set what node should be drawn
#define MESSAGE_AM_RENDER_SUBJECT		58//sent back to objects when they are set as the render subject

#define MESSAGE_SELECTED 			110
#define MESSAGE_DESELECTED 			111

#define MESSAGE_TAKE_CONTROL 		175
#define MESSAGE_GIVE_CONTROL 		176
#define MESSAGE_PICKUP				179
#define MESSAGE_DROP				180
#define MESSAGE_CAN_INTERACT		181
#define MESSAGE_CANT_INTERACT		182

#define MESSAGE_PRIMARY_INTERACT	290
#define MESSAGE_SECONDARY_INTERACT	291
#define MESSAGE_TERTIARY_INTERACT	292

/*engine commands, the engine sets a reference
to itself as node::root, so any engine functions
can be called from any other node.*/
#define MESSAGE_ENGINE_SET_STATE 				300
#define MESSAGE_ENGINE_EXIT 					350
#define MESSAGE_ENGINE_SET_TEMP_CONTROLLER 		351
#define MESSAGE_ENGINE_UNSET_TEMP_CONTROLLER 	352
#define MESSAGE_ENGINE_SET_VIEW_CAMERA 			353

/*collision and damage stuff*/
#define MESSAGE_PROJECTILE_IMPACT	 			600
#define MESSAGE_BLUNT_IMPACT					601

#define MESSAGE_SET_ENABLED 		710
#define MESSAGE_SET_DISABLED 		711

/*physics engine stuff*/
#define MESSAGE_SET_VELOCITY 		920
#define MESSAGE_SET_ORIENTATION 	921
#define MESSAGE_SET_ROTATION 		922
#define MESSAGE_SET_PHYSICS_SPACE   923
#define MESSAGE_REGISTER_PHYSICS_OFFER      924
#define MESSAGE_REGISTER_PHYSICS_REQUEST    925 //should send a var map of physics objects to create
#define MESSAGE_REGISTER_PHYSICS_FINISHED   926 //should return a map that has corresponding physics objects

/*graphics engine stuff*/
#define MESSAGE_SET_RENDER_SETTINGS		1000 //is telling the receiving object to use the (RenderSettings*) pointer passed to it
#define MESSAGE_RENDER_SETTINGS_CHANGED 1001 //tell whoever it is sent to that your settings have changed

class Node;

class Message{
public:

	Message();
	Message(Node* receiver, unsigned int code, void* data);
	~Message();

	Node* sender;
	Node* receiver;
	unsigned int code;
	unsigned int subCode;
	void* data;
};

