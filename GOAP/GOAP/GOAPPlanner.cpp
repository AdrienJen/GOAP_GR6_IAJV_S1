#include "GOAP.h"

#include <cassert>

#include "GameState.h"

std::vector<Action*> GOAPPlanner::plan(
	std::vector<Action*>& possibleActions,
	GameState& actualState,
	const Action* goal) const
{
	//copy all goal preconditions

	std::vector<Action*> actions; //Final vector that will be returned
	int actionsCost = -1;

	
	GameState stateCopy = actualState;

	//Construction of the graph
	for (auto& action : possibleActions)
	{
		std::vector<Action*> tmpActions; 
		int tmpCost = -1;

		if (goal->getPrecondition() == nullptr || goal->getPrecondition()->getPrecType() == ActionType::NO_ACTION)
			break;

		if (goal->getPrecondition()->checkPrecondition(action->getEffect()->getEffectType()))
		{
			tmpCost = 0;

			
			tmpCost += action->getCost();

			// Execute action
			

			// Add the action to the list
			tmpActions.push_back(action);

			const bool isBuilded = buildGraph(possibleActions, stateCopy, action, tmpActions, tmpCost);

		}

		if (actionsCost == -1
			&& tmpCost > 0)
		{
			actionsCost = tmpCost;
			actions = tmpActions;
		}

		if (tmpCost < actionsCost
			&& tmpCost > 0)
		{
			actionsCost = tmpCost;
			actions = tmpActions;
		}
	}

	//Identify if we have built the graph correctly
	assert(!actions.empty(), "Error in the actions !!");

	///return the action list
	return actions;
}

bool GOAPPlanner::buildGraph(const std::vector<Action*>& possibleActions,
	GameState& actualState,
	const Action* goal,
	std::vector<Action*>& actionsQueue,
	int& cost) const
{
	bool foundGraph = false;

	for (auto& action : possibleActions)
	{
		if (action == goal)
			continue;

		//if the goal passed as a parameter is nullptr or its prectype is no action
		// it has reached the end of the possible graph , so break
	
		if (goal->getPrecondition() == nullptr ||
			goal->getPrecondition()->getPrecType() == ActionType::NO_ACTION)
		{
			foundGraph = true;
			break;
		}

		//If goal=true, break
		if (goal->getPrecondition()->checkPreconditionOnGs(actualState))
			break;

		// Check the compatibility of enums
		// If true, the effect meets the condition
		if (goal->getPrecondition()->checkPrecondition(action->getEffect()->getEffectType()))
		{

			cost += action->getCost();


			// Add the action to the list
			actionsQueue.push_back(action);

			
			foundGraph = true;

			// If compatible, we add to the table of possible actions
			const bool found = buildGraph(possibleActions, actualState, action, actionsQueue, cost);
		}

		
	}

	return foundGraph;
}
