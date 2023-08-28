#include "syMetaKnight_TornadoSkill.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syMetaKnight.h"
#include "syPlayer.h"


namespace sy
{
	MetaKnight_TornadoSkill::MetaKnight_TornadoSkill(MetaKnight* owner)
		: Effects(owner)
	{
	}

	MetaKnight_TornadoSkill::~MetaKnight_TornadoSkill()
	{
	}

	void MetaKnight_TornadoSkill::Initialize()
	{
		Effects::Initialize();
	}

	void MetaKnight_TornadoSkill::Update()
	{
		Effects::Update();
	}

	void MetaKnight_TornadoSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void MetaKnight_TornadoSkill::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void MetaKnight_TornadoSkill::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}