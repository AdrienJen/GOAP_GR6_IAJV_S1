#pragma once
#include "Task.h"
#include "Village.h"

//Classe Pour r�cup�ratioin du bois

class Timber : public Task {
public:
	void Execute(Village& village) const override;
	float Evaluation(Village& village) const override;
private:
};