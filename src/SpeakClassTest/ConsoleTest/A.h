#pragma once
#include "SpeakClass.h"

class A : public SpeakClass{
public:
	void ReceiveFromOtherClass(Room* room, const int& dataType, void* data, const string& otherClassName);
};