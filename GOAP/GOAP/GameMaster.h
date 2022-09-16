#pragma once
#include "GameState.h"
#include "GOAP.h"


// The game master manages the main loops of the program

struct GameMaster
{
	GameState* currentGameState;
	GOAPPlanner* goap;
	Action* goal;

	std::vector<Action*> availableActions;

	static void waitForMilliseconds(int milli);

	void StartGame();

	void UdapteGame();

	void DeleteGame();
};