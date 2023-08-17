#include "syDarkNebula_Star.h"
#include "syDarkNebula.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syTime.h"

namespace sy
{
	DarkNebula_Star::DarkNebula_Star(DarkNebula* owner, Vector2 Dir)
		: Effects(owner)
		, mTransform(nullptr)
		, mDir(Dir)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		AddComponent<Collider>()->SetSize(Vector2(20.f, 21.f));

		// 애니메이션 생성
		Animator* animator = GetComponent<Animator>();
		Texture* DarkNebula_Star_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Star_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Star.bmp");

		animator->CreateAnimation(DarkNebula_Star_Tex, L"DarkNebula_Star", Vector2::Zero, Vector2(20.f, 21.f), Vector2(20.f, 0.f), 0.05f, 8);

		animator->PlayAnimation(L"DarkNebula_Star", true);
	}

	DarkNebula_Star::~DarkNebula_Star()
	{

	}
	void DarkNebula_Star::Initialize()
	{
		Effects::Initialize();
	}

	void DarkNebula_Star::Update()
	{
		Vector2 pos = mTransform->GetPosition();
		mDir.Normalize();
		pos += mDir * 200.f * Time::DeltaTime();
		mTransform->SetPosition(pos);

		mDuration += Time::DeltaTime();

		if (mDuration > 5.f)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void DarkNebula_Star::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void DarkNebula_Star::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// Inhale 상태에선 무시
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
		if (kirby != nullptr)
		{
			if (kirby->GetKirbyState() == eDefaultKirbyState::Inhale_1 || kirby->GetKirbyState() == eDefaultKirbyState::Inhale_2)
				return;

			// DefaultKirby가 Damage 상태면 적용하지않음
			if (kirby->IsDamagedState())
				return;
		}

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}