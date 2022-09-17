#include "BuildHouse.h"
#include <iostream>

void BuildHouse::Execute(Village& village) const
{
	village.BuildHouse();
	village.UseTimber(15);
	std::cout << "Build House" << std::endl;
}

float BuildHouse::Evaluation(Village& village) const
{
	if (village.GetTimberReserve() < 15) {
		return 0.0f;
	}
	float utilityBuild = ((NUMBER_HOUSE - static_cast<float>(village.numberHouses)) / NUMBER_HOUSE);
	float utilityTimber = 1 - ((MAX_TIMBER_SIZE - village.GetTimberReserve()) / MAX_TIMBER_SIZE);
	float utilityVillager = 1 - ((MAX_HUMAN_SIZE - village.sizeHuman) / static_cast<float>(MAX_HUMAN_SIZE));

	std::cout << "Evaluation build house : " << (utilityBuild + utilityTimber + utilityVillager) / 3 << std::endl;
	return (utilityBuild + utilityTimber + utilityVillager) / 3;
}