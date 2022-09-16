#include "GameMaster.h"

#include <cassert>
#include <ctime>
#include <iostream>

//Function to wait
void GameMaster::waitForMilliseconds(int milli)
{
	
	clock_t end_time;
	end_time = clock() + milli * CLOCKS_PER_SEC / 1000;
	while (clock() < end_time)
	{
		
	}
}

void GameMaster::StartGame()
{
	//create planner
	goap = new GOAPPlanner();
	std::cout << "Je dois construire 5 armures pour le roi. "  << std::endl;
	// creation of the various necessary preconditions
	Precondition* ironPrec = new Precondition(ActionType::STOCK_IRON);
	ironPrec->setPrecondition([](const GameState& gs)
		{
			
			//if gamstate have 150 de iron or more
			if (gs.ironStock >= 150)
			{
				return true;
			}
				

			
			return false;
		});

	Precondition* havePickaxePrec = new Precondition(ActionType::HAVE_PICKAXE);
	havePickaxePrec->setPrecondition([](const GameState& gs)
		{
			//this precondition can be achieved when
			//the gamestate is equipped with an pickaxe
			return gs.hasPickaxe;
		});


	Precondition* buildPickaxePrec = new Precondition(ActionType::BUILD_PICKAXE);
	buildPickaxePrec->setPrecondition([](const GameState& gs)
		{
			//this precondition can be achieved when
			//the gamestate has pickaxe, and it is no longer equipped with a pickaxe
			return gs.availablePickaxe > 0 && !gs.hasPickaxe;
		});

	

	
	/*
	* Precondition* StealIronBeforeBuildPickaxePrec = new Precondition(ActionType::STEAL_IRON_TO_THE_NEXT_VILLAGE);
	StealIronBeforeBuildPickaxePrec->setPrecondition([](const GameState& gs)
		{
			
			return gs.canSteal;
		});
	*/
	

	Precondition* beforeBuildPickaxePrec = new Precondition(ActionType::NO_ACTION);
	beforeBuildPickaxePrec->setPrecondition([](const GameState& gs)
		{
			//this precondition can be achieved when
			//the gamestate has no pickaxe, and it is no longer equipped with a pickaxe

			return gs.availablePickaxe < 1 && !gs.hasPickaxe;
		});

	Precondition* ironOrePrec = new Precondition(ActionType::NO_ACTION);
	ironOrePrec->setPrecondition([](const GameState& gs)
		{
			return true;
		});

	// ---------------------------------------------------------------------------------

	//create effects
	Effect* armorEffect = new Effect(ActionType::BUILD_ARMOR);
	armorEffect->setEffect([](GameState& gs)
		{
			gs.ironStock -= 150;
			gs.craftedArmor += 1;

			std::cout << "J'ai construit une armure !! " << gs.craftedArmor << std::endl;
		});

	Effect* stockIronEffect = new Effect(ActionType::STOCK_IRON);
	stockIronEffect->setEffect([](GameState& gs)
		{
			gs.ironStock += 10;
			gs.pickaxeEnergy -= 2;

			std::cout << "Je recolte un filon Fer !! + 10 :::: " << gs.ironStock << std::endl;
			std::cout << "Ma pioche perd en energie !! " << gs.pickaxeEnergy << std::endl;
			
			gs.awareness -= 5;
			if (gs.awareness <= 0)
			{
				gs.awareness = 0;
			}
			std::cout << "Vigilance :  " << gs.awareness << std::endl;

			if (gs.pickaxeEnergy <= 0)
			{
				gs.hasPickaxe = false;
				gs.canSteal = true;
				std::cout << "Je n'ai plus de pioche ... mais je peux peut être voler du fer chez le village voisin" << std::endl;
			}
		});

	Effect* stockIronOreEffect = new Effect(ActionType::STOCK_IRON);
	stockIronOreEffect->setEffect([](GameState& gs)
		{
			gs.ironStock += 1;
			std::cout << "Je recolte un mineraie de fer  !! + 1 :::: " << gs.ironStock << std::endl;
			gs.awareness -= 15;
			std::cout << "Vigilance :  " << gs.awareness << std::endl;

		});
	
	
	
	

	Effect* pickupPickaxeEffect = new Effect(ActionType::HAVE_PICKAXE);
	pickupPickaxeEffect->setEffect([](GameState& gs)
		{
			std::cout << "J'ai pris une pioche !!" << std::endl;

			gs.hasPickaxe = true;
			gs.availablePickaxe -= 1;
			gs.pickaxeEnergy = 6;
		});

	Effect* buildPickaxeEffect = new Effect(ActionType::BUILD_PICKAXE);
	buildPickaxeEffect->setEffect([](GameState& gs)
		{
			if (gs.awareness < 50 && gs.canSteal)
			{
				gs.ironStock += 25;

				std::cout << "Je vais voler du fer dans le village voisin + 25 ::::  " << gs.ironStock << std::endl;
				gs.awareness += 40;
				std::cout << "Vigilance :  " << gs.awareness << std::endl;
			}
			else if(gs.awareness > 50 && gs.canSteal)
			{
				std::cout << "La vigilance du village voisin est trop haute pour voler ...  " << gs.awareness << std::endl;
				std::cout << "Vigilance :  " << gs.awareness << std::endl;
			}
			std::cout << "Je construit une pioche !!" << std::endl;
			gs.availablePickaxe += 1;
		});

	// ---------------------------------------------------------------------------------

	//create action
	goal = new Action(5);
	goal->setEffect(armorEffect);
	goal->setPrecondition(ironPrec);

	Action* stockIronOre = new Action(20);
	stockIronOre->setEffect(stockIronOreEffect);
	stockIronOre->setPrecondition(ironOrePrec);

	Action* stockIron = new Action(1);
	stockIron->setEffect(stockIronEffect);
	stockIron->setPrecondition(havePickaxePrec);

	Action* pickupPickaxe = new Action(1);
	pickupPickaxe->setEffect(pickupPickaxeEffect);
	pickupPickaxe->setPrecondition(buildPickaxePrec);


	Action* buildPickaxe = new Action(1);
	buildPickaxe->setEffect(buildPickaxeEffect);
	buildPickaxe->setPrecondition(beforeBuildPickaxePrec);

	// ---------------------------------------------------------------------------------

	//create gamestate
	currentGameState = new GameState();

	//allocate space to possible actions
	availableActions.reserve(10);

	//add the actions
	availableActions.push_back(goal);
	availableActions.push_back(stockIron);
	availableActions.push_back(pickupPickaxe);
	availableActions.push_back(buildPickaxe);
	availableActions.push_back(stockIronOre);
}

