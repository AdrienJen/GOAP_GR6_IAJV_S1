#pragma once

//Classe pour gestion des t�ches du village

class Village;
class Task {
public:
	virtual void Execute(Village& village) const = 0;
	virtual float Evaluation(Village& village) const = 0;

protected:
	float utility;
};