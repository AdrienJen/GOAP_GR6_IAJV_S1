#pragma once
#include "Village.h"

class Human {
public:
	Human(Village& village) { village.AddHuman(); }
private:
};