void GameMaster::UdapteGame()
{

	while (currentGameState->craftedArmor < 5)
	{
		//looking for the optimal action plan
		std::vector<Action*> plan = goap->plan(availableActions, *currentGameState, goal);

		//check that there is at least 1 action
		assert(!plan.empty(), " PLAN EMPTY");

		//apply the actions from the end
		for (int i = plan.size() - 1; i >= 0; --i)
		{
			//if the condition on the Gamestate is valid
			if (plan[i]->getPrecondition()->checkPreconditionOnGs(*currentGameState))
			{
				
				plan[i]->performAction(*currentGameState);
			}

			
			waitForMilliseconds(1000);
		}

		std::cout << "\n" << std::endl;

		//check goal
		if (goal->getPrecondition()->checkPreconditionOnGs(*currentGameState))
		{
			goal->getEffect()->applyEffect(*currentGameState);
		}

		//clear le plan
		
		plan.clear();

		waitForMilliseconds(1000);
	}
}


void GameMaster::DeleteGame()
{

	for (auto a : availableActions)
	{
		if (a != nullptr)
		{
			delete a;
			a = nullptr;
		}
	}
	availableActions.clear();

	//destroy gamestate
	if (currentGameState != nullptr)
	{
		delete currentGameState;
		currentGameState = nullptr;
	}

	//destroy planner
	if (goap != nullptr)
	{
		delete goap;
		goap = nullptr;
	}

}