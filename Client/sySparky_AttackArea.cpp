#include "sySparky_AttackArea.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "sySparky.h"
#include "syPlayer.h"
#include "syResourceManager.h"
#include "sySound.h"

namespace sy
{
	Sparky_AttackArea::Sparky_AttackArea(Sparky* owner)
		: Effects(owner)
		, mOwner(owner)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		Collider* col = AddComponent<Collider>();
		col->SetColliderType(eColliderType::Sphere);
		col->SetRadius(20.f);

		ResourceManager::Load<Sound>(L"SparkSound", L"..\\Resources\\Sound\\Effect\\Spark.wav")->Play(true);
	}

	Sparky_AttackArea::~Sparky_AttackArea()
	{
	}

	void Sparky_AttackArea::Initialize()
	{
		Effects::Initialize();
	}

	void Sparky_AttackArea::Update()
	{
		// Sparky가 특정상태가 아니면 삭제
		if (mOwner == nullptr
			|| mOwner->GetGameObjectState() == eGameObjectState::Dead
			|| !(mOwner->GetSparkyState() == eSparkyState::AttackReady
				|| mOwner->GetSparkyState() == eSparkyState::Attack))
		{
			Destroy(this);
			ResourceManager::Find<Sound>(L"SparkSound")->Stop(true);
		}

		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Effects::Update();
	}

	void Sparky_AttackArea::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Sparky_AttackArea::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Sparky_AttackArea::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}