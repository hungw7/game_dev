#pragma once
#ifndef _GAMEPLAYER_H
#define _GAMEPLAYER_H

#include "GameObject.h"
#include "InputHandler.h"
#include "ControllerObject.h"
#include "SophiaWheel.h"
#include "SophiaBody.h"
#include "SophiaCabin.h"
#include "SophiaGun.h"

class CSophiaCabin;
class CSophiaWheel;
class CSophiaBody;
class CSophiaGun;

enum SophiaDirectState
{
	Stay = 0,
	RightMove = 1,
	LeftMove = -1
};

enum SophiaActionState {
	Idle = 0,
	Tile45 = 1,
	Up90 = 2,
};

class CSophia : public CGameObject, public CControllerObject
{
private:
	CSophiaWheel* leftWheel;
	CSophiaWheel* rightWheel;
	CSophiaBody* body;
	CSophiaCabin* cabin;
	CSophiaGun* gun;

	SophiaDirectState directState;
	SophiaActionState actionState;

public:
	DWORD stateTime;
	DWORD prevStateTime;

	CSophia();

	void Update(DWORD dt);
	void Render();
	void ListenKeyEvent();

	void SubcribeDirectState(SophiaDirectState directState);
	void SubcribeActionState(SophiaActionState actionState);

	void EdgeCollisionHandler(int width);

	SophiaDirectState GetDirectState() { return directState; }
	SophiaActionState GetActionState() { return actionState; }

	CSophiaWheel* GetLeftWheel() { return this->leftWheel; }
	CSophiaWheel* GetRightWheel() { return this->rightWheel; }
};

#endif // !_GAMEPLAYER_H

