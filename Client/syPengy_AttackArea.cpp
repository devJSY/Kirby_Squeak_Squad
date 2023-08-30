#include "syPengy_AttackArea.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syPengy.h"
#include "syPlayer.h"
#include "syResourceManager.h"
#include "sySound.h"

namespace sy
{
	Pengy_AttackArea::Pengy_AttackArea(Pengy* owner)
		: Effects(owner)
		, mOwner(owner)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(50.f, 30.f));

		if (mOwner != nullptr)
		{
			if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)			
				col->SetOffset(Vector2(35.f, 0.f));			
			else			
				col->SetOffset(Vector2(-35.f, 0.f));				
		}

		ResourceManager::Load<Sound>(L"IceSkill_Sound", L"..\\Resources\\Sound\\Effect\\IceSkill.wav")->Play(true);
	}

	Pengy_AttackArea::~Pengy_AttackArea()
	{
	}

	void Pengy_AttackArea::Initialize()
	{
		Effects::Initialize();
	}

	void Pengy_AttackArea::Update()
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		// Pengy가 특정상태가 아니면 삭제
		if (mOwner == nullptr
			|| !(mOwner->GetPengyState() == ePengyState::AttackReady
				|| mOwner->GetPengyState() == ePengyState::Attack))
		{
			Destroy(this);
			ResourceManager::Find<Sound>(L"IceSkill_Sound")->Stop(true);
		}

		Effects::Update();
	}

	void Pengy_AttackArea::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Pengy_AttackArea::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Pengy_AttackArea::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}