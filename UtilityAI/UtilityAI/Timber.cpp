#include "Timber.h"
#include <iostream>

void Timber::Execute(Village& village) const
{
	village.AddTimber(5);
	village.UseHunt(4);
	std::cout << "Get Wood : " << village.GetTimberReserve() << std::endl;
}

float Timber::Evaluation(Village& village) const
{
	float utilityWood = (MAX_TIMBER_SIZE - village.GetTimberReserve()) / MAX_TIMBER_SIZE;
	float utilityFood = 1 - ((MAX_HUNT_SIZE - static_cast<float>(village.GetHuntReserve())) / MAX_HUNT_SIZE);
	float utilityVillager = 1 - ((MAX_HUMAN_SIZE - village.sizeHuman) / static_cast<float>(MAX_HUMAN_SIZE));

	std::cout << "Evaluation timber : " << (utilityFood + utilityWood + utilityVillager) / 3 << std::endl;
	return (utilityFood + utilityWood + utilityVillager) / 3;
}