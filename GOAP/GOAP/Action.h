#pragma once
#include <functional>
#include <vector>

class Action;
class GameState;

//All Action
enum ActionType
{
	BUILD_ARMOR,
	STOCK_IRON,
	HAVE_PICKAXE,
	BUILD_PICKAXE,
	//STEAL_IRON_TO_THE_NEXT_VILLAGE,
	NO_ACTION 
};


// The effect class responds to the condition and applies the action on the gamestate

class Effect
{
private:
	ActionType effect;
	//Stored lambda that will be applied on a gamestate ref
	std::function<void(GameState&)> effectFunction; 
public:
	Effect() = default;
	Effect(const ActionType c) : effect(c) {}

	~Effect();

	//apply the effect to a given gamestate
	void applyEffect(GameState& gs) const; 

	void setEffect(std::function<void(GameState&)> fctn)
	{
		effectFunction = std::move(fctn);
	}
	ActionType getEffectType() const
	{
		return this->effect;
	}
};

//The precondition class asks another action if its effect matches
//when applying the effects, asks the Gamestate if it is necessary to apply this effect

class Precondition
{
	ActionType condition;
	std::function<bool(const GameState&)> preconditionFunction;
public:
	Precondition() = default;
	Precondition(const ActionType c) : condition(c) {}

	~Precondition();

	bool checkPreconditionOnGs(const GameState& gs) const
	{
		return preconditionFunction(gs);
	}

	void setPrecondition(std::function<bool(const GameState&)> fctn)
	{
		preconditionFunction = std::move(fctn);
	}

	bool checkPrecondition(const ActionType c) const;
	ActionType getPrecType() const
	{
		return this->condition;
	}
};

//main class, Contains a precondition, an effect and a move

class Action
{
	uint8_t cost;

	Precondition* precondition;
	Effect* effect;
public:
	Action();
	Action(int cst);

	~Action();

	void setEffect(Effect* e);
	void setPrecondition(Precondition* p);

	void performAction(GameState& gs) const;

	bool checkPreconditions(const Action& a) const;

	const Precondition* getPrecondition() const
	{
		return this->precondition;
	}
	const Effect* getEffect() const
	{
		return this->effect;
	}
	const int getCost() const
	{
		return this->cost;
	}
};