#include "Action.h"


Action::Action()
{
	this->cost = 1;

	this->precondition = nullptr;
	this->effect = nullptr;
}

Action::Action(int cst) : cost(cst)
{
	this->precondition = nullptr;
	this->effect = nullptr;
}
Action::~Action()
{
	if (precondition != nullptr)
	{
		delete precondition;
		precondition = nullptr;
	}

	if (effect != nullptr)
	{
		delete effect;
		effect = nullptr;
	}

}

void Action::setPrecondition(Precondition* p)
{
	this->precondition = p;
}

void Action::setEffect(Effect* e)
{
	this->effect = e;
}



void Action::performAction(GameState& gs) const
{
	effect->applyEffect(gs);
}

bool Action::checkPreconditions(const Action& a) const
{


	return this->precondition->checkPrecondition(a.getEffect()->getEffectType());
}





Precondition::~Precondition()
{

}

bool Precondition::checkPrecondition(const ActionType oth) const
{
	
	return this->condition == oth;
}

void Effect::applyEffect(GameState& gs) const
{
	
	this->effectFunction(gs);
}

Effect::~Effect()
{

}
