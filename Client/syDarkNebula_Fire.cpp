#include "syDarkNebula_Fire.h"
#include "syDarkNebula.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syTime.h"
#include "sySceneManager.h"

namespace sy
{
	DarkNebula_Fire::DarkNebula_Fire(DarkNebula* owner, Vector2 pos)
		: Effects(owner)
		, mDuration(0.f)
	{
		pos.y -= 9.f;
		GetComponent<Transform>()->SetPosition(pos);
		AddComponent<Collider>()->SetSize(Vector2(18.f, 18.f));

		// 애니메이션 생성
		Animator* animator = GetComponent<Animator>();
		Texture* DarkNebula_Fire_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Fire_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Fire.bmp");

		animator->CreateAnimation(DarkNebula_Fire_Tex, L"DarkNebula_Fire", Vector2::Zero, Vector2(18.f, 18.f), Vector2(18.f, 0.f), 0.05f, 4);

		animator->PlayAnimation(L"DarkNebula_Fire", true);
	}

	DarkNebula_Fire::~DarkNebula_Fire()
	{
	}

	void DarkNebula_Fire::Initialize()
	{
		Effects::Initialize();
	}

	void DarkNebula_Fire::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 3.f)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void DarkNebula_Fire::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void DarkNebula_Fire::OnCollisionEnter(Collider* other)
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