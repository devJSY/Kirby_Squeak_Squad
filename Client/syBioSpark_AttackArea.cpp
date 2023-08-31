#include "syBioSpark_AttackArea.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syBioSpark.h"
#include "syPlayer.h"
#include "syResourceManager.h"
#include "sySound.h"

namespace sy
{
	BioSpark_AttackArea::BioSpark_AttackArea(BioSpark* owner)
		: Effects(owner)
		, mOwner(owner)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(30.f, 15.f));

		if (mOwner != nullptr)
		{
			if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
				col->SetOffset(Vector2(15.f, 0.f));
			else
				col->SetOffset(Vector2(-15.f, 0.f));
		}
	}

	BioSpark_AttackArea::~BioSpark_AttackArea()
	{
	}

	void BioSpark_AttackArea::Initialize()
	{
		Effects::Initialize();
	}

	void BioSpark_AttackArea::Update()
	{
		// BioSpark가 특정상태가 아니면 삭제
		if (mOwner == nullptr
			|| !(mOwner->GetBioSparkState() == eBioSparkState::Attack))
		{
			Destroy(this);
		}

		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Effects::Update();
	}

	void BioSpark_AttackArea::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void BioSpark_AttackArea::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void BioSpark_AttackArea::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}