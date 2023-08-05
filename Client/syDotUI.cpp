#include "syDotUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTime.h"

namespace sy
{
	DotUI::DotUI()
		: mAnimator(nullptr)
		, mDelayTime(0.f)
		, mActiveTrig(false)
	{
	}

	DotUI::~DotUI()
	{
	}

	void DotUI::Initialize()
	{
		Texture* Tex = ResourceManager::Load<Texture>(L"Dot", L"..\\Resources\\UI\\Dot.bmp");
		Texture* CreateDot_Tex = ResourceManager::Load<Texture>(L"CreateDot", L"..\\Resources\\Effect\\CreateDot.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(Tex, L"Dot", Vector2::Zero, Vector2(6.f, 6.f), Vector2(6.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(CreateDot_Tex, L"CreateDot", Vector2::Zero, Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.1f, 5);
		mAnimator->SetAffectedCamera(false);	

		UI::Initialize();
	}

	void DotUI::Update()
	{
		static float time = 0.f;

		if (mActiveTrig)
		{			
			time += Time::DeltaTime();

			if (time > mDelayTime)
			{
				mAnimator->PlayAnimation(L"CreateDot", false);
				mActiveTrig = false;
				time = 0.f;
			}
		}

		if (mAnimator->GetActiveAnimation() != nullptr
			&& mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"Dot", true);
		}		


		UI::Update();
	}

	void DotUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}