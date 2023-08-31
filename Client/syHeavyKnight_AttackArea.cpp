#include "syHeavyKnight_AttackArea.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syHeavyKnight.h"
#include "syPlayer.h"
#include "syResourceManager.h"
#include "sySound.h"

namespace sy
{
	HeavyKnight_AttackArea::HeavyKnight_AttackArea(HeavyKnight* owner)
		: Effects(owner)
		, mOwner(owner)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(30.f, 30.f));

		if (mOwner != nullptr)
		{
			if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
				col->SetOffset(Vector2(35.f, 0.f));
			else
				col->SetOffset(Vector2(-35.f, 0.f));
		}
	}

	HeavyKnight_AttackArea::~HeavyKnight_AttackArea()
	{
	}

	void HeavyKnight_AttackArea::Initialize()
	{
		Effects::Initialize();
	}

	void HeavyKnight_AttackArea::Update()
	{
		// HeavyKnight가 특정상태가 아니면 삭제
		if (mOwner == nullptr
			|| mOwner->GetGameObjectState() == eGameObjectState::Dead
			|| !(mOwner->GetHeavyKnightState() == eHeavyKnightState::SlashReady
				|| mOwner->GetHeavyKnightState() == eHeavyKnightState::Slash))
		{
			Destroy(this);
		}

		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Effects::Update();
	}

	void HeavyKnight_AttackArea::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void HeavyKnight_AttackArea::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void HeavyKnight_AttackArea::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}