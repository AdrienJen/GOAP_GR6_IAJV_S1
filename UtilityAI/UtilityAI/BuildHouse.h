#pragma once
#include "Task.h"
#include "Village.h"

//Classe BuildHouse

class BuildHouse : public Task {
public:
	void Execute(Village& village) const;
	float Evaluation(Village& village) const;
private:
};