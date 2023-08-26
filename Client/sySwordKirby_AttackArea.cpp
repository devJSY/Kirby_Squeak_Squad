#include "sySwordKirby_AttackArea.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "sySwordKirby.h"

namespace sy
{
	SwordKirby_AttackArea::SwordKirby_AttackArea(Player* owner, Vector2 ColliderSize)
		: Effects(owner)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		Collider* col = AddComponent<Collider>();
		col->SetSize(ColliderSize);

		Player* player = dynamic_cast<Player*>(GetOwner());
		SwordKirby* swordKirby = dynamic_cast<SwordKirby*>(player->GetActiveKirby());

		if (swordKirby != nullptr)
		{
			if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
			{
				if (swordKirby->GetKirbyState() == eSwordKirbyState::DownAttack)
					col->SetOffset(Vector2(10.f, 0.f));
				else if (swordKirby->GetKirbyState() == eSwordKirbyState::JumpAttack)
					col->SetOffset(Vector2::Zero);
				else if (swordKirby->GetKirbyState() == eSwordKirbyState::Slash)				
					col->SetOffset(Vector2(25.f, 0.f));
				else if (swordKirby->GetKirbyState() == eSwordKirbyState::Slashing)				
					col->SetOffset(Vector2(25.f, 0.f));
				else if (swordKirby->GetKirbyState() == eSwordKirbyState::UpperSlash)
					col->SetOffset(Vector2(15.f, 0.f));
			}
			else
			{
				if (swordKirby->GetKirbyState() == eSwordKirbyState::DownAttack)
					col->SetOffset(Vector2(-10.f, 0.f));
				else if (swordKirby->GetKirbyState() == eSwordKirbyState::JumpAttack)
					col->SetOffset(Vector2::Zero);
				else if (swordKirby->GetKirbyState() == eSwordKirbyState::Slash)
					col->SetOffset(Vector2(-25.f, 0.f));
				else if (swordKirby->GetKirbyState() == eSwordKirbyState::Slashing)
					col->SetOffset(Vector2(-25.f, 0.f));
				else if (swordKirby->GetKirbyState() == eSwordKirbyState::UpperSlash)
					col->SetOffset(Vector2(-15.f, 0.f));
			}
		}
	}

	SwordKirby_AttackArea::~SwordKirby_AttackArea()
	{
	}

	void SwordKirby_AttackArea::Initialize()
	{
		Effects::Initialize();
	}

	void SwordKirby_AttackArea::Update()
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Player* player = dynamic_cast<Player*>(GetOwner());
		SwordKirby* swordKirby = dynamic_cast<SwordKirby*>(player->GetActiveKirby());

		// swordKirby 가 아니거나 특정상태가 아니면 삭제
		if (swordKirby == nullptr 
			|| 	!(swordKirby->GetKirbyState() == eSwordKirbyState::DownAttack
				|| swordKirby->GetKirbyState() == eSwordKirbyState::JumpAttack
				|| swordKirby->GetKirbyState() == eSwordKirbyState::Slash
				|| swordKirby->GetKirbyState() == eSwordKirbyState::Slashing
				|| swordKirby->GetKirbyState() == eSwordKirbyState::UpperSlash))
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void SwordKirby_AttackArea::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void SwordKirby_AttackArea::OnCollisionEnter(Collider* other)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy == nullptr)
			return;

		Player* player = dynamic_cast<Player*>(GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 몬스터 방향
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}

	void SwordKirby_AttackArea::OnCollisionStay(Collider* other)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy == nullptr)
			return;

		Player* player = dynamic_cast<Player*>(GetOwner());

		if (player == nullptr)
			return;

		// Stay상태에서 Damage 상태면 적용하지않음
		if (enemy->IsDamagedState())
			return;

		// 스킬 → 몬스터 방향
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}
}