#pragma once
#ifndef _ENEMY_STUKA_H
#define _ENEMY_STUKA_H

#include "EnemyBase.h"

#define C_STUKA			0
#define V_STUKA_BOXSIZE		Vector2D(18, 18)

class CEnemyStuka : public CEnemyBase {
private:
	int stepMove = 0;

public:
	CEnemyStuka();

	void Update(DWORD dt);
	void Render();

	void OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent);
	void OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent);
};

#endif // !_ENEMY_STUKA_H
