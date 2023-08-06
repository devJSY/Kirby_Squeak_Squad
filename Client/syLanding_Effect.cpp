#include "syLanding_Effect.h"
#include "syTransform.h"
#include "syTexture.h"
#include "sySpriteRenderer.h"
#include "syResourceManager.h"
#include "syTime.h"
#include "syPlayer.h"

namespace sy
{
	Landing_Effect::Landing_Effect(Player* owner)
		: Effects(owner)
		, mDir()
		, mDuration(0.f)
	{
		Texture* Landing_Effect_tex = ResourceManager::Load<Texture>(L"Landing_Effect", L"..\\Resources\\Effect\\Landing_Effect.bmp");

		mTransform = GetComponent<Transform>();
		Vector2 vec = GetOwner()->GetComponent<Transform>()->GetPosition();
		mTransform->SetPosition(vec);

		SpriteRenderer* spriteRenderer = AddComponent<SpriteRenderer>();
		spriteRenderer->SetTexture(Landing_Effect_tex);		

		int randomNumber = std::rand() % 4; // 0부터 3까지의 랜덤 정수 생성
		mDir = (eLandingDir)randomNumber;
	}

	Landing_Effect::~Landing_Effect()
	{
	}

	void Landing_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Landing_Effect::Update()
	{
		Vector2 Dir = Vector2::Zero;

		if (mDir == eLandingDir::LeftTop)
			Dir = Vector2(-1.f, 1.f);
		else if (mDir == eLandingDir::RightTop)
			Dir = Vector2(1.f, 1.f);
		else if (mDir == eLandingDir::LeftBotton)
			Dir = Vector2(-1.f, -1.f);
		else if (mDir == eLandingDir::RightBotton)
			Dir = Vector2(1.f, -1.f);

		Dir.Normalize();

		Dir *= 100.f * Time::DeltaTime();

		Vector2 pos = mTransform->GetPosition();
		pos += Dir;
		mTransform->SetPosition(pos);

		mDuration += Time::DeltaTime();

		if (mDuration > 0.2f)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void Landing_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}
