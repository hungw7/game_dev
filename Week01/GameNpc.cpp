#include "GameNpc.h"

void CGameNpc::Update(DWORD dt)
{
	this->position.x += this->velocity.x * dt;
	this->position.y += this->velocity.y * dt;
	//CGameObject::Update(dt);

	//int backbufferWidth = CGame::Get_instance()->Get_backbuffer_width();
	//int backbufferHeight = CGame::Get_instance()->Get_backbuffer_height();

	//// clock
	//Npc_move_follow_clock(backbufferHeight, backbufferWidth);

	// reverse clock
	//Npc_move_reverse_clock(backbufferHeight, backbufferWidth);
}

void CGameNpc::Npc_move_follow_clock(int backbufferHeight, int backbufferWidth)
{
	switch (this->state)
	{
	case NPC_STATE_MOVING_UP:
		if (this->position.y < 0) {
			CGameObject::SetNewY(NPC_START_Y);
			CGameNpc::SetState(NPC_STATE_MOVING_RIGHT);
		}
		break;
	case NPC_STATE_MOVING_DOWN:
		if (this->position.y > backbufferHeight - PLAYER_HEIGHT) {
			CGameObject::SetNewY(backbufferHeight - PLAYER_HEIGHT);
			CGameNpc::SetState(NPC_STATE_MOVING_LEFT);
		}
		break;
	case NPC_STATE_MOVING_RIGHT:
		if (this->position.x > backbufferWidth - PLAYER_WIDTH) {
			CGameObject::SetNewX(backbufferWidth - PLAYER_WIDTH);
			CGameNpc::SetState(NPC_STATE_MOVING_DOWN);
		}
		break;
	case NPC_STATE_MOVING_LEFT:
		if (this->position.x < 0) {
			CGameObject::SetNewX(NPC_START_X);
			CGameNpc::SetState(NPC_STATE_MOVING_UP);
		}
		break;
	default:
		break;
	}
}

void CGameNpc::Npc_move_reverse_clock(int backbufferHeight, int backbufferWidth)
{
	switch (this->state)
	{
	case NPC_STATE_MOVING_UP:
		if (this->position.y < 0) {
			CGameObject::SetNewY(NPC_START_Y);
			CGameNpc::SetState(NPC_STATE_MOVING_LEFT);
		}
		break;
	case NPC_STATE_MOVING_DOWN:
		if (this->position.y > backbufferHeight - PLAYER_HEIGHT) {
			CGameObject::SetNewY(backbufferHeight - PLAYER_HEIGHT);
			CGameNpc::SetState(NPC_STATE_MOVING_RIGHT);
		}
		break;
	case NPC_STATE_MOVING_RIGHT:
		if (this->position.x > backbufferWidth - PLAYER_WIDTH) {
			CGameObject::SetNewX(backbufferWidth - PLAYER_WIDTH);
			CGameNpc::SetState(NPC_STATE_MOVING_UP);
		}
		break;
	case NPC_STATE_MOVING_LEFT:
		if (this->position.x < 0) {
			CGameObject::SetNewX(NPC_START_X);
			CGameNpc::SetState(NPC_STATE_MOVING_DOWN);
		}
		break;
	default:
		break;
	}
}

void CGameNpc::Render()
{
	int animation = CGameNpc::GetState();
	this->animations[animation]->Render(this->position.x, this->position.y);
}

int CGameNpc::GetState()
{
	switch (this->state)
	{
	case NPC_STATE_MOVING_LEFT:
		return NPC_ANIMATION_MOVING_LEFT;
	case NPC_STATE_MOVING_DOWN:
		return NPC_ANIMATION_MOVING_DOWN;
	case NPC_STATE_MOVING_UP:
		return NPC_ANIMATION_MOVING_UP;
	default:
		return NPC_ANIMATION_MOVING_RIGHT;
	}
}

void CGameNpc::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case NPC_STATE_MOVING_RIGHT:
		this->velocity.x = NPC_MOVING_SPEED;
		this->velocity.y = 0;
		break;
	case NPC_STATE_MOVING_LEFT:
		this->velocity.x = -NPC_MOVING_SPEED;
		this->velocity.y = 0;
		break;
	case NPC_STATE_MOVING_DOWN:
		this->velocity.x = 0;
		this->velocity.y = NPC_MOVING_SPEED;
		break;
	case NPC_STATE_MOVING_UP:
		this->velocity.x = 0;
		this->velocity.y = -NPC_MOVING_SPEED;
		break;
	default:
		break;
	}
}
