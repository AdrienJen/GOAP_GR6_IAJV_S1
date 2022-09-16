#pragma once
#include "Action.h"

//Contains all program data

class GameState
{
public:
	

	
	int availablePickaxe = 0;
	int craftedArmor = 0;
	int pickaxeEnergy = 0;
	int ironStock = 0;
	int awareness = 0;
	bool canSteal = false;
	bool hasPickaxe = false;
	~GameState()
	{

	}
};