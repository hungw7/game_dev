#include "JasonDirectionState.h"

CJasonDirectionState::CJasonDirectionState()
{
}

CJasonDirectionState::CJasonDirectionState(CJason* target)
{
	this->target = target;
}

void CJasonDirectionState::SetTarget(CJason* target)
{
	this->target = target;
}

void CJasonDirectionState::SetState(JasonDirectState state)
{
	this->state = state;
}

JasonDirectState CJasonDirectionState::GetState()
{
	return this->state;
}

std::string CJasonDirectionState::MappingStateOfAnimation(JasonDirectState state)
{
	switch (state)
	{
	case JasonDirectState::LEFTWALK:
		return "walk";

	case JasonDirectState::RIGHTWALK:
		return "walk";

	case JasonDirectState::STAY:
		return "stay";

	default:
		return "stay";
	}
}

void CJasonDirectionState::Stay()
{
	auto targetAnimations = this->target->GetAnimations();
	auto key = MappingStateOfAnimation(this->GetState());

	auto animation = targetAnimations.at(key);
	animation->SetWait(true);
}

void CJasonDirectionState::MoveBackward()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations
		.at(MappingStateOfAnimation(this->GetState()));

	animation->SetReverse(false);
	animation->SetWait(false);
}

void CJasonDirectionState::MoveForward()
{
	auto targetAnimations = this->target->GetAnimations();
	auto animation = targetAnimations
		.at(MappingStateOfAnimation(this->GetState()));

	animation->SetReverse(true);
	animation->SetWait(false);
}
