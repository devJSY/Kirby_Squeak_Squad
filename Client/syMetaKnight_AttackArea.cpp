#include "syMetaKnight_AttackArea.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syMetaKnight.h"
#include "syPlayer.h"

namespace sy
{
	MetaKnight_AttackArea::MetaKnight_AttackArea(MetaKnight* owner, Vector2 ColliderSize)
		: Effects(owner)
		, mOwner(owner)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		Collider* col = AddComponent<Collider>();
		col->SetSize(ColliderSize);

		if (mOwner != nullptr)
		{
			if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
			{
				if (mOwner->GeteMetaKnightState() == eMetaKnightState::DashAttack)
					col->SetOffset(Vector2(25.f, 0.f));
				else if (mOwner->GeteMetaKnightState() == eMetaKnightState::Slash)
					col->SetOffset(Vector2(25.f, 0.f));
				else if (mOwner->GeteMetaKnightState() == eMetaKnightState::SlashSkill)
					col->SetOffset(Vector2(25.f, 0.f));
				else if (mOwner->GeteMetaKnightState() == eMetaKnightState::SpinAttack)
					col->SetOffset(Vector2::Zero);
			}
			else
			{
				if (mOwner->GeteMetaKnightState() == eMetaKnightState::DashAttack)
					col->SetOffset(Vector2(-25.f, 0.f));
				else if (mOwner->GeteMetaKnightState() == eMetaKnightState::Slash)
					col->SetOffset(Vector2(-25.f, 0.f));
				else if (mOwner->GeteMetaKnightState() == eMetaKnightState::SlashSkill)
					col->SetOffset(Vector2(-25.f, 0.f));
				else if (mOwner->GeteMetaKnightState() == eMetaKnightState::SpinAttack)
					col->SetOffset(Vector2::Zero);
			}
		}
	}

	MetaKnight_AttackArea::~MetaKnight_AttackArea()
	{
	}

	void MetaKnight_AttackArea::Initialize()
	{
		Effects::Initialize();
	}

	void MetaKnight_AttackArea::Update()
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		// MetaKnight가 특정상태가 아니면 삭제
		if (mOwner == nullptr
			|| mOwner->GetGameObjectState() == eGameObjectState::Dead
			|| !(mOwner->GeteMetaKnightState() == eMetaKnightState::DashAttack
				|| mOwner->GeteMetaKnightState() == eMetaKnightState::Slash
				|| mOwner->GeteMetaKnightState() == eMetaKnightState::SlashSkill
				|| mOwner->GeteMetaKnightState() == eMetaKnightState::SpinAttack))
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void MetaKnight_AttackArea::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void MetaKnight_AttackArea::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void MetaKnight_AttackArea::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}