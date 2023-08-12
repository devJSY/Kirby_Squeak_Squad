#include "syStar_Effect.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syTime.h"
#include "syPlayer.h"
#include "syCollider.h"

namespace sy
{
	Star_Effect::Star_Effect(GameObject* owner, Vector2 pos)
		: Effects(owner)
		, mAnimator(nullptr)
	{
		GetComponent<Transform>()->SetPosition(pos);

		AddComponent<Collider>()->SetSize(Vector2(20.f, 20.f));

		// 텍스쳐 로드
		Texture* Star_Effect_Tex = ResourceManager::Load<Texture>(L"Star_Effect_Tex", L"..\\Resources\\Effect\\Star_Effect.bmp");
		Texture* Star_Effect_Dead_Tex = ResourceManager::Load<Texture>(L"Star_Effect_Dead_Tex", L"..\\Resources\\Effect\\Star_Effect_Dead.bmp");

		mAnimator = GetComponent<Animator>();

		mAnimator->CreateAnimation(Star_Effect_Tex, L"Star_Effect", Vector2(0.f, 0.f), Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.05f, 6);
		mAnimator->CreateAnimation(Star_Effect_Dead_Tex, L"Star_Effect_Dead", Vector2(0.f, 0.f), Vector2(70.f, 70.f), Vector2(70.f, 0.f), 0.1f, 3);

		mAnimator->PlayAnimation(L"Star_Effect", true);
	}

	Star_Effect::~Star_Effect()
	{
	}

	void Star_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Star_Effect::Update()
	{
		static float time = 0.f;
		time += Time::DeltaTime();

		if (time > 3.f)
		{
			mAnimator->PlayAnimation(L"Star_Effect_Dead", false);
			time = 0.f;
		}

		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void Star_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Star_Effect::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}