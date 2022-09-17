#include "Human.h"
#include "Hunt.h"
#include "Timber.h"
#include "BuildHouse.h"
#include "UtilityAI.h"

#include "windows.h"
#include <iostream>

void UtilityAI::ExecuteUtilityAI()
{
	Village village = Village();
	Human human = Human(village);

	Hunt* hunt = new Hunt();
	Timber* timber = new Timber();
	BuildHouse* buildHouse = new BuildHouse();

	village.AddTask(hunt);
	village.AddTask(timber);
	village.AddTask(buildHouse);

	int nbIt = 0;
	while (nbIt < 50) {
		village.ExecuteBestTask();
		nbIt++;
	}
	std::cout << village.GetHuntReserve() << " Hunt remaining" << std::endl;
	std::cout << village.GetTimberReserve() << " Timber remaining" << std::endl;
	std::cout << village.numberHouses << " Houses created" << std::endl;
}