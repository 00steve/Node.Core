#pragma once

#include <cstring>
#include <stdio.h>
#include <iostream>

template <typename T>
class List{
private:
	T* children;
	unsigned int count;
	unsigned int length;

protected:


	virtual void increaseLength() {
		unsigned int newLength = length * 2 + 1;
		T* newChildren = new T[newLength];
		memcpy(newChildren, children, sizeof(T)*length);
		delete[] children;
		children = newChildren;
		length = newLength;
	}


public:
	List<T>() :
		count(0),
		length(0) {
		children = new T[0];
	}

	~List() {
		delete children;
	}


	unsigned int Count() {
		return count;
	}

	/*most of the time the last child index won't be the one that is cut, so it's using 
	the more simple method of just returning what's at the cut index and replacing it with
	whatever is stored in the last index. If the last index is the one cut, it will still 
	decrease the count and put its value back in the same index so who gives a shit.*/
	T Cut(unsigned int index) {
		T temp = children[index];
		children[index] = children[--count];
		return temp;
	}

	void Empty() {
		count = 0;
	}

	bool Exists(T item) {
		unsigned int i = count;
		while (i--> 0) {
			if (item != children[i]) continue;
			return true;
		}
		return false;
	}

	T Pop() {
		return children[--count];
	}

	unsigned int Length() {
		return length;
	}


	T Push(T newItem) {
		if (count == length) increaseLength();
		children[count++] = newItem;
		return newItem;
	}





	T operator [] (unsigned int index) {
		return children[index];
	}



};

