#pragma once

#include "DBOUT.h"
#include <sstream>

struct MapNode {
	std::string key;
	long long int keyHash;
	void* value;

	MapNode* left;
	MapNode* right;
};



template <class Value>
class Map{
private:
	MapNode* root;

	//generate hash map
	//1.get bytesize
	//2.add each byte to a long long int (8 bytes)
	//3.loop over and keep adding them
	//4.get a unique value
	long long int Hash(std::string key) {
		//unsigned int byteLength = sizeof(string);
		//unsigned int x = key.length;
		//DBOUT("key: " << std::endl);
		return 0;
	}


	void Insert(MapNode* parent, MapNode* child) {

	}


public:
	Map() :
		root(NULL) {
	}

	~Map() {

	}

	void Add(std::string key, Value* value) {
		MapNode* newNode = new MapNode();
		newNode->key = key;
		newNode->keyHash = Hash(key);
		newNode->value = (void*)value;

	}
};

