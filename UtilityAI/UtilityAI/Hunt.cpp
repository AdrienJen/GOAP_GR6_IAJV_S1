#include "Hunt.h"
#include <iostream>

void Hunt::Execute(Village& village) const
{
	village.AddHunt(5);
	std::cout << "Get Hunt : " << village.GetHuntReserve() << std::endl;
}

float Hunt::Evaluation(Village& village) const
{
	float utilityHunt = (MAX_HUNT_SIZE - static_cast<float>(village.GetHuntReserve())) / MAX_HUNT_SIZE;
	std::cout << "Evaluation Hunt : " << utilityHunt << std::endl;
	return utilityHunt;
}