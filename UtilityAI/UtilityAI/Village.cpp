#include <math.h>
#include <iostream>
#include "Village.h"
#include "Human.h"
#include "Hunt.h"

//Ajout de tâche à Human
void Village::AddTask(Task* task) {
	possibleTasks.push_back(task);
}


//Résultat de chasse
void Village::AddHunt(int hunt)
{
	if (huntReserve < MAX_HUNT_SIZE) {
		huntReserve += hunt;
		if (huntReserve > MAX_HUNT_SIZE)
		{
			huntReserve = MAX_HUNT_SIZE;
		}
	}
}


//Lancement de la meilleure tâche à executer
void Village::ExecuteBestTask()
{
	float bestTask = -1.0f;
	Task* currentTask = new Hunt();

	for (auto& task : possibleTasks) {
		float taskVal = task->Evaluation(*this);
		if (taskVal > bestTask) {
			bestTask = taskVal;
			currentTask = task;
		}
	}

	currentTask->Execute(*this);
	std::cout << std::endl;
}


//Reserve de nourriture
float Village::GetHuntReserve() const
{
	return huntReserve;
}


//Reserve de bois
float Village::GetTimberReserve() const
{
	return timberReserve;
}

//Lancement de chasse
void Village::UseHunt(int cost)
{
	huntReserve -= cost;
}


//Lancement de récupérationt de bois
void Village::UseTimber(int cost)
{
	timberReserve -= cost;
}

//Ajout de bois
void Village::AddTimber(int wood)
{
	timberReserve += wood;
}


//Construction de maison
void Village::BuildHouse()
{
	numberHouses++;
}