#pragma once
#ifndef _BRICK_H
#define _BRICK_H

#include "GameObject.h"

class CBrick : public CGameObject {
public:
	CBrick(); // WARM: not used anymore
	CBrick(Vector2D boundingBox);

	void Update(DWORD dt);
	void Render();
};

#endif // !_BRICK_H
