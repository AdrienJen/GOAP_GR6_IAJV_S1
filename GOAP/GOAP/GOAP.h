#pragma once
#include <vector>
#include "Action.h"

class GOAPPlanner
{
public:

	//Returns the sequence of actions necessary to reach the goal
	std::vector<Action*> plan(std::vector<Action*>& possibleActions, GameState& actualState,
		const Action* const goal) const;


	bool buildGraph(const std::vector<Action*>& possibleActions,
		GameState& actualState,
		const Action* goal,
		std::vector<Action*>& actionsQueue,
		int& cost) const;
};