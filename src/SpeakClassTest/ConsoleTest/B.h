#pragma once
#include "SpeakClass/SpeakClassAPI.h"

class B : public SpeakClass{
public:
	void ReceiveFromOtherClass(Room* room, const int& dataType, void* data, const string& otherClassName);
};