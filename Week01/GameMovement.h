#pragma once
#ifndef _GAMEMOVEMENT_H
#define _GAMEMOVEMENT_H

#include "resources.h"
#include <math.h>

void LinearMoveWithGravity(Vector2D& position, Vector2D& velocity, DWORD dt);
void LinearMove(Vector2D& position, Vector2D& velocity, DWORD dt);

#endif // !_GAMEMOVEMENT_H
