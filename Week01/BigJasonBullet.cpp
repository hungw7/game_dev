#include "BigJasonBullet.h"
#include "Camera.h"
#include "Brick.h"
#include "EnemyGX-680.h"
#include "EnemyGX-680S.h"

#define V_BOXSIZE_HORIZON			Vector2D(8.0f, 6.0f)
#define V_BOXSIZE_VERTICAL			Vector2D(6.0f, 6.0f)

#define BIGJASON_BULLET_VELOCITY	0.2f

#define SPRITE_DEFAULT_ID			"df"

CBigJasonBullet::CBigJasonBullet(BigJasonBulletDirection state)
{
	this->directState = state;
	this->damage = 10;

	CCollider2D* collider = new CCollider2D(this, true, false);
	collider->SetOffset(VectorZero());
	switch (this->directState)
	{
	case BigJasonBulletDirection::LEFT:
		this->AddSprite(SPRITE_DEFAULT_ID, "sprBJBullet00");
		this->velocity.x = -BIGJASON_BULLET_VELOCITY;
		this->nx = -1;
		collider->SetBoxSize(V_BOXSIZE_HORIZON);
		break;

	case BigJasonBulletDirection::RIGHT:
		this->AddSprite(SPRITE_DEFAULT_ID, "sprBJBullet00");
		this->velocity.x = BIGJASON_BULLET_VELOCITY;
		this->nx = 1;
		collider->SetBoxSize(V_BOXSIZE_HORIZON);
		break;

	case BigJasonBulletDirection::UP:
		this->AddSprite(SPRITE_DEFAULT_ID, "sprBJBullet01");
		this->velocity.y = BIGJASON_BULLET_VELOCITY;
		this->nx = 1;
		collider->SetBoxSize(V_BOXSIZE_VERTICAL);
		break;

	case BigJasonBulletDirection::DOWN:
		this->AddSprite(SPRITE_DEFAULT_ID, "sprBJBullet01");
		this->velocity.y = -BIGJASON_BULLET_VELOCITY;
		this->nx = -1;
		collider->SetBoxSize(V_BOXSIZE_VERTICAL);
		break;

	default:
		break;
	}
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CBigJasonBullet::Update(DWORD dt)
{
	auto camera = CCamera::GetInstance();
	if (!camera->GetBoundingBox().Contain(this->colliders.at(0)->GetBoundingBox())) {
		this->hp = 0;
	}
}

void CBigJasonBullet::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	this->sprites.at(SPRITE_DEFAULT_ID)->Draw(this->position, this->nx, color);
}

void CBigJasonBullet::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
	if (dynamic_cast<CBrick*>(coEvent->object)
		|| dynamic_cast<CBigJasonBullet*>(coEvent->object)) {
		this->hp = 0;
	}
	else if (dynamic_cast<CEnemyGX680*>(coEvent->object)
		|| dynamic_cast<CEnemyGX680S*>(coEvent->object)) {
		LPGAMEOBJECT thisObj = (LPGAMEOBJECT)this;
		coEvent->object->TakeDamage(thisObj);
		this->hp = 0;
	}
}

void CBigJasonBullet::OnTrigger(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
