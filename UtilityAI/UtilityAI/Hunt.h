#pragma once
#include "Task.h"
#include "Village.h"

//Classe pour récupération de la nourriture

class Hunt : public Task {
public:
	void Execute(Village& village) const override;
	float Evaluation(Village& village) const override;
private:
};