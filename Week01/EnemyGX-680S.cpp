#include "EnemyGX-680S.h"
#include "Player.h"
#include "BigDestroyEffect.h"
#include "ItemPower.h"
#include "GX680SBullet.h"

#define V_BOXSIZE					Vector2D(18.0f, 17.0f)

constexpr auto AnimationDefaultId = "df";
constexpr auto DetectedPlayerRadius = 120;
constexpr auto AttackPlayerRadius = 60;
constexpr auto OwnSpeed = 0.02f;
constexpr auto RateDropItemPower = 0.1f;
constexpr auto DelayAttackTime = 2200;

CEnemyGX680S::CEnemyGX680S()
{
	this->AddAnimation(AnimationDefaultId, "aniEGX680S");

	this->active = false;
	this->velocity = VectorZero();
	this->damage = 10;
	this->hp = 40;

	//
	CCollider2D* collider = new CCollider2D(this, true, false, VectorZero(), V_BOXSIZE);
	this->colliders.push_back(collider);
	this->SetColliders(this->colliders);
}

void CEnemyGX680S::Update(DWORD dt)
{
	if (!this->IsLive()) {
		CGame::GetInstance()->InitiateAndPushToQueue<CBigDestroyEffect>(this->position);
		
		float rate = (float)Random(1, 100) / 100;
		if (rate <= RateDropItemPower) {
			CGame::GetInstance()->InitiateAndPushToQueue<CItemPower>(this->position);
		}

		return;
	}

	LPGAMEOBJECT player = CPlayer::GetInstance()->GetPlayer();
	// detected player
	if (PositionsDistance(this->position, player->GetPosition()) < DetectedPlayerRadius) {
		this->active = true;
	}

	// auto move to player
	if (this->active == true) {
		Vector2D vDistance = player->GetPosition() - this->position - Vector2D(0, 12.0f);
		if (vDistance.x != 0) vDistance.x = vDistance.x / abs(vDistance.x);
		if (vDistance.y != 0) vDistance.y = vDistance.y / abs(vDistance.y);

		this->velocity.x = vDistance.x * OwnSpeed;
		this->velocity.y = vDistance.y * OwnSpeed;

		// attack player
		auto now = GetTickCount64();
		if (PositionsDistance(this->position, player->GetPosition()) < AttackPlayerRadius
			&& now - this->prevTimeAttack > DelayAttackTime) {
			CGame::GetInstance()->InitiateAndPushToQueue<CGX680SBullet>(this->position);
			this->prevTimeAttack = now;
		}
	}
}

void CEnemyGX680S::Render()
{
	D3DCOLOR color = this->GetRenderColor();
	animations.at(AnimationDefaultId)->Render(this->position, 1, color);
}

void CEnemyGX680S::OnCollision(CCollider2D* self, LPCOLLISIONEVENT coEvent)
{
}
