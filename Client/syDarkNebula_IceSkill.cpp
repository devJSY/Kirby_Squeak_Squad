#include "syDarkNebula_IceSkill.h"
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
	DarkNebula_IceSkill::DarkNebula_IceSkill(DarkNebula* owner)
		: Effects(owner)
		, mTransform(nullptr)
	{
		mTransform = GetComponent<Transform>();
		Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		pos.y += 65.f;
		mTransform->SetPosition(pos);
		AddComponent<Collider>()->SetSize(Vector2(30.f, 130.f));

		// 애니메이션 생성
		Animator* animator = GetComponent<Animator>();
		Texture* DarkNebula_IceSkill_Tex = ResourceManager::Load<Texture>(L"DarkNebula_IceSkill_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_IceSkill.bmp");

		animator->CreateAnimation(DarkNebula_IceSkill_Tex, L"DarkNebula_IceSkill", Vector2::Zero, Vector2(60.f, 130.f), Vector2(60.f, 0.f), 0.05f, 4);

		animator->PlayAnimation(L"DarkNebula_IceSkill", true);
	}

	DarkNebula_IceSkill::~DarkNebula_IceSkill()
	{
	}

	void DarkNebula_IceSkill::Initialize()
	{
		Effects::Initialize();
	}

	void DarkNebula_IceSkill::Update()
	{
		Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		pos.y += 65.f;
		mTransform->SetPosition(pos);

		DarkNebula* owner = dynamic_cast<DarkNebula*>(GetOwner());
		if (owner->GetDarkNebulaState() != eDarkNebulaState::IceSkill)
		{
			Destroy(this);
		}		

		Effects::Update();
	}

	void DarkNebula_IceSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void DarkNebula_IceSkill::OnCollisionEnter(Collider* other)
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

	void DarkNebula_IceSkill::OnCollisionStay(Collider* other)
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