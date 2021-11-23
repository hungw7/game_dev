#pragma once
#ifndef _GAMENPC_H
#define _GAMENPC_H

#include "resources.h"
#include "GameObject.h"
#include "Game.h"

#define C_ROBOT 0

class CEnemyRobot : public CGameObject
{
public:
	CEnemyRobot();

	void Update(DWORD dt);
	void Render();
	
	int GetState();
	void SetState(int state);
};

#endif // !_GAMENPC_H
