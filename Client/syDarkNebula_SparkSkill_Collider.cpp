#include "syDarkNebula_SparkSkill_Collider.h"
#include "syDarkNebula.h"
#include "syTime.h"
#include "syTransform.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"

namespace sy
{
	DarkNebula_SparkSkill_Collider::DarkNebula_SparkSkill_Collider(Vector2 pos, Vector2 Size)
	{
		GetComponent<Transform>()->SetPosition(pos);
		AddComponent<Collider>()->SetSize(Size);
	}

	DarkNebula_SparkSkill_Collider::~DarkNebula_SparkSkill_Collider()
	{
	}

	void DarkNebula_SparkSkill_Collider::Initialize()
	{
		GameObject::Initialize();
	}

	void DarkNebula_SparkSkill_Collider::Update()
	{
		GameObject::Update();
	}

	void DarkNebula_SparkSkill_Collider::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DarkNebula_SparkSkill_Collider::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// Damage 상태에선 무시
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
		if (kirby != nullptr && kirby->IsDamagedState())
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void DarkNebula_SparkSkill_Collider::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// Damage 상태에선 무시
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
		if (kirby != nullptr && kirby->IsDamagedState())
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}