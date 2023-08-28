#include "syMetaKnight_SlashSkill.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syMetaKnight.h"
#include "syPlayer.h"


namespace sy
{
	MetaKnight_SlashSkill::MetaKnight_SlashSkill(MetaKnight* owner)
		: Effects(owner)
	{
	}

	MetaKnight_SlashSkill::~MetaKnight_SlashSkill()
	{
	}

	void MetaKnight_SlashSkill::Initialize()
	{
		Effects::Initialize();
	}

	void MetaKnight_SlashSkill::Update()
	{
		Effects::Update();
	}

	void MetaKnight_SlashSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void MetaKnight_SlashSkill::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void MetaKnight_SlashSkill::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}