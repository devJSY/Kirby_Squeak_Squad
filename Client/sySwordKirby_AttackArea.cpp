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
		AddComponent<Collider>()->SetSize(ColliderSize);
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

		if (swordKirby != nullptr)  
		{
			if (swordKirby->GetKirbyState() == eSwordKirbyState::JumpAttack
				|| swordKirby->GetKirbyState() == eSwordKirbyState::Slash
				|| swordKirby->GetKirbyState() == eSwordKirbyState::Slashing)
			{
				Destroy(this);
			}
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

		// ��ų �� ���� ����
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

		// ��ų �� ���� ����
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}
}