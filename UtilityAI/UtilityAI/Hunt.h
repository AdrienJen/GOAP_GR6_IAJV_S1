#pragma once
#include "Task.h"
#include "Village.h"

//Classe pour r�cup�ration de la nourriture

class Hunt : public Task {
public:
	void Execute(Village& village) const override;
	float Evaluation(Village& village) const override;
private:
};