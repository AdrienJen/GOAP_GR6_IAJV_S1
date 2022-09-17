
#pragma once
#include <unordered_map>
#define MAX_HUMAN_SIZE 5
#define MAX_HUNT_SIZE 20
#define HUNT_COST 1.0f
#define MAX_TIMBER_SIZE 20
#define NUMBER_HOUSE 4
#include "Task.h"
#include <list>

//Gestion du village

class Village {
public:
	Village() : huntReserve(0), timberReserve(0), sizeHuman(0), currentTask(NULL), numberHouses(0) {}
	float GetHuntReserve() const;
	float GetTimberReserve() const;

	void AddTask(Task* task);
	void AddHuman();
	void ExecuteBestTask();
	void AddHunt(int food);
	void UseHunt(int cost);
	void UseTimber(int cost);
	void AddTimber(int wood);
	void BuildHouse();
	int sizeHuman;
	int numberHouses;

private:
	std::list<Task*> possibleTasks;
	Task* currentTask;
	float huntReserve;
	float timberReserve;
};