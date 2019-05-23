#pragma once

#include "DBOUT.h"
#include <sstream>

template <class Value>
struct MapNode {
	std::string key;
	long long hash;
	Value value;

	MapNode* left;
	MapNode* right;
};



template <class Value>
class Map{
private:

	MapNode<Value>* lastAddedNode;

	/*store the last hash that was generated.*/
	long long lastHash;

	/*store the last values used for whatever was
	added to the map*/
	std::string lastKey;

	/*store the length of the last key that was hashed.
	You never know when this might be useful.*/
	unsigned int lastKeyLength;

	/*store a bit map of 01111111 to clear out the 
	8th bit, which shouldn't be used for normal ascii
	characters. They should only be between 32-127, if
	it is plain text without crazy stuff that is dumb.*/
	const char lastSevenBits = 127;

	MapNode<Value>* root;

	MapNode<Value>* GetValue(MapNode<Value>* node, long long hash) {
		if (!node) {
			return NULL;
		}
		if (node->hash == hash) {
			return node;
		}
		if (node->hash > hash) {
			return GetValue(node->left, hash);
		}
		else {
			return GetValue(node->right, hash);
		}
	}

	//generate hash map
	long long int Hash(std::string key) {
		unsigned int i = lastKeyLength = key.length();
		long long h = 0;
		while (i-- > 0) {
			//remove the 8th bit, shift it to where it should be 
			//inserted into c, then xor with c to flip all of the
			//bits affected in c
			h = h ^ ((key[i] & lastSevenBits) << (i * 7 % 64));
		}
		return lastHash = h;
	}


	bool Insert(MapNode<Value>* parent, MapNode<Value>* child) {
		if (!parent) {
			parent = child;
			return true;
		}
		//if the current node is larger than the new
		//node send it to the left child
		if (parent->hash > child->hash) {
			return Insert(parent->left, child);
		}
		//if the current node is the same size or smaller than 
		//the new node send it to the right child
		else if(parent->hash < child->hash){
			return Insert(parent->right, child);
		}
		else return false;
	}


public:



	bool Add(std::string key, Value value) {
		MapNode<Value>* newNode = new MapNode<Value>();
		newNode->key = key;
		newNode->hash = Hash(key);
		newNode->value = value;

		lastAddedNode = newNode;
		return Insert(root, newNode);
	}

	bool KeyExists(std::string key) {
		MapNode<Value>* node = GetValue(root, Hash(key));
		return node;
	}

	Map() :
		root(NULL) {
	}

	~Map() {

	}


	Value operator [] (std::string key) {
		MapNode<Value>* node = GetValue(root, Hash(key));
		if (!node) {
			return Value();
		}
		return node->value;
	}
};

