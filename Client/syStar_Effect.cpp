#include "syStar_Effect.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syTime.h"
#include "syPlayer.h"
#include "syCollider.h"
#include "syDefaultKirby.h"

namespace sy
{
	Star_Effect::Star_Effect(GameObject* owner, Vector2 pos)
		: Effects(owner)
		, mState(eStarState::Active)
		, mAnimator(nullptr)
		, mDuration(0.f)
	{
		GetComponent<Transform>()->SetPosition(pos);

		Collider* col = AddComponent<Collider>();
		col->SetColliderType(eColliderType::Sphere);
		col->SetRadius(15.f);

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
		switch (mState)
		{
		case eStarState::Active:
			Active();
			break;
		case eStarState::Dead:
			Dead();
			break;
		default:
			break;
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

		// Inhale 상태에선 무시
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
		if (kirby != nullptr)
		{
			if (kirby->GetKirbyState() == eDefaultKirbyState::Inhale_1 || kirby->GetKirbyState() == eDefaultKirbyState::Inhale_2)
				return;
		}

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Star_Effect::Active()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 3.f)
		{
			mAnimator->PlayAnimation(L"Star_Effect_Dead", false);
			mDuration = 0.f;
			mState = eStarState::Dead;
		}
	}

	void Star_Effect::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}