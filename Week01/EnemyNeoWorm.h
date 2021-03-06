#pragma once
#ifndef _ENEMY_NEO_WORM_H
#define _ENEMY_NEO_WORM_H

#include "EnemyBase.h"

class CEnemyNeoWorm : public CEnemyBase {
private:
	DWORD bornTime = GetTickCount64();

	bool ground = false;

public:
	CEnemyNeoWorm();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_NEO_WORM_H