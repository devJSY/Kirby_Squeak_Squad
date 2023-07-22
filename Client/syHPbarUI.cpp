#include "syHPbarUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syApplication.h"

namespace sy
{
	HPbarUI::HPbarUI()
		: mBar(nullptr)
		, mRed(nullptr)
		, mPink(nullptr)
	{
	}

	HPbarUI::~HPbarUI()
	{
	}

	void HPbarUI::Initialize()
	{
		//Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		//vec.x = 85.0f;
		//vec.y -= 12.f;
		//GetComponent<Transform>()->SetPosition(vec);

		mBar = ResourceManager::Load<Texture>(L"HP_Bar", L"..\\Resources\\UI\\HpBar\\HP_Bar.bmp");
		mPink = ResourceManager::Load<Texture>(L"HP_Pink", L"..\\Resources\\UI\\HpBar\\HP_Pink.bmp");
		mRed = ResourceManager::Load<Texture>(L"HP_Red", L"..\\Resources\\UI\\HpBar\\HP_Red.bmp");

		UI::Initialize();
	}

	void HPbarUI::Update()
	{
		UI::Update();
	}

	void HPbarUI::Render(HDC hdc)
	{
		//TransparentBlt(hdc, 44, 178, mBar->GetWidth(), mBar->GetHeight(), mBar->GetHdc()
		//	, 0, 0, mBar->GetWidth(), mBar->GetHeight(), RGB(255, 0, 255));

		//TransparentBlt(hdc, 50, 180, (int)(mRed->GetWidth() * mDraw / mMHP), mRed->GetHeight(), mRed->GetHdc()
		//	, 0, 0, (int)(mRed->GetWidth() * mDraw / mMHP), mRed->GetHeight(), RGB(255, 0, 255));

		//TransparentBlt(hdc, 50, 180, (int)(mPink->GetWidth() * mHP / mMHP), mPink->GetHeight(), mPink->GetHdc()
		//	, 0, 0, (int)(mPink->GetWidth() * mHP / mMHP), mPink->GetHeight(), RGB(255, 0, 255));
		
		TransparentBlt(hdc, 44, 178, mBar->GetWidth(), mBar->GetHeight(), mBar->GetHdc()
			, 0, 0, mBar->GetWidth(), mBar->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 180, (int)(mRed->GetWidth()), mRed->GetHeight(), mRed->GetHdc()
			, 0, 0, (int)(mRed->GetWidth()), mRed->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 180, (int)(mPink->GetWidth()), mPink->GetHeight(), mPink->GetHdc()
			, 0, 0, (int)(mPink->GetWidth()), mPink->GetHeight(), RGB(255, 0, 255));

		UI::Render(hdc);
	}
}